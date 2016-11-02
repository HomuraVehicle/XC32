#ifndef XC32_ADC_INC
#define XC32_ADC_INC 100
#
#include<XCBase/future.hpp>
#include<XCBase/array_queue.hpp>
#include<XCBase/lock.hpp>
#include<XCBase/chain.hpp>
#include"exceptions.hpp"
#include"sfr/interrupt.hpp"
#include"sfr/adc_base.hpp"
#include"sfr/analog.hpp"
namespace xc32{
	using namespace xc;

	namespace adc{
		using namespace sfr::adc;
		//adc_block用設定クラス
		struct block_setting{
			sfr::adc::vref_mode VrefMode;
			unsigned char ClockDiv;
			block_setting() :VrefMode(sfr::adc::vref_Vref_Gnd), ClockDiv(0){}
			friend bool operator==(const block_setting& s1, const block_setting& s2){
				return s1.VrefMode == s2.VrefMode && s1.ClockDiv == s2.ClockDiv;
			}
			friend bool operator!=(const block_setting& s1, const block_setting& s2){
				return !(s1 == s2);
			}
		};
		//adc_converter用設定クラス
		struct converter_setting{
			unsigned char ClockDiv;
			unsigned char SamplingTime;
			sfr::adc::resolution_mode ResolutionMode;
			converter_setting() : ClockDiv(1), SamplingTime(0), ResolutionMode(sfr::adc::resolution_12bits){}
			friend bool operator==(const converter_setting& s1, const converter_setting& s2){
				return s1.ResolutionMode == s2.ResolutionMode && s1.SamplingTime == s2.SamplingTime && s1.ClockDiv == s2.ClockDiv;
			}
			friend bool operator!=(const converter_setting& s1, const converter_setting& s2){
				return !(s1 == s2);
			}
		};
	}

	//独占型同期ADC
	//	exclusive_adcは明示的に使用者が実体を用意し、それぞれをlock/unlockする必要があるタイプ。
	//	利用時には、まずexclusive_adcの実体を用意し、次にconverterを用意し、そのうえでanalog_pinから読み出し処理を行う。
	//	用意されている機能は最小限。analog_pinから利用する際のconverterの競合チェックやlock済みかどうかの確認すら行わない。
	template<typename adc_block_register_>
	class exclusive_adc{
		typedef adc_block_register_ adc_block_register;
		typedef exclusive_adc<adc_block_register> my_type;
	private:
		adc_block_register ADC;
		unique_lock<adc_block_register> ADCLock;
		adc::block_setting BlockSetting;
	public:
		exclusive_adc()
			: ADCLock(ADC, true)
			, BlockSetting(){
		}
	private:
		//コピー禁止
		exclusive_adc(const my_type&);
		const my_type& operator=(const my_type&);
	public:
		void config(adc::block_setting BlockSetting_) {
			BlockSetting = BlockSetting_;
		}
		bool lock(adc::block_setting BlockSetting_) {
			config(BlockSetting_);
			return lock();
		}
		bool lock(){
			if (is_lock())return false;
			if (ADCLock.lock())return true;
			ADC.reset_all_config();
			
			//参照電圧を設定
			ADC.reference_voltage(BlockSetting.VrefMode);
			__asm("nop");
			//クロックをTcyに設定
			ADC.clock_select(1);
			__asm("nop");
			//クロック分周設定(0～127までなので高位のビットを削除)
			ADC.clock_div((BlockSetting.ClockDiv & 0x7F));
			__asm("nop");
			//ADC始動！
			ADC.enable(1);
			__asm("nop");

			//self calibration待ち
			while (!ADC.module_ready());

			return false;
		}
		void unlock(){
			if (!is_lock())return;

			//ADCを落とす！
			ADC.enable(0);

			ADCLock.unlock();
		}
		bool is_lock()const{
			return ADCLock;
		}
	public:
		//コンバーター　Pinごとに繋がっているコンバーターは異なる点に注意
		template<typename converter_no_>
		struct converter{
		private:
			my_type& Ref;
			bool Lock;

