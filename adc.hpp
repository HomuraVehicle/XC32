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
	namespace adc {
		using namespace sfr::adc;
	}
	//独占型ADC
	//	一つのadc_block_registerを一つのsynchronous_adcが排他的に利用する
	//	synchronous_adc、converterは明示的に使用者が実体を用意し、それぞれをlock/unlockする必要
	//	analog_pinからの読み出しは重複しうるため、利用者が明示的に避ける必要がある
	template<typename adc_block_register_>
	class exclusive_adc{
		typedef adc_block_register_ adc_block_register;
		typedef exclusive_adc<adc_block_register> my_type;
	private:
		adc_block_register ADC;
		unique_lock<adc_block_register> ADCLock;

		sfr::adc::vref_mode VrefMode;
		uint8 ClockDiv;
	public:
		exclusive_adc()
			: ADCLock(ADC, true)
			, VrefMode(sfr::adc::vref_mode::vref_Vref_Gnd)
			, ClockDiv(0){
		}
	private:
		exclusive_adc(const my_type&);
		const my_type& operator=(const my_type&);
	public:
		void config(sfr::adc::vref_mode VrefMode_, uint8 ClockDiv_) {
			VrefMode = VrefMode_;
			ClockDiv = ClockDiv_;
		}
		bool lock(sfr::adc::vref_mode VrefMode_, uint8 ClockDiv_) {
			config(VrefMode_, ClockDiv_);
			return lock();
		}
		bool lock(){
			if (is_lock())return false;
			if (ADCLock.lock())return true;

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

			//self calibration待ち
			while (!ADC.module_ready());

			ADCLock.lock();

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
	private:
		void read_data(){
			//個別スキャン開始
			ADC.individual_convert(true);
			__asm("nop");
		}
	public:
		template<typename converter_no_>
		struct converter{
		private:
			my_type& Ref;
			bool Lock;

			unsigned char ClockDiv;
			unsigned char SamplingTime;
			sfr::adc::resolution_mode ResolutionMode;
		public:
			converter(my_type& Ref_) :Ref(Ref_), LockCnt(0), ClockDiv(1), SamplingTime(0), ResolutionMode(sfr::adc::resolution_12bits){}
			void config(unsigned char ClockDiv_, unsigned char SamplingTime_, sfr::adc::resolution_mode ResolutionMode_){
				ClockDiv = ClockDiv_;
				SamplingTime = SamplingTime_;
				ResolutionMode = ResolutionMode_;
			}
			bool lock(unsigned char ClockDiv_, unsigned char SamplingTime_, sfr::adc::resolution_mode ResolutionMode_){
				config(ClockDiv_, SamplingTime_, ResolutionMode_);
				return lock();
			}
			bool lock(){
				if(Lock)return false;
				Lock = true;

				//メインデバイスがロックされていなければ、初期化作業は失敗
				if(!Ref.ADC.is_lock())return true;

				//スタートアップ処理
				Ref.ADC.adc_clock_div<converter_no_>(ClockDiv);
				Ref.ADC.sampling_time<converter_no_>(SamplingTime);
				Ref.ADC.resolution_bits<converter_no_>(ResolutionMode);

				//ADC 準備を待つ
				Ref.ADC.adc_enable<converter_no_>(true);
				while(!Ref.ADC.adc_ready<converter_no_>());

				Ref.ADC.adc_work_enable<converter_no_>(true);

			}
			void unlock(){
				if(!Lock)return;
				Lock = false;


				//メインデバイスがロックされていなければ、アンロック作業は失敗
				if(!Ref.ADC.is_lock())return;

				Ref.ADC.adc_work_enable<converter_no_>(false);
				Ref.ADC.adc_enable<converter_no_>(false);
			}
			bool is_lock()const{ return Lock; }
			void use_alternative_pin(bool val_){
				Ref.ADC.use_alternative_pin<converter_no_>(val_);
			}
		};
	public:
		template<typename pin_register_>
		class analog_pin{
		private:
			typedef pin_register_ pin_register;
			typedef typename pin_register::analog_no analog_no;
			typedef sfr::adc::an<analog_no> an_register;
			typedef typename an_register::converter_no converter_no;
			typedef converter<converter_no> my_converter;
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

				//トリガを引く
				Ref.read_data();

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
					//トリガを引く
					Ref.ADC.read_data();

					//スキャン待ち
					while (!AN.data_ready());

					//データを加算
					Val += AN.data();
				}

				return Val;
			}
		};
	};

	//共有型のADC
	//	一つのadc_block_registerを複数のshared_adcが共有する
	//	shared_adcは実体を用意する必要がない。analog_pinからのlock/unclockで適宜初期化される。
	//	analog_pinの読み出し処理は重複していないことの確認がなされる。重複時は読みだし失敗となり、0xffffが返る
	template<typename adc_block_register_, typename identifier_>
	class shared_adc{
		typedef shared_adc<adc_block_register_, identifier_> my_type;
	private:
		static adc_block_register_ ADC;
		static unique_lock<adc_block_register_> ADCLock;
	private:
		static unsigned int LockCnt;
		static bool IsUsed;
		static sfr::adc::vref_mode ApplyVrefMode;
		static uint8 ApplyClockDiv;
	private:
		static bool lock(sfr::adc::vref_mode VrefMode_, uint8 ClockDiv_){
			if (++LockCnt == 1){
				if (ADCLock.lock())return true;

				//Applyを更新
				ApplyVrefMode = VrefMode_;
				ApplyClockDiv = ClockDiv_;

				//参照電圧を設定
				ADC.reference_voltage(ApplyVrefMode);
				__asm("nop");
				//クロックをTcyに設定
				ADC.clock_select(1);
				__asm("nop");
				//クロック分周設定(0〜127までなので高位のビットを削除)
				ADC.clock_div((ApplyClockDiv & 0x7F));
				__asm("nop");
				//ADC始動！
				ADC.enable(1);
				__asm("nop");

				//self calibration待ち
				while (!ADC.module_ready());
			}

			return false;
		}
		static void unlock(){
			if (--LockCnt == 0){
				//ADC停止
				ADC.enable(0);

				//ロック解除
				ADCLock.unlock();
			}
		}
		static bool is_lock(){ return LockCnt>0; }
		static bool start(sfr::adc::vref_mode VrefMode_, uint8 ClockDiv_){
			if (IsUsed)return true;
			IsUsed = true;

			//一緒ならパス
			if (ApplyVrefMode == VrefMode_ && ApplyClockDiv == ClockDiv_)return false;

			//一旦ストップ
			ADC.enable(0);

			//Applyを更新
			ApplyVrefMode = VrefMode_;
			ApplyClockDiv = ClockDiv_;

			//再起動
			//参照電圧を設定
			ADC.reference_voltage(ApplyVrefMode);
			__asm("nop");
			//クロックをTcyに設定
			ADC.clock_select(1);
			__asm("nop");
			//クロック分周設定(0〜127までなので高位のビットを削除)
			ADC.clock_div((ApplyClockDiv & 0x7F));
			__asm("nop");
			//ADC始動！
			ADC.enable(1);
			__asm("nop");
			//self calibration待ち
			while (!ADC.module_ready());

			return false;
		}
		static void stop(){
			IsUsed = false;
		}
		static void read_data(){
			ADC.individual_convert(true);
			__asm("nop");
		}
	private:
		template<typename converter_no_>
		struct converter{
		private:
			static unsigned bool LockCnt;

			static unsigned char ClockDiv;
			static unsigned char SamplingTime;
			static sfr::adc::resolution_mode ResolutionMode;
		public:
			static void config(unsigned char ClockDiv_, unsigned char SamplingTime_, sfr::adc::resolution_mode ResolutionMode_){
				ClockDiv = ClockDiv_;
				SamplingTime = SamplingTime_;
				ResolutionMode = ResolutionMode_;
			}
			static bool lock(unsigned char ClockDiv_, unsigned char SamplingTime_, sfr::adc::resolution_mode ResolutionMode_){
				config(ClockDiv_, SamplingTime_, ResolutionMode_);
				return lock();
			}
			static bool lock(){
				if(++LockCnt == 0){
					//メインデバイスがロックされていなければ、初期化作業は失敗
					if(!my_type::ADC.is_lock())return true;

					//スタートアップ処理
					my_type::ADC.adc_clock_div<converter_no_>(ClockDiv);
					my_type::ADC.sampling_time<converter_no_>(SamplingTime);
					my_type::ADC.resolution_bits<converter_no_>(ResolutionMode);

					//ADC 準備を待つ
					my_type::ADC.adc_enable<converter_no_>(true);
					while(!my_type::ADC.adc_ready<converter_no_>());

					my_type::ADC.adc_work_enable<converter_no_>(true);
				}
				
				return false;
			}
			static void unlock(){
				if(--Lock == 0){
					my_type::ADC.adc_work_enable<converter_no_>(false);
					my_type::ADC.adc_enable<converter_no_>(false);
				}
			}
			static bool is_lock()const{ return LockCnt!=0; }
			static void use_alternative_pin(bool val_){
				my_type::ADC.use_alternative_pin<converter_no_>(val_);
			}
		};
	public:
		template<typename pin_register_>
		class analog_pin {
			typedef pin_register_ pin_register;
			typedef typename pin_register::analog_no analog_no;
			typedef sfr::adc::an<typename pin_register_::analog_no> an_register;
			typedef typename an_register::converter_no converter_no;
			typedef converter<converter_no> my_converter;
			typedef analog_pin<pin_register_> my_pin;
		private:
			bool IsLock;
			pin_register Pin;
			an_register AN;
			sfr::adc::vref_mode VrefMode;
			uint8 ClockDiv;
		private:
			analog_pin(const my_pin&);
			const my_pin& operator()(const my_pin&);
		public:
			analog_pin()
				:IsLock(false){
			}
			~analog_pin() { unlock(); }
			bool lock() {
				if (is_lock())return false;

				if (my_type::lock(VrefMode, ClockDiv))return true;

				if(my_converter::lock(ConverterClockDiv, SamplingTime, ResolutionMode))return true;

				Pin.tris(true);
				Pin.analog(true);
				Pin.opendrain(false);

				IsLock = true;
				return false;
			}
			bool is_lock()const {
				return IsLock;
			}
			void unlock() {
				if (!is_lock())return;

				Pin.tris(false);
				Pin.analog(false);
				Pin.opendrain(false);

				my_type::unlock();

				IsLock = false;
			}
		public:
			uint16 operator()(void){
				xc32_assert(is_lock(), exception(0xE1));

				if(my_type::start())return 0xFFFF;


				//代替ピンの設定の有無を設定
				my_converter::use_alternative_pin(AN.is_alternative());

				//個別スキャンするチャンネルを設定
				ADC.individual_convert_input_select(analog_no::No);
				__asm("nop");

				//トリガを引く
				my_type::read_data();

				//スキャン待ち
				while (!AN.data_ready());

				//データを加算
				uint16 Val = AN.data();

				my_type::stop();

				return Val;
			}
			uint16 operator()(uint16 ObserveNum_){
				xc32_assert(is_lock(), exception(0xE2));

				if (my_type::start())return 0xFFFF;

				//代替ピンの設定の有無を設定
				my_converter::use_alternative_pin(AN.is_alternative());

				//個別スキャンするチャンネルを設定
				ADC.individual_convert_input_select(analog_no::No);
				__asm("nop");

				uint32 Val = 0;
				for (uint16 ObserveCnt = 0; ObserveCnt<ObserveNum_; ++ObserveCnt) {
					//トリガを引く
					my_type::ADC.read_data();

					//スキャン待ち
					while (!AN.data_ready());

					//データを加算
					Val += AN.data();
				}

				my_type::stop();

				return Val;
			}
		};
	};
	template<typename adc_block_register_, typename identifier_>
	adc_block_register_ shared_adc<adc_block_register_, identifier_>::ADC;
	template<typename adc_block_register_, typename identifier_>
	unique_lock<adc_block_register_> shared_adc<adc_block_register_, identifier_>::ADCLock(ADC, true);
	template<typename adc_block_register_, typename identifier_>
	bool shared_adc<adc_block_register_, identifier_>::IsUsed = false;
	template<typename adc_block_register_, typename identifier_>
	unsigned int shared_adc<adc_block_register_, identifier_>::LockCnt = 0;
	template<typename adc_block_register_, typename identifier_>
	sfr::adc::vref_mode shared_adc<adc_block_register_, identifier_>::ApplyVrefMode;
	template<typename adc_block_register_, typename identifier_>
	uint8 shared_adc<adc_block_register_, identifier_>::ApplyClockDiv;
	template<typename adc_block_register_, typename identifier_>
	template<typename converter_no_>
	unsigned bool shared_adc<adc_block_register_, identifier_>::converter<converter_no_>::LockCnt = 0;
	template<typename adc_block_register_, typename identifier_>
	template<typename converter_no_>
	unsigned bool shared_adc<adc_block_register_, identifier_>::converter<converter_no_>::ClockDiv = 1;
	template<typename adc_block_register_, typename identifier_>
	template<typename converter_no_>
	unsigned bool shared_adc<adc_block_register_, identifier_>::converter<converter_no_>::SamplingTime = 0;
	template<typename adc_block_register_, typename identifier_>
	template<typename converter_no_>
	sfr::adc::resolution_mode shared_adc<adc_block_register_, identifier_>::converter<converter_no_>::ResolutionMode = sfr::adc::resolution_12bits;

	//非同期型のADC
	//	一つのadc_block_registerを一つのasync_functional_adcが排他的に利用する
	//	analog_pinから読みだしても値はその場で読みだされる、futureが戻り値として返される
	//	同時に、内部ではqueueにadc用のtaskが積まれ、operator()(void)の実行時に順次処理される
	//	queueで明示的に処理の重複を阻害している
	template<typename adc_block_register_,unsigned int QueueSize_=10>
	class async_functional_adc{
		friend class test_async_functional_adc;
	private:
		typedef adc_block_register_ adc_block_register;
		typedef async_functional_adc<adc_block_register_> my_type;
	private:
		struct itf_request_data{
			adc::vref_mode VrefMode;
			uint8 ClockDiv;
			unsigned char Num;
			promise<uint16>& Ref;
			itf_request_data(promise<uint16>& Ref_)
				: Ref(Ref_)
				, VrefMode(xc32::adc::vref_Vref_Gnd)
				, ClockDiv(0)
				, Num(1){
			}
			virtual unsigned char getAN() = 0;
			virtual uint16 read_data() = 0;
		};
		static array_queue<itf_request_data*, QueueSize_> RequestQueue;
	public:
		template<typename pin_register_>
		struct analog_pin {
		private:
//			typedef pin_register_ pin_register;
			typedef typename pin_register_::analog_no analog_no;
			typedef sfr::adc::an<typename pin_register_::analog_no> an_register;
		private:
			struct request_data:public itf_request_data{
				an_register AN;
				request_data(promise<uint16>& Ref_) :itf_request_data(Ref_){}
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
}
#
#endif
