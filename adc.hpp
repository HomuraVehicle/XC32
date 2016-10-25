#ifndef XC32_ADC_INC
#define XC32_ADC_INC 100
#
#include<XCBase/future.hpp>
#include<XCBase/array_queue.hpp>
#include<XCBase/lock.hpp>
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
		};
		//adc_converter用設定クラス
		struct converter_setting{
			unsigned char ClockDiv;
			unsigned char SamplingTime;
			sfr::adc::resolution_mode ResolutionMode;
			converter_setting() : ClockDiv(1), SamplingTime(0), ResolutionMode(sfr::adc::resolution_12bits){}
		};
	}

	//独占型同期ADC
	//	exclusive_adcは明示的に使用者が実体を用意し、それぞれをlock/unlockする必要があるタイプ。
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

			//参照電圧を設定
			ADC.reference_voltage(BlockSetting.VrefMode);
			__asm("nop");
			//クロックをTcyに設定
			ADC.clock_select(1);
			__asm("nop");
			//クロック分周設定(0〜127までなので高位のビットを削除)
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
				if(!Ref.ADC.is_lock())return true;

				//スタートアップ処理
				Ref.ADC.converter_clock_div<converter_no_>(ConverterSetting.ClockDiv);
				Ref.ADC.converter_sampling_time<converter_no_>(ConverterSetting.SamplingTime);
				Ref.ADC.converter_resolution_bits<converter_no_>(ConverterSetting.ResolutionMode);

				//ADC 準備を待つ
				Ref.ADC.converter_enable<converter_no_>(true);
				while(!Ref.ADC.converter_ready<converter_no_>());

				Ref.ADC.converter_work_enable<converter_no_>(true);
			}
			void unlock(){
				if(!Lock)return;
				Lock = false;


				//メインデバイスがロックされていなければ、アンロック作業は失敗
				if(!Ref.ADC.is_lock())return;

				Ref.ADC.converter_work_enable<converter_no_>(false);
				Ref.ADC.converter_enable<converter_no_>(false);
			}
			bool is_lock()const{ return Lock; }
			void use_alternative_pin(bool val_){
				Ref.ADC.converter_use_alternative_pin<converter_no_>(val_);
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
				Ref.ADC.individual_convert_input_select(analog_no::No);

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
				Ref.ADC.individual_convert_input_select(analog_no::No);

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

	/*
	//共有型同期ADC
	//	shared_adcは実体を用意する必要がない。代わりにanalog_pinからのlock/unclockで適宜初期化/終端化される。
	//	逆に言えば、shared_adcを解放するためには、すべてのanalog_pinでunlockする必要がある。
	//	analog_pinの読み出し処理は重複していないことの確認がなされる。重複時は読みだし失敗となり、0xffffが返る
	template<typename adc_block_register_, typename identifier_>
	class shared_adc{
		typedef shared_adc<adc_block_register_, identifier_> my_type;
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
					//クロック分周設定(0〜127までなので高位のビットを削除)
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
					//クロック分周設定(0〜127までなので高位のビットを削除)
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
					//クロック分周設定(0〜127までなので高位のビットを削除)
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
	public:
		template<typename pin_register_>
		class analog_pin{
			typedef pin_register_ pin_register;
			typedef typename pin_register::analog_no analog_no;
			typedef sfr::adc::an<typename pin_register_::analog_no> an_register;
			typedef typename an_register::converter_no converter_no;
			typedef typename block::converter<converter_no> my_converter;
			typedef analog_pin<pin_register_> my_pin;
		private:
			bool IsLock;
			pin_register Pin;
			an_register AN;
			const adc::adc_block_setting* pBlockSetting;
			const adc::adc_setting* pADCSetting;
		private:
			analog_pin(const my_pin&);
			const my_pin& operator=(const my_pin&);
		public:
			analog_pin()
				:IsLock(false), pBlockSetting(0), pADCSetting(0){}
			~analog_pin(){ unlock(); }
			void config(const adc::adc_block_setting* pBlockSetting_, const adc::adc_setting* pADCSetting_){
				pBlockSetting = pBlockSetting_;
				pADCSetting = pADCSetting_;
			}
			bool lock(const adc::adc_block_setting* pBlockSetting_, const adc::adc_setting* pADCSetting_){
				config(pBlockSetting_, pADCSetting_);
				return lock();
			}
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
			uint16 operator()(void){
				xc32_assert(is_lock(), exception(0xE1));

				if(my_converter::start(pBlockSetting, pADCSetting))return 0xFFFF;

				//代替ピンの設定の有無を設定
				my_converter::use_alternative_pin(AN.is_alternative());

				//個別スキャンするチャンネルを設定
				ADC.individual_convert_input_select(analog_no::No);
				__asm("nop");

				//トリガを引く
				my_converter::read_data();

				//スキャン待ち
				while(!AN.data_ready());

				//データを加算
				uint16 Val = AN.data();

				my_converter::stop();

				return Val;
			}
			uint16 operator()(uint16 ObserveNum_){
				xc32_assert(is_lock(), exception(0xE2));

				if(my_converter::start())return 0xFFFF;

				//代替ピンの設定の有無を設定
				my_converter::use_alternative_pin(AN.is_alternative());

				//個別スキャンするチャンネルを設定
				ADC.individual_convert_input_select(analog_no::No);
				__asm("nop");

				uint32 Val = 0;
				for(uint16 ObserveCnt = 0; ObserveCnt<ObserveNum_; ++ObserveCnt){
					//トリガを引く
					my_converter::read_data();

					//スキャン待ち
					while(!AN.data_ready());

					//データを加算
					Val += AN.data();
				}

				my_converter::stop();

				return Val;
			}
		};
	};
	template<typename adc_block_register_, typename identifier_>
	adc_block_register_ shared_adc<adc_block_register_, identifier_>::block::ADC;
	template<typename adc_block_register_, typename identifier_>
	unique_lock<adc_block_register_> shared_adc<adc_block_register_, identifier_>::block::ADCLock(ADC, true);
	template<typename adc_block_register_, typename identifier_>
	unsigned int shared_adc<adc_block_register_, identifier_>::block::LockCnt = 0;
	template<typename adc_block_register_, typename identifier_>
	adc::adc_block_setting shared_adc<adc_block_register_, identifier_>::block::Default;
	template<typename adc_block_register_, typename identifier_>
	const adc::adc_block_setting* shared_adc<adc_block_register_, identifier_>::block::Apply;

	template<typename adc_block_register_, typename identifier_>
	template<typename converter_no_>
	unsigned int shared_adc<adc_block_register_, identifier_>::converter<converter_no_>::LockCnt = 0;
	template<typename adc_block_register_, typename identifier_>
	template<typename converter_no_>
	bool shared_adc<adc_block_register_, identifier_>::block::converter<converter_no_>::IsUsed = false;
	template<typename adc_block_register_, typename identifier_>
	template<typename converter_no_>
	adc::adc_setting shared_adc<adc_block_register_, identifier_>::block::converter<converter_no_>::Default;
	template<typename adc_block_register_, typename identifier_>
	template<typename converter_no_>
	const adc::adc_setting* shared_adc<adc_block_register_, identifier_>::block::converter<converter_no_>::Apply;
	*/

/*
	//非同期型個別コンバートADC
	//	async_adcはshared_adc同様、実体を用意する必要がない。analog_pinからのlock/unclockで適宜初期化/終端化される。
	//	一つのadc_block_registerを一つのasync_functional_adcが排他的に利用する
	//	analog_pinから読みだしても値はその場で読みだされる、futureが戻り値として返される。内部ではqueueにadc用のtaskが積まれる。
	//	機能させるためには、定期的にconverterごとのwork関数を呼び出す必要がある。
	template<typename adc_block_register_, typename identifier_, unsigned int QueueSize_=10>
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
		friend class test_async_functional_adc;
	private:
		typedef adc_block_register_ adc_block_register;
		typedef async_functional_adc<adc_block_register_, identifier_, QueueSize_> my_type;
	private:
		//データリクエスト内容
		struct data_request{
			const adc::adc_block_setting* pBlockSetting;
			const adc::adc_setting* pADCSetting;
			unsigned char Num;
			promise<uint16>& Ref;
			data_request(promise<uint16>& Ref_)
				: Ref(Ref_)
				, VrefMode(xc32::adc::vref_Vref_Gnd)
				, ClockDiv(0)
				, Num(1){
			}
			virtual unsigned char getAN() = 0;
			virtual uint16 read_data() = 0;
		};
		static array_queue<data_request*, QueueSize_> RequestQueue;
	public:
		template<typename pin_register_>
		struct analog_pin {
		private:
//			typedef pin_register_ pin_register;
			typedef typename pin_register_::analog_no analog_no;
			typedef sfr::adc::an<typename pin_register_::analog_no> an_register;
		private:
			struct an_data_request :public data_request{
				an_register AN;
				an_data_request(promise<uint16>& Ref_) :itf_request_data(Ref_){}
				virtual unsigned char getAN(){ return analog_no::No; }
				virtual uint16 read_data(){
					//スキャン待ち
					while (!AN.data_ready());
					//データを加算
					return AN.data();
				}
			}RequestData;
		private:
			typedef pin_register_ pin_register;
			pin_register Pin;
			bool IsLock;
			promise<uint16> Promise;
		public:
			analog_pin()
				: IsLock(false)
				, RequestData(Promise){
			}
			~analog_pin(){ if (is_lock())unlock(); }
			void config(sfr::adc::vref_mode VrefMode_, uint8 ClockDiv_) {
				RequestData.VrefMode = VrefMode_;
				RequestData.ClockDiv = ClockDiv_;
			}
			bool lock(sfr::adc::vref_mode VrefMode_, uint8 ClockDiv_) {
				config(VrefMode_, ClockDiv_);
				return lock();
			}
			bool lock(){
				if (IsLock)return false;

				Pin.tris(true);
				Pin.analog(true);
				Pin.opendrain(false);

				IsLock = true;

				return false;
			}
			bool is_lock()const{ return IsLock; }
			void unlock(){
				Pin.tris(false);
				Pin.analog(false);
				Pin.opendrain(false);

				IsLock = false;
			}
		public:
			future<uint16> operator()(void){
				if (!Promise.can_get_future())return future<uint16>();

				RequestData.Num = 1;
				if(RequestQueue.push(&RequestData))return future<uint16>();

				return Promise.get_future();
			}
			future<uint16> operator()(uint16 ObserveNum_){
				if (!Promise.can_get_future())return future<uint16>();
				if (ObserveNum_ == 0)return future<uint16>();

				if(ObserveNum_ > 0xff)ObserveNum_ = 0xff;
				RequestData.Num = static_cast<unsigned char>(ObserveNum_);
				if (RequestQueue.push(&RequestData))return future<uint16>();

				return Promise.get_future();
			}
		public:
			bool can_get_future()const{return Promise.can_get_future();}
		};
	private:
		adc_block_register ADC;
		unique_lock<adc_block_register> ADCLock;
		adc::vref_mode VrefMode;
		uint8 ClockDiv;
	public:
		async_functional_adc()
			: Request(0)
			, ADCLock(ADC,true){
		}
	private:
		async_functional_adc(const my_type&);
		const my_type& operator=(const my_type&);
	public:
		bool lock(){
			if (is_lock())return false;
			if (ADCLock.lock())return true;

			start();

			return false;
		}
		void unlock(){
			if (!is_lock())return;

			stop();

			ADCLock.unlock();
		}
		bool is_lock()const{return ADCLock;}
	private:
		void start(){
			//参照電圧を設定
			ADC.reference_voltage(VrefMode);
			__asm("nop");
			//クロックをTcyに設定
			ADC.clock_select(1);
			__asm("nop");
			//クロック分周設定(0〜127までなので高位のビットを削除)
			ADC.clock_div((ClockDiv & 0x7F));
			__asm("nop");
			//ADC始動！
			ADC.enable(1);
			__asm("nop");
		}
		void stop(){ ADC.enable(0); }
		void restart(adc::vref_mode VrefMode_, uint8 ClockDiv_){
			if (VrefMode_ == VrefMode && ClockDiv == ClockDiv_)return;

			//一旦停止
			stop();

			//設定書き換え
			VrefMode = VrefMode_;
			ClockDiv = ClockDiv_;

			//スタート
			start();
		}
		bool can_read(){ return ADC.module_ready(); }
		uint16 read(unsigned char No_, itf_request_data* ReqData_, uint16 ObserveNum_){
			if (ObserveNum_ == 0)return 0xffff;

			xc32_assert(ADC.is_lock(),exception(0xE2));

			//チャンネルを設定
			ADC.individual_convert_input_select(No_);

			uint32 Val = 0;
			for (uint16 ObserveCnt = 0; ObserveCnt<ObserveNum_; ++ObserveCnt) {
				__asm("nop");
				//トリガを引く
				ADC.individual_convert(true);

				//データを加算
				Val += ReqData_->read_data();

			}
			return Val/ObserveNum_;
		}
	private:
		itf_request_data* Request;
	public:
		void operator()(void){
			if (!is_lock())return;

			//リクエスト中のデータがある場合
			if (Request != 0){
				if (ADC.module_ready()){
					//Request->Ref.ref() = read(Request->getAN(), Request, Request->Num);
					//Request->Ref.end_write();
					Request->Ref.set_value(read(Request->getAN(), Request, Request->Num));
					Request = 0;

				}
			}

			//リクエスト中のデータがない場合
			if (Request == 0 && !RequestQueue.empty()){
				Request = RequestQueue.next();
				RequestQueue.pop();
				restart(Request->VrefMode, Request->ClockDiv);
			}
		}
	public:
		bool can_request()const{return !RequestQueue.full();}
	};
	template<typename adc_block_register_, unsigned int QueueSize_>
	array_queue<typename async_functional_adc<adc_block_register_, QueueSize_>::itf_request_data*, QueueSize_> async_functional_adc<adc_block_register_, QueueSize_>::RequestQueue;

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
					//クロック分周設定(0〜127までなので高位のビットを削除)
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
					//クロック分周設定(0〜127までなので高位のビットを削除)
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
					//クロック分周設定(0〜127までなので高位のビットを削除)
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