			adc::converter_setting ConverterSetting;
		public:
			converter(my_type& Ref_) :Ref(Ref_), Lock(false){}
		private:
			//コピー禁止
			converter(const my_type&);
			const my_type& operator=(const my_type&);
		public:
			void config(adc::converter_setting ConverterSetting_){
				ConverterSetting = ConverterSetting_;
			}
			bool lock(adc::converter_setting ConverterSetting_){
				config(ConverterSetting_);
				return lock();
			}
			bool lock(){
				if(Lock)return false;
				Lock = true;

				//メインデバイスがロックされていなければ、初期化作業は失敗
				if(!Ref.ADC.is_lock()){
					Lock = false;
					return true;
				}

				//スタートアップ処理
				Ref.ADC.template converter_clock_div<converter_no_>(ConverterSetting.ClockDiv);
				Ref.ADC.template converter_sampling_time<converter_no_>(ConverterSetting.SamplingTime);
				Ref.ADC.template converter_resolution_bits<converter_no_>(ConverterSetting.ResolutionMode);
				//ADC 準備を待つ
				Ref.ADC.template converter_enable<converter_no_>(true);
				while(!Ref.ADC.template converter_work_ready<converter_no_>());

				Ref.ADC.template converter_work_enable<converter_no_>(true);

				return false;
			}
			void unlock(){
				if(!Lock)return;
				Lock = false;


				//メインデバイスがロックされていなければ、アンロック作業は失敗
				if(!Ref.ADC.is_lock())return;

				Ref.ADC.template converter_work_enable<converter_no_>(false);
				Ref.ADC.template converter_enable<converter_no_>(false);
			}
			bool is_lock()const{ return Lock; }
		public:
			void use_alternative_pin(bool val_){
				Ref.ADC.template converter_use_alternative_pin<converter_no_>(val_);
			}
		};
	public:
		template<typename pin_register_>
		class analog_pin{
		private:
			typedef pin_register_ pin_register;
			typedef typename pin_register::analog_no analog_no;
			typedef sfr::adc::an<analog_no> an_register;
		public:
			typedef typename an_register::converter_no converter_no;
			typedef converter<converter_no> my_converter;
		private:
			typedef analog_pin<pin_register_> my_pin;
		private:
			pin_register Pin;
			an_register AN;
			my_type& Ref;
			my_converter& Converter;
			bool Lock;
		private:
			analog_pin(const my_pin&);
			const my_pin& operator()(const my_pin&);
		public:
			analog_pin(my_type& Ref_, my_converter& Converter_):Ref(Ref_), Converter(Converter_), Lock(false){}
			~analog_pin(){ unlock(); }
			bool lock(){
				if (is_lock())return false;

				Pin.tris(true);
				Pin.analog(true);
				Pin.opendrain(false);

				Lock = true;

				return false;
			}
			void unlock(){
				if (!is_lock())return;

				Pin.tris(false);
				Pin.analog(false);
				Pin.opendrain(false);

				Lock = false;
			}
			bool is_lock()const{ return Lock; }
		public:
			uint16 operator()(void){
				xc32_assert(is_lock(), exception(0xE1));

				//代替ピンの設定の有無を設定
				Converter.use_alternative_pin(AN.is_alternative());

				//チャンネルを設定
				Ref.ADC.individual_convert_select(analog_no::No);

				//個別スキャン開始
				Ref.ADC.individual_convert_trigger(true);
				__asm("nop");

				//スキャン待ち
				while (!AN.data_ready());

				//データを加算
				uint16 Val = AN.data();

				return Val;
			}
			uint16 operator()(uint16 ObserveNum_){
				xc32_assert(is_lock(), exception(0xE2));

				//代替ピンの設定の有無を設定
				Converter.use_alternative_pin(AN.is_alternative());

				//チャンネルを設定
				Ref.ADC.individual_convert_select(analog_no::No);

				uint32 Val = 0;
				for (uint16 ObserveCnt = 0; ObserveCnt < ObserveNum_; ++ObserveCnt) {
					//個別スキャン開始
					Ref.ADC.individual_convert_trigger(true);
					__asm("nop");

					//スキャン待ち
					while (!AN.data_ready());

					//データを加算
					Val += AN.data();
				}

				return Val;
			}
		};
	};

