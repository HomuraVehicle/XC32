#ifndef XC32LIB_ADC_INC
#define XC32LIB_ADC_INC 100
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
	//�����^ADC
	//	ADC��Ref�ŕ�����analog_pin���痘�p����
	//	ADC��lock/unlock��enable/disable�����s�����
	template<typename adc_register_>
	class synchronous_adc{
		typedef adc_register_ adc_register;
		typedef synchronous_adc<adc_register> my_type;
	private:
		adc_register ADC;
		unique_lock<adc_register> ADCLock;

		sfr::adc::vref_mode VrefMode;
		uint8 ClockDiv;
	public:
		synchronous_adc()
			: ADCLock(ADC, true)
			, VrefMode(sfr::adc::vref_mode::vref_Vref_Gnd)
			, ClockDiv(0){
		}
	private:
		synchronous_adc(const my_type&);
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

			//�Q�Ɠd����ݒ�
			ADC.reference_voltage(VrefMode);
			__asm("nop");
			//�N���b�N��Tcy�ɐݒ�
			ADC.clock_select(1);
			__asm("nop");
			//�N���b�N�����ݒ�(0�`127�܂łȂ̂ō��ʂ̃r�b�g���폜)
			ADC.clock_div((ClockDiv & 0x7F));
			__asm("nop");
			//ADC�n���I
			ADC.enable(1);
			__asm("nop");
			//self calibration�҂�
			while (!ADC.module_ready());

			ADCLock.lock();

			return false;
		}
		void unlock(){
			if (!is_lock())return;

			//ADC�𗎂Ƃ��I
			ADC.enable(0);

			ADCLock.unlock();
		}
		bool is_lock()const{
			return ADCLock;
		}
	private:
		void read_data(){
			//�ʃX�L�����J�n
			ADC.individual_convert(true);
			__asm("nop");
		}
	public:
		template<typename pin_register_>
		class analog_pin{
		private:
			typedef pin_register_ pin_register;
			typedef typename pin_register::analog_no analog_no;
			typedef sfr::adc::an<analog_no> an_register;
			typedef analog_pin<pin_register_> my_pin;
		private:
			pin_register Pin;
			an_register AN;
			my_type& Ref;
			bool Lock;
		private:
			analog_pin(const my_pin&);
			const my_pin& operator()(const my_pin&);
		public:
			analog_pin(my_type& Ref_):Ref(Ref_){}
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

				//�`�����l����ݒ�
				Ref.ADC.individual_convert_input_select(analog_no::No);

				//�g���K������
				Ref.read_data();

				//�X�L�����҂�
				while (!AN.data_ready());

				//�f�[�^�����Z
				uint16 Val = AN.data();

				return Val;
			}
			uint16 operator()(uint16 ObserveNum_){
				xc32_assert(is_lock(), exception(0xE2));

				//�`�����l����ݒ�
				Ref.ADC.individual_convert_input_select(analog_no::No);

				uint32 Val = 0;
				for (uint16 ObserveCnt = 0; ObserveCnt < ObserveNum_; ++ObserveCnt) {
					//�g���K������
					Ref.ADC.read_data();

					//�X�L�����҂�
					while (!AN.data_ready());

					//�f�[�^�����Z
					Val += AN.data();
				}

				return Val;
			}
		};
	};

	//���L�^��ADC
	//	������analog_pin�̊ԂŁA���adc�����L����
	//	���ׂĂ�lock���������ꂽ�Ƃ���disable�ɂȂ�
	template<typename adc_register_, typename identifier_>
	class shared_adc{
		typedef shared_adc<adc_register_, identifier_> my_type;
	private:
		static adc_register_ ADC;
		static unique_lock<adc_register_> ADCLock;
	private:
		static unsigned int LockCnt;
		static bool IsUsed;
		static sfr::adc::vref_mode ApplyVrefMode;
		static uint8 ApplyClockDiv;
	public:
		static bool lock(sfr::adc::vref_mode VrefMode_, uint8 ClockDiv_){
			if (++LockCnt == 1){
				if (ADCLock.lock())return true;

				ApplyVrefMode = VrefMode_;
				ApplyClockDiv = ClockDiv_;

				//�Q�Ɠd����ݒ�
				ADC.reference_voltage(ApplyVrefMode);
				__asm("nop");
				//�N���b�N��Tcy�ɐݒ�
				ADC.clock_select(1);
				__asm("nop");
				//�N���b�N�����ݒ�(0�`127�܂łȂ̂ō��ʂ̃r�b�g���폜)
				ADC.clock_div((ApplyClockDiv & 0x7F));
				__asm("nop");
				//ADC�n���I
				ADC.enable(1);
				__asm("nop");

				//self calibration�҂�
				while (!ADC.module_ready());
			}

			return false;
		}
		static void unlock(){
			if (--LockCnt == 0){
				//ADC��~
				ADC.enable(0);

				//���b�N����
				ADCLock.unlock();
			}
		}
		static bool is_lock(){ return LockCnt>0; }
		static bool start(sfr::adc::vref_mode VrefMode_, uint8 ClockDiv_){
			if (IsUsed)return true;
			IsUsed = true;

			//�ꏏ�Ȃ�p�X
			if (ApplyVrefMode == VrefMode_ && ApplyClockDiv == ClockDiv_)return false;

			//��U�X�g�b�v
			ADC.enable(0);

			//Apply���X�V
			ApplyVrefMode = VrefMode_;
			ApplyClockDiv = ClockDiv_;

			//�ċN��
			//�Q�Ɠd����ݒ�
			ADC.reference_voltage(ApplyVrefMode);
			__asm("nop");
			//�N���b�N��Tcy�ɐݒ�
			ADC.clock_select(1);
			__asm("nop");
			//�N���b�N�����ݒ�(0�`127�܂łȂ̂ō��ʂ̃r�b�g���폜)
			ADC.clock_div((ApplyClockDiv & 0x7F));
			__asm("nop");
			//ADC�n���I
			ADC.enable(1);
			__asm("nop");
			//self calibration�҂�
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
	public:
		template<typename pin_register_>
		class analog_pin {
			typedef pin_register_ pin_register;
			typedef typename pin_register::analog_no analog_no;
			typedef sfr::adc::an<typename pin_register_::analog_no> an_register;
		private:
			bool IsLock;
			pin_register Pin;
			an_register AN;
			sfr::adc::vref_mode VrefMode;
			uint8 ClockDiv;
		public:
			analog_pin()
				:IsLock(false){
			}
			~analog_pin() { unlock(); }
			void config(sfr::adc::vref_mode VrefMode_, uint8 ClockDiv_) {
				VrefMode = VrefMode_;
				ClockDiv = ClockDiv_;
			}
			bool lock(sfr::adc::vref_mode VrefMode_, uint8 ClockDiv_) {
				config(VrefMode_, ClockDiv_);
				return lock();
			}
			bool lock() {
				if (is_lock())return false;

				if (my_type::lock(VrefMode, ClockDiv))return true;

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


				//�ʃX�L��������`�����l����ݒ�
				ADC.individual_convert_input_select(analog_no::No);
				__asm("nop");

				//�g���K������
				my_type::read_data();

				//�X�L�����҂�
				while (!AN.data_ready());

				//�f�[�^�����Z
				uint16 Val = AN.data();

				my_type::stop();

				return Val;
			}
			uint16 operator()(uint16 ObserveNum_){
				xc32_assert(is_lock(), exception(0xE2));

				if (my_type::start())return 0xFFFF;

				//�ʃX�L��������`�����l����ݒ�
				ADC.individual_convert_input_select(analog_no::No);
				__asm("nop");

				uint32 Val = 0;
				for (uint16 ObserveCnt = 0; ObserveCnt<ObserveNum_; ++ObserveCnt) {
					//�g���K������
					my_type::ADC.read_data();

					//�X�L�����҂�
					while (!AN.data_ready());

					//�f�[�^�����Z
					Val += AN.data();
				}

				my_type::stop();

				return Val;
			}
		};
	};
	template<typename adc_register_, typename identifier_>
	adc_register_ shared_adc<adc_register_, identifier_>::ADC;
	template<typename adc_register_, typename identifier_>
	unique_lock<adc_register_> shared_adc<adc_register_, identifier_>::ADCLock(ADC, true);
	template<typename adc_register_, typename identifier_>
	bool shared_adc<adc_register_, identifier_>::IsUsed = false;
	template<typename adc_register_, typename identifier_>
	unsigned int shared_adc<adc_register_, identifier_>::LockCnt = 0;
	template<typename adc_register_, typename identifier_>
	sfr::adc::vref_mode shared_adc<adc_register_, identifier_>::ApplyVrefMode;
	template<typename adc_register_, typename identifier_>
	uint8 shared_adc<adc_register_, identifier_>::ApplyClockDiv;

/*	template<typename adc_register_, typename identifier_>
	adc_register_ shared_adc<adc_register_, identifier_>::ADC;
	template<typename adc_register_, unsigned int shared_adc_ch_>
	unique_lock<adc_register_> shared_adc<adc_register_, shared_adc_ch_>::ADCLock(ADC, true);
	template<typename adc_register_, unsigned int shared_adc_ch_>
	bool shared_adc<adc_register_, shared_adc_ch_>::IsUsed = false;
	template<typename adc_register_, unsigned int shared_adc_ch_>
	unsigned int shared_adc<adc_register_, shared_adc_ch_>::LockCnt = 0;
	template<typename adc_register_, unsigned int shared_adc_ch_>
	sfr::adc::vref_mode shared_adc<adc_register_, shared_adc_ch_>::ApplyVrefMode;
	template<typename adc_register_, unsigned int shared_adc_ch_>
	uint8 shared_adc<adc_register_, shared_adc_ch_>::ApplyClockDiv;
*/
	//�񓯊��^��ADC
	//	analog_pin����ǂ݂����ƁA���̏�Ŏ��s�͂��ꂸ�Aqueue��adc�p��task���ς܂��
	//	adc��operator()�Ő������������s���ꎟ��Afuture�ɑ΂��Ēl���Ԃ����
	template<typename adc_register_,unsigned int QueueSize_=10>
	class async_functional_adc{
		friend class test_async_functional_adc;
	private:
		typedef adc_register_ adc_register;
		typedef async_functional_adc<adc_register_> my_type;
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
					//�X�L�����҂�
					while (!AN.data_ready());
					//�f�[�^�����Z
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
		adc_register ADC;
		unique_lock<adc_register> ADCLock;
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
			//�Q�Ɠd����ݒ�
			ADC.reference_voltage(VrefMode);
			__asm("nop");
			//�N���b�N��Tcy�ɐݒ�
			ADC.clock_select(1);
			__asm("nop");
			//�N���b�N�����ݒ�(0�`127�܂łȂ̂ō��ʂ̃r�b�g���폜)
			ADC.clock_div((ClockDiv & 0x7F));
			__asm("nop");
			//ADC�n���I
			ADC.enable(1);
			__asm("nop");
		}
		void stop(){ ADC.enable(0); }
		void restart(adc::vref_mode VrefMode_, uint8 ClockDiv_){
			if (VrefMode_ == VrefMode && ClockDiv == ClockDiv_)return;

			//��U��~
			stop();

			//�ݒ菑������
			VrefMode = VrefMode_;
			ClockDiv = ClockDiv_;

			//�X�^�[�g
			start();
		}
		bool can_read(){ return ADC.module_ready(); }
		uint16 read(unsigned char No_, itf_request_data* ReqData_, uint16 ObserveNum_){
			if (ObserveNum_ == 0)return 0xffff;

			xc32_assert(ADC.is_lock(),exception(0xE2));

			//�`�����l����ݒ�
			ADC.individual_convert_input_select(No_);

			uint32 Val = 0;
			for (uint16 ObserveCnt = 0; ObserveCnt<ObserveNum_; ++ObserveCnt) {
				__asm("nop");
				//�g���K������
				ADC.individual_convert(true);

				//�f�[�^�����Z
				Val += ReqData_->read_data();

			}
			return Val/ObserveNum_;
		}
	private:
		itf_request_data* Request;
	public:
		void operator()(void){
			if (!is_lock())return;

			//���N�G�X�g���̃f�[�^������ꍇ
			if (Request != 0){
				if (ADC.module_ready()){
					//Request->Ref.ref() = read(Request->getAN(), Request, Request->Num);
					//Request->Ref.end_write();
					Request->Ref.set_value(read(Request->getAN(), Request, Request->Num));
					Request = 0;

				}
			}

			//���N�G�X�g���̃f�[�^���Ȃ��ꍇ
			if (Request == 0 && !RequestQueue.empty()){
				Request = RequestQueue.next();
				RequestQueue.pop();
				restart(Request->VrefMode, Request->ClockDiv);
			}
		}
	public:
		bool can_request()const{return !RequestQueue.full();}
	};
	template<typename adc_register_, unsigned int QueueSize_>
	array_queue<typename async_functional_adc<adc_register_, QueueSize_>::itf_request_data*, QueueSize_> async_functional_adc<adc_register_, QueueSize_>::RequestQueue;
}
#
#endif