	//すべての共有型ADCの基本となる、初期化管理をつかさどるクラス
	template<typename adc_block_register_, typename identifier_>
	class basic_shared_adc{
		typedef basic_shared_adc<adc_block_register_, identifier_> my_type;
	public:
		struct block{
			template<typename> friend struct converter;
		private:
			adc_block_register_ ADC;
			unique_lock<adc_block_register_> ADCLock;
		private:
			unsigned int LockCnt;
			adc::block_setting Setting;
		public:
			void config(const adc::block_setting& Setting_){
				Setting = Setting_;
			}
			bool lock(const adc::block_setting& Setting_){
				config(Setting_);
				return lock();
			}
			bool lock(){
				if(++LockCnt == 1){
					if(ADCLock.lock()){
						//Lockに失敗したら戻してから終わる
						LockCnt = 0;
						return true;
					}

					//参照電圧を設定
					ADC.reference_voltage(Setting.VrefMode);
					__asm("nop");
					//クロックをTcyに設定
					ADC.clock_select(1);
					__asm("nop");
					//クロック分周設定(0～127までなので高位のビットを削除)
					ADC.clock_div((Setting.ClockDiv & 0x7F));
					__asm("nop");
					//ADC始動！
					ADC.enable(1);
					__asm("nop");

					//self calibration待ち
					while(!ADC.module_ready());
				}

				return false;
			}
			void unlock(){
				if(LockCnt == 0)return;

				if(--LockCnt == 0){
					//ADC停止
					ADC.enable(0);

					//ロック解除
					ADCLock.unlock();
				}
			}
			bool is_lock(){ return LockCnt > 0; }
			bool relock(const adc::block_setting& Setting_, bool ForceReset = false){
				//一緒ならパス
				if(Setting == Setting_ && !ForceReset)return true;

				//一旦ストップ
				ADC.enable(0);

				//設定更新
				Setting = Setting_;

				//参照電圧を設定
				ADC.reference_voltage(Setting.VrefMode);
				__asm("nop");
				//クロックをTcyに設定
				ADC.clock_select(1);
				__asm("nop");
				//クロック分周設定(0～127までなので高位のビットを削除)
				ADC.clock_div((Setting.ClockDiv & 0x7F));
				__asm("nop");
				//ADC始動！
				ADC.enable(1);
				__asm("nop");

				//self calibration待ち
				while(!ADC.module_ready());

				//ADC再始動
				ADC.enable(1);
				__asm("nop");
				//self calibration待ち
				while(!ADC.module_ready());

				return false;
			}
		public:
			void individual_convert_select(unsigned char no){
				ADC.individual_convert_select(no);
				__asm("nop");
			}
			void individual_convert_trigger(){
				ADC.individual_convert_trigger(true);
				__asm("nop");
			}
			//スキャントリガ源選択ビット,0:トリガなし,1:グローバルソフトウェアトリガ,…
			void scan_trigger_select(unsigned char val_){ADC.scan_trigger_select(val_);}
			//グローバルソフトウェアトリガビット
			void global_convert_trigger(){ ADC.global_convert_trigger(); }
			//一斉スキャン（Global Scan）が終了したか　読みだすと自動的に落ちる
			bool is_end_global_convert()const volatile{ return ADC.is_end_global_convert(); }
		};
		static block Block;
	public:
		template<typename converter_no_>
		struct converter{
		private:
			bool IsUsed;
			unsigned int LockCnt;
			adc::converter_setting Setting;
		public:
			void config(const adc::converter_setting& Setting_){
				Setting = Setting_;
			}
			bool lock(const adc::converter_setting& Setting_){
				config(Setting_);
				return lock();
			}
			bool lock(){
				//adc_blockをロック　失敗したら何もせず終わる
				if(my_type::Block.lock())return true;

				if(++LockCnt == 0){
					//スタートアップ処理
					my_type::Block.ADC.template converter_clock_div<converter_no_>(Setting.ClockDiv);
					my_type::Block.ADC.template converter_sampling_time<converter_no_>(Setting.SamplingTime);
					my_type::Block.ADC.template converter_resolution_bits<converter_no_>(Setting.ResolutionMode);

					//ADC 準備を待つ
					my_type::Block.ADC.template converter_enable<converter_no_>(true);
					while(!my_type::Block.ADC.template converter_work_ready<converter_no_>());
					my_type::Block.ADC.template converter_work_enable<converter_no_>(true);
				}

				return false;
			}
			void unlock(){
				if(LockCnt == 0)return;
				if(--LockCnt == 0){
					my_type::Block.ADC.template converter_work_enable<converter_no_>(false);
					my_type::Block.ADC.template converter_enable<converter_no_>(false);
				}

				//adc_blockをアンロック
				my_type::Block.unlock();
			}
			bool is_lock()const{ return LockCnt != 0; }
			bool relock(const adc::converter_setting& Setting_, bool ForceReset = false){
				//一緒ならパス
				if(Setting == Setting_ && !ForceReset)return true;

				//設定更新
				Setting = Setting_;

				//一旦ストップ
				my_type::Block.ADC.template converter_work_enable<converter_no_>(false);
				my_type::Block.ADC.template converter_enable<converter_no_>(false);

				//スタートアップ処理
				my_type::Block.ADC.template converter_clock_div<converter_no_>(Setting.ClockDiv);
				my_type::Block.ADC.template converter_sampling_time<converter_no_>(Setting.SamplingTime);
				my_type::Block.ADC.template converter_resolution_bits<converter_no_>(Setting.ResolutionMode);

				//ADC 準備を待つ
				my_type::Block.ADC.template converter_enable<converter_no_>(true);
				while(!my_type::Block.ADC.template converter_work_ready<converter_no_>());
				my_type::Block.ADC.template converter_work_enable<converter_no_>(true);

				return false;
			}
		public:
			bool start(){
				if(IsUsed)return true;
				IsUsed = true;
				return false;
			}
			void stop(){
				IsUsed = false;
			}
		public:
			void use_alternative_pin(bool val_){
				my_type::Block.ADC.template converter_use_alternative_pin<converter_no_>(val_);
			}
		};
		template<typename converter_no_>
		struct cv{
			static converter<converter_no_> Converter;
		};
	};
	template<typename adc_block_register_, typename identifier_>
	typename basic_shared_adc<adc_block_register_, identifier_>::block basic_shared_adc<adc_block_register_, identifier_>::Block;
	template<typename adc_block_register_, typename identifier_>
	template<typename converter_no_>
	typename basic_shared_adc<adc_block_register_, identifier_>::template converter<converter_no_> basic_shared_adc<adc_block_register_, identifier_>::cv<converter_no_>::Converter;

	//共有型同期ADC
	//	shared_adcは実体を用意する必要がない。代わりにanalog_pinからのlock/unclockで適宜初期化/終端化される。
	//	逆に言えば、shared_adcを解放するためには、すべてのanalog_pinでunlockする必要がある。
	//	analog_pinの読み出し処理は重複していないことの確認がなされる。重複時は読みだし失敗となり、0xffffが返る
	template<typename adc_block_register_, typename identifier_>
	class shared_adc{
		typedef shared_adc<adc_block_register_, identifier_> my_type;
		struct my_identifier{};//独自のidentifierを作る　これは、identifier_が使いまわされている場合に、basic_shared_adcが競合するのを防ぐため。
		typedef basic_shared_adc<adc_block_register_, my_identifier> my_adc;
	private:
		static adc::block_setting BlockSetting;
		template<typename converter_no_>
		struct cv{
			static adc::converter_setting ConverterSetting;
		};
	public:
		static void set_default(const adc::block_setting& BlockSetting_){
			BlockSetting = BlockSetting_;
		}
		template<typename converter_no_>
		static void set_default(const adc::converter_setting& ConverterSetting_){
			cv<converter_no_>::ConverterSetting = ConverterSetting_;
		}
	public:
		template<typename pin_register_>
		class analog_pin{
			typedef pin_register_ pin_register;
			typedef typename pin_register::analog_no analog_no;
			typedef sfr::adc::an<typename pin_register_::analog_no> an_register;
			typedef typename an_register::converter_no converter_no;
			typedef typename my_adc::template cv<converter_no> my_converter;
			typedef typename my_type::cv<converter_no> my_converter_setting;
			typedef analog_pin<pin_register_> my_pin;
		private:
			bool IsLock;
			pin_register Pin;
			an_register AN;
			const adc::block_setting* pBlockSetting;
			const adc::converter_setting* pConverterSetting;
		private:
			analog_pin(const my_pin&);
			const my_pin& operator=(const my_pin&);
		public:
			analog_pin()
				:IsLock(false), pBlockSetting(0), pConverterSetting(0){}
			~analog_pin(){ unlock(); }
			void config(const adc::block_setting* pBlockSetting_, const adc::converter_setting* pADCSetting_){
				pBlockSetting = pBlockSetting_;
				pConverterSetting = pADCSetting_;
			}
			bool lock(const adc::block_setting* pBlockSetting_, const adc::converter_setting* pADCSetting_){
				config(pBlockSetting_, pADCSetting_);
				return lock();
			}
			bool lock(){
				if(is_lock())return false;

				if(my_adc::Block.lock())return true;

				if(my_converter::Converter.lock()){
					my_adc::Block.unlock();
					return true;
				}

				Pin.tris(true);
				Pin.analog(true);
				Pin.opendrain(false);

				IsLock = true;
				return false;
			}
			bool is_lock()const{
				return IsLock;
			}
			void unlock(){
				if(!is_lock())return;

				Pin.tris(false);
				Pin.analog(false);
				Pin.opendrain(false);

				my_converter::Converter.unlock();
				my_adc::Block.unlock();;

				IsLock = false;
			}
		public:
			uint16 operator()(void){
				xc32_assert(is_lock(), exception(0xE1));

				bool ForceReset = false;

				//ここで、Converter使用権確保
				if(my_converter::Converter.start())return 0xFFFF;

				if(pBlockSetting == 0){
					//relockがtrueを返した＝リセットする必要がない
					ForceReset = !my_adc::Block.relock(my_type::BlockSetting);
				} else{
					ForceReset = !my_adc::Block.relock(*pBlockSetting);
				}

				if(pConverterSetting == 0){
					my_converter::Converter.relock(my_converter_setting::ConverterSetting, ForceReset);
				} else{
					my_converter::Converter.relock(*pConverterSetting, ForceReset);
				}

				//代替ピンの設定の有無を設定
				my_converter::Conveter.use_alternative_pin(AN.is_alternative());

				//個別スキャンするチャンネルを設定
				my_adc::Block.individual_convert_select(analog_no::No);
				__asm("nop");

				//トリガを引く
				my_adc::Block.individual_convert_trigger();

				//スキャン待ち
				while(!AN.data_ready());

				//データを加算
				uint16 Val = AN.data();

				//コンバーター使用権放棄
				my_converter::Conveter.stop();

				return Val;
			}
			uint16 operator()(uint16 ObserveNum_){
				xc32_assert(is_lock(), exception(0xE2));

				bool ForceReset = false;

				//ここで、Converter使用権確保
				if(my_converter::Converter.start())return 0xFFFF;

				if(pBlockSetting == 0){
					//relockがtrueを返した＝リセットする必要がない
					ForceReset = !my_adc::Block.relock(my_type::BlockSetting);
				} else{
					ForceReset = !my_adc::Block.relock(*pBlockSetting);
				}

				if(pConverterSetting == 0){
					my_converter::Converter.relock(my_converter_setting::ConverterSetting, ForceReset);
				} else{
					my_converter::Converter.relock(*pConverterSetting, ForceReset);
				}

				//代替ピンの設定の有無を設定
				my_converter::Converter.use_alternative_pin(AN.is_alternative());

				//個別スキャンするチャンネルを設定
				my_adc::Block.individual_convert_select(analog_no::No);

				uint32 Val = 0;
				for(uint16 ObserveCnt = 0; ObserveCnt<ObserveNum_; ++ObserveCnt){
					//トリガを引く
					my_adc::Block.individual_convert_trigger();

					//スキャン待ち
					while(!AN.data_ready());

					//データを加算
					Val += AN.data();
				}

				//コンバーター使用権放棄
				my_converter::Converter.stop();

				return Val;
			}
		};
	};
	template<typename adc_block_register_, typename identifier_>
	adc::block_setting shared_adc<adc_block_register_, identifier_>::BlockSetting;
	template<typename adc_block_register_, typename identifier_>
	template<typename converter_no_>
	adc::converter_setting shared_adc<adc_block_register_, identifier_>::cv<converter_no_>::ConverterSetting;

	//非同期型個別コンバートADC
	//	async_adcはshared_adc同様、実体を用意する必要がない。analog_pinからのlock/unclockで適宜初期化/終端化される。
	//	一つのadc_block_registerを一つのasync_functional_adcが排他的に利用する
	//	analog_pinから読みだしても値はその場で読みだされる、futureが戻り値として返される。内部ではqueueにadc用のtaskが積まれる。
	//	機能させるためには、定期的にconverterごとのwork関数を呼び出す必要がある。
	template<typename adc_block_register_, typename identifier_>
	class async_functional_adc{
		//=== 設計概要 ===
		//async_functional_adcは、個別コンバートを利用してadcのデータ読み出しを担当する
		//async_functional_adc::analog_pinから、operator()を実行すると、
		//	RequestQueueにデータリクエスト内容が積まれる
		//	リクエストには、結果書き込み用のpromise&も含まれる
		//	戻り値として、利用者はfutureを受け取る
		//adcのoperator()実行によって、
		//	走っているタスクがなければ、RequestQueueを読み込む
		//	リクエスト内容に沿って一括コンバートを駆動する
		//	データ読み出しが完了していれば、promise&を介して通知する
		//	すべてが完了後、タスクをキューから外す
	private:
		typedef adc_block_register_ adc_block_register;
		typedef async_functional_adc<adc_block_register_, identifier_> my_type;
		struct my_identifier{};
		typedef basic_shared_adc<adc_block_register_, my_identifier> my_adc;
	private:
		//データリクエスト内容
		struct request{
		public:
			promise<uint16>& Ref;
			const unsigned char AN;
		public:
			const adc::block_setting* pBlockSetting;
			const adc::converter_setting* pConverterSetting;
			uint16 Num;
		public:
			request(promise<uint16>& Ref_, unsigned char AN_)
				: Ref(Ref_)
				, AN(AN_)
				, pBlockSetting(0)
				, pConverterSetting(0)
				, Num(1){
			}
		public:
			//Converter系 startは失敗したらtrueを返す
			virtual bool start() = 0;
			virtual void stop() = 0;
			//AN Pin系
			virtual uint16 try_read_data() = 0;	//失敗したら、戻り値は0xffff
		};
		typedef typename xc::chain<request*>::element request_ptr_element;
		static xc::chain<request*> ReqPtrQueue;
		static request* HandlingReqPtr;
		static uint32 DataSum;
		static uint16 DataCnt;
	public:
		template<typename pin_register_>
		struct analog_pin {
		private:
			typedef pin_register_ pin_register;
			typedef typename pin_register_::analog_no analog_no;
			typedef sfr::adc::an<typename pin_register_::analog_no> an_register;
			typedef typename an_register::converter_no converter_no;
			typedef typename my_adc::template cv<converter_no> my_converter;
		private:
			struct an_request :public request{
				an_register AN;
			public:
				an_request(promise<uint16>& Ref_) :request(Ref_, analog_no::No){}
			public:
				virtual bool start(){
					//ここで、Converter使用権確保
					if(my_converter::Converter.start())return true;

					bool ForceReset = false;
					if(pBlockSetting == 0){
						//relockがtrueを返した＝リセットする必要がない
						ForceReset = !my_adc::Block.relock(my_type::BlockSetting);
					} else{
						ForceReset = !my_adc::Block.relock(*pBlockSetting);
					}

					if(pConverterSetting == 0){
						my_converter::Converter.relock(my_converter_setting::ConverterSetting, ForceReset);
					} else{
						my_converter::Converter.relock(*pConverterSetting, ForceReset);
					}

					//代替ピンの設定の有無を設定
					my_converter::Conveter.use_alternative_pin(AN.is_alternative());

					return false;
				}
				virtual void stop(){
					//コンバーター使用権放棄
					my_converter::Conveter.stop();
				}
				virtual uint16 read_data(){
					//スキャン待ち
					if(!AN.data_ready())return 0xffff;
					return AN.data();
				}
			};
			an_request Request;
			request_ptr_element Element;	//Requestへのポインタを掴んでいる
		private:
			pin_register Pin;
			bool IsLock;
			promise<uint16> Promise;
		public:
			analog_pin()
				: IsLock(false)
				, Request(Promise){
				*Element = &Request;
			}
			~analog_pin(){ if (is_lock())unlock(); }
			void config(const adc::block_setting* pBlockSetting_, const adc::converter_setting* pConverterSetting_) {
				Request.pBlockSetting = pBlockSetting_;
				Request.pConverterSetting = pConverterSetting_;
			}
			bool lock(const adc::block_setting* pBlockSetting_, const adc::converter_setting* pConverterSetting_) {
				config(pBlockSetting_, pConverterSetting_);
				return lock();
			}
			bool lock(){
				if(is_lock())return false;

				if(my_adc::Block.lock())return true;

				if(my_converter::Converter.lock()){
					my_adc::Block.unlock();
					return true;
				}

				Pin.tris(true);
				Pin.analog(true);
				Pin.opendrain(false);

				IsLock = true;
				return false;
			}
			bool is_lock()const{
				return IsLock;
			}
			void unlock(){
				if(!is_lock())return;

				Pin.tris(false);
				Pin.analog(false);
				Pin.opendrain(false);

				my_converter::Converter.unlock();
				my_adc::Block.unlock();;

				IsLock = false;
			}
		public:
			//データ読み出し
			//	リクエストがそもそも不可能な場合は空のfutureが返る
			//	何らかの原因で失敗した場合は、0xffffがfutureに書き込まれる
			future<uint16> operator()(void){return operator()(1);}
			future<uint16> operator()(uint16 ObserveNum_){
				if (owns_request())return future<uint16>();
				if (ObserveNum_ == 0)return future<uint16>();

				//Requestを書き換えて、そのポインタをつかんでるElementをQueueにぶち込む
				Request.Num = ObserveNum_;
				ReqPtrQueue.push_back(Element);

				return Promise.get_future();
			}
		public:
			//現在リクエスト中か？
			bool owns_request()const{ return !Promise.can_get_future() || !static_cast<bool>(Element); }
		};
	public:
		//関数オブジェクトとして使う場合の、タスク関数
		void operator()(void){work();}
	public:
		//静的メンバ関数として用意された、タスク関数
		static void work(){
			if(!is_lock())return;

			//リクエスト中のデータがある場合
			if(HandlingReqPtr){
				uint16 Data = HandlingReqPtr->try_read_data();

				//データ読み取りに失敗していなければ
				if(Data != 0xffff){
					DataSum += Data;
					++DataCnt;

					if(DataCnt >= HandlingReqPtr->Num){
						//Converterを停止
						HandlingReqPtr->stop();
						//結果を書き込み
						HandlingReqPtr->Ref.write(static_cast<uint16>(DataSum / DataCnt));
						//リクエストデータ終了
						HandlingReqPtr = 0;
					} else{
						//個別スキャンするチャンネルを設定
						my_adc::Block.individual_convert_select(HandlingReqPtr->AN);
						__asm("nop");
						//トリガを引いて、最初のリクエスト
						my_adc::Block.individual_convert_trigger();
					}
				}
			}

			//リクエスト中のデータがない場合
			while(HandlingReqPtr == 0 && !RequestQueue.empty()){
				//先頭から抜いてくる
				HandlingReqPtr = ReqPtrQueue.front();
				ReqPtrQueue.pop_front();

				//ヌルポをはじく（原理的にはないはず）
				if(HandlingReqPtr == 0)continue;

				//startに失敗することは、原理的にあり得ないので無視
				HandlingReqPtr->start();

				DataSum = 0;
				DataCnt = 0;

				//個別スキャンするチャンネルを設定
				my_adc::Block.individual_convert_select(HandlingReqPtr->AN);
				__asm("nop");

				//トリガを引いて、最初のリクエスト
				my_adc::Block.individual_convert_trigger();
			}
		}
		//登録されたすべてのリクエストを破棄
		static void clear(){
			for(xc::chain<request*>::iterator Itr = ReqPtrQueue.begin(); Itr != ReqPtrQueue.end(); ++Itr){
				if(*Itr != 0){
					(*Itr)->write(0xffff);
				}
			}
			ReqPtrQueue.clear();
			if(HandlingReqPtr){
				HandlingReqPtr->Ref.write(0xffff);
			}
			HandlingReqPtr = 0;
		}
	};
	template<typename adc_block_register_, typename identifier_>
	xc::chain < typename async_functional_adc <adc_block_register_,identifier_>::request* > async_functional_adc < typename adc_block_register_, identifier_>::ReqPtrQueue;
	template<typename adc_block_register_, typename identifier_>
	typename async_functional_adc <adc_block_register_, identifier_>::request* async_functional_adc <adc_block_register_, identifier_>::HandlingReqPtr = 0;
	template<typename adc_block_register_, typename identifier_>
	uint32 async_functional_adc <adc_block_register_, identifier_>::DataSum = 0;
	template<typename adc_block_register_, typename identifier_>
	uint16 async_functional_adc <adc_block_register_, identifier_>::DataCnt = 0;

	/*
	//非同期型一括コンバートADC
	//	
	template<typename adc_block_register_, typename identifier_>
	class async_functional_gadc{
		//=== 設計概要 ===
		//async_functional_gadcは、一括コンバートを利用してadcのデータ読み出しを担当する
		//async_functional_gadc::analog_pinから、operator()を実行すると、
		//	RequestQueueにデータリクエスト内容が積まれる
		//	リクエストには、結果書き込み用のpromise&も含まれる
		//	戻り値として、利用者はfutureを受け取る
		//adcのoperator()実行によって、
		//走っているタスクがなければ、RequestQueueを読み込む
		//リクエスト内容に沿って一括コンバートを駆動する
		//データ読み出しが完了していれば、promise&を介して通知する
		//すべてが完了後、タスクをキューから外す
		typedef async_functional_gadc<adc_block_register_, identifier_> my_type;
	private:
		struct block{
		private:
			static adc_block_register_ ADC;
			static unique_lock<adc_block_register_> ADCLock;
		private:
			static unsigned int LockCnt;
			static adc::adc_block_setting Default;
			static const adc::adc_block_setting* Apply;
		private:
			static void set_default(const adc::adc_block_setting& Setting){
				Default = Setting;
			}
		private:
			static bool lock(){
				if(++LockCnt == 1){
					if(ADCLock.lock())return true;

					//参照電圧を設定
					ADC.reference_voltage(Default.VrefMode);
					__asm("nop");
					//クロックをTcyに設定
					ADC.clock_select(1);
					__asm("nop");
					//クロック分周設定(0～127までなので高位のビットを削除)
					ADC.clock_div((Default.ClockDiv & 0x7F));
					__asm("nop");
					//ADC始動！
					ADC.enable(1);
					__asm("nop");

					//self calibration待ち
					while(!ADC.module_ready());
				}

				return false;
			}
			static void unlock(){
				if(--LockCnt == 0){
					//ADC停止
					ADC.enable(0);

					//ロック解除
					ADCLock.unlock();
				}
			}
			static bool is_lock(){ return LockCnt>0; }
			//再起動時にtrueを返す
			static bool start(const adc::adc_block_setting* pSetting, bool ForceReset = false){
				//一緒ならパス
				if(pSetting == Apply && !ForceReset)return false;

				//一旦ストップ
				ADC.enable(0);

				if(pSetting == 0){
					//参照電圧を設定
					ADC.reference_voltage(Default.VrefMode);
					__asm("nop");
					//クロックをTcyに設定
					ADC.clock_select(1);
					__asm("nop");
					//クロック分周設定(0～127までなので高位のビットを削除)
					ADC.clock_div((Default.ClockDiv & 0x7F));
					__asm("nop");
					Apply = 0;
				} else{
					//参照電圧を設定
					ADC.reference_voltage(Apply->VrefMode);
					__asm("nop");
					//クロックをTcyに設定
					ADC.clock_select(1);
					__asm("nop");
					//クロック分周設定(0～127までなので高位のビットを削除)
					ADC.clock_div((Apply->ClockDiv & 0x7F));
					__asm("nop");
					Apply = pSetting;
				}

				//ADC再始動
				ADC.enable(1);
				__asm("nop");
				//self calibration待ち
				while(!ADC.module_ready());

				return true;
			}
			static void stop(){}
		public:
			template<typename converter_no_>
			struct converter{
			private:
				static unsigned int LockCnt;
				static bool IsUsed;

				static adc::adc_setting Default;
				static adc::adc_setting* Apply;

				static array_queue<data_request*, QueueSize_> RequestQueue;
				static itf_request_data* Request;
			private:
				static bool lock(){
					//adc_blockをロック
					if(block::lock())return true;

					if(++LockCnt == 0){
						//スタートアップ処理
						block::ADC.adc_clock_div<converter_no_>(Default.ClockDiv);
						block::ADC.sampling_time<converter_no_>(Default.SamplingTime);
						block::ADC.resolution_bits<converter_no_>(Default.ResolutionMode);
						Apply = 0;

						//ADC 準備を待つ
						block::ADC.adc_enable<converter_no_>(true);
						while(!block::ADC.adc_ready<converter_no_>());

						block::ADC.adc_work_enable<converter_no_>(true);
					}

					return false;
				}
				static void unlock(){
					if(--Lock == 0){
						block::ADC.adc_work_enable<converter_no_>(false);
						block::ADC.adc_enable<converter_no_>(false);
					}

					//adc_blockをアンロック
					block::unlock();
				}
				static bool is_lock()const{ return LockCnt != 0; }
				static void use_alternative_pin(bool val_){
					block::ADC.use_alternative_pin<converter_no_>(val_);
				}
				//失敗した場合にtrueを返す
				//blockのstartと戻り値の意味が違うので注意
				static bool start(const adc::adc_block_setting* pBlockSetting, const adc::adc_setting* pSetting, bool ForceReset = false){
					if(IsUsed)return true;
					IsUsed = true;

					//再起動が必要な設定だった場合は、こちらも強制的に再起動
					ForceReset = block::start(pBlockSetting, ForceReset);

					//一緒ならパス
					if(pSetting == Apply && !ForceReset)return false;

					//一旦ストップ
					block::ADC.adc_work_enable<converter_no_>(false);
					block::ADC.adc_enable<converter_no_>(false);

					//スタートアップ処理
					if(pSetting == 0){
						block::ADC.adc_clock_div<converter_no_>(Default.ClockDiv);
						block::ADC.sampling_time<converter_no_>(Default.SamplingTime);
						block::ADC.resolution_bits<converter_no_>(Default.ResolutionMode);
						Apply = 0;
					} else{
						block::ADC.adc_clock_div<converter_no_>(pSetting->ClockDiv);
						block::ADC.sampling_time<converter_no_>(pSetting->SamplingTime);
						block::ADC.resolution_bits<converter_no_>(pSetting->ResolutionMode);
						Apply = pSetting;
					}

					//ADC 準備を待つ
					block::ADC.adc_enable<converter_no_>(true);
					while(!block::ADC.adc_ready<converter_no_>());

					block::ADC.adc_work_enable<converter_no_>(true);

					return false;
				}
				static void stop(){
					block::stop();

					IsUsed = false;
				}
				static void read_data(){
					block::ADC.individual_convert(true);
					__asm("nop");
				}
			public:
				static void set_default(const adc::adc_block_setting& BlcokSetting, const adc::adc_setting& Setting){
					block::set_default(BlcokSetting);
					Default = Setting;

					//すでにロックして起動済みなら、明示的にDefaultで再起動
					if(is_lock() && Apply == 0){
						start(0, 0, true);
						stop();
					}
				}
				static void set_default(const adc::adc_setting& Setting){
					Default = Setting;

					//すでにロックして起動済みなら、明示的にDefaultで再起動
					if(is_lock() && Apply == 0){
						Apply = reinterpret_cast<const adc::adc_setting*>(1);
						start(0, 0);
						stop();
					}
				}
				static bool request(data_request& Request_){
					return RequestQueue.push(&Request_);
				}
				static void work(){
					if(!is_lock())return;

					//リクエスト中のデータがある場合
					if(Request != 0){
						if(ADC.module_ready()){
							//Request->Ref.ref() = read(Request->getAN(), Request, Request->Num);
							//Request->Ref.end_write();
							Request->Ref.set_value(read(Request->getAN(), Request, Request->Num));
							Request = 0;

						}
					}

					//リクエスト中のデータがない場合
					if(Request == 0 && !RequestQueue.empty()){
						Request = RequestQueue.next();
						RequestQueue.pop();
						restart(Request->VrefMode, Request->ClockDiv);
					}
				}
			};
		};
	public:
		template<typename converter_no_>
		static void set_default(const adc::adc_block_setting& BlockSetting, const adc::adc_setting& ADCSetting){
			block::converter<converter_no_>::set_default(BlockSetting, ADCSetting);
		}
		template<typename converter_no_>
		static void set_default(const adc::adc_setting& ADCSetting){
			block::converter<converter_no_>::set_default(ADCSetting);
		}
		template<typename converter_no_>
		static void work(){
			converter<converter_no_>::work();
		}
	public:
		template<typename pin_register_>
		class analog_pin{
			typedef pin_register_ pin_register;
			typedef typename pin_register::analog_no analog_no;
			typedef sfr::adc::an<typename pin_register_::analog_no> an_register;
			typedef typename an_register::converter_no converter_no;
			typedef typename block::converter<converter_no> my_converter;
			typedef analog_pin<pin_register_> my_pin;
		public:
			typedef xc::polling_future<uint16> future;
		private:
			class adc_promise{
			private:
				struct base :public xc::promise_base<uint16>{
					an_register AN;
					bool WaitRead;
				public:
					base():WaitRead(false){}
				public://override functions of xc::promise_base
					virtual bool can_read(){
						return AN.data_ready();
					}
					virtual void read(uint16& Data_){
						Data_ = AN.data();
						WaitRead = false;
					}
					virtual void cancel(){
						WaitRead = false;
					}
				};
			public:
				base Base;
			public:
				promise() :Base(){}
			private://コピー禁止
				promise(const my_type&){}
				const my_type& operator=(const my_type&);
			public:
				bool can_get_future()const{ return !Base.WaitRead; }
				future get_future(){
					Base.WaitRead = true;
					return future(Base);
				}
			};
		private:
			bool IsLock;
			pin_register Pin;
			const adc::adc_block_setting* pBlockSetting;
			const adc::adc_setting* pADCSetting;

			promise<uint16> Promise;
		private:
			analog_pin(const my_pin&);
			const my_pin& operator=(const my_pin&);
		public:
			analog_pin()
				:IsLock(false){}
			~analog_pin(){ unlock(); }
			bool lock(){
				if(is_lock())return false;

				if(my_converter::lock())return true;

				Pin.tris(true);
				Pin.analog(true);
				Pin.opendrain(false);

				IsLock = true;
				return false;
			}
			bool is_lock()const{
				return IsLock;
			}
			void unlock(){
				if(!is_lock())return;

				Pin.tris(false);
				Pin.analog(false);
				Pin.opendrain(false);

				my_converter::unlock();

				IsLock = false;
			}
		public:
			future operator()(void){
				if(!Promise.can_get_future())return future<uint16>();

				RequestData.Num = 1;
				if(my_converter::request(RequestData))return future<uint16>();

				return Promise.get_future();
			}
		};
	};
	template<typename adc_block_register_, typename identifier_, unsigned int QueueSize_>
	adc_block_register_ async_adc<adc_block_register_, identifier_>::block::ADC;
	template<typename adc_block_register_, typename identifier_, unsigned int QueueSize_>
	unique_lock<adc_block_register_> async_adc<adc_block_register_, identifier_>::block::ADCLock(ADC, true);
	template<typename adc_block_register_, typename identifier_, unsigned int QueueSize_>
	unsigned int async_adc<adc_block_register_, identifier_>::block::LockCnt = 0;
	template<typename adc_block_register_, typename identifier_, unsigned int QueueSize_>
	adc::adc_block_setting async_adc<adc_block_register_, identifier_>::block::Default;
	template<typename adc_block_register_, typename identifier_, unsigned int QueueSize_>
	const adc::adc_block_setting* async_adc<adc_block_register_, identifier_>::block::Apply;

	template<typename adc_block_register_, typename identifier_, unsigned int QueueSize_>
	template<typename converter_no_>
	unsigned int async_adc<adc_block_register_, identifier_>::converter<converter_no_>::LockCnt = 0;
	template<typename adc_block_register_, typename identifier_, unsigned int QueueSize_>
	template<typename converter_no_>
	bool async_adc<adc_block_register_, identifier_>::block::converter<converter_no_>::IsUsed = false;
	template<typename adc_block_register_, typename identifier_, unsigned int QueueSize_>
	template<typename converter_no_>
	adc::adc_setting async_adc<adc_block_register_, identifier_>::block::converter<converter_no_>::Default;
	template<typename adc_block_register_, typename identifier_, unsigned int QueueSize_>
	template<typename converter_no_>
	const adc::adc_setting* async_adc<adc_block_register_, identifier_>::block::converter<converter_no_>::Apply;
	*/
}
#
#endif
