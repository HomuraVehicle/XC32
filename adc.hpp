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
	//�Ɛ�^ADC
	//	���adc_block_register�����synchronous_adc���r���I�ɗ��p����
	//	synchronous_adc�Aconverter�͖����I�Ɏg�p�҂����̂�p�ӂ��A���ꂼ���lock/unlock����K�v
	//	analog_pin����̓ǂݏo���͏d�������邽�߁A���p�҂������I�ɔ�����K�v������
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

				//���C���f�o�C�X�����b�N����Ă��Ȃ���΁A��������Ƃ͎��s
				if(!Ref.ADC.is_lock())return true;

				//�X�^�[�g�A�b�v����
				Ref.ADC.adc_clock_div<converter_no_>(ClockDiv);
				Ref.ADC.sampling_time<converter_no_>(SamplingTime);
				Ref.ADC.resolution_bits<converter_no_>(ResolutionMode);

				//ADC ������҂�
				Ref.ADC.adc_enable<converter_no_>(true);
				while(!Ref.ADC.adc_ready<converter_no_>());

				Ref.ADC.adc_work_enable<converter_no_>(true);

			}
			void unlock(){
				if(!Lock)return;
				Lock = false;


				//���C���f�o�C�X�����b�N����Ă��Ȃ���΁A�A�����b�N��Ƃ͎��s
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

				//��փs���̐ݒ�̗L����ݒ�
				Converter.use_alternative_pin(AN.is_alternative());

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

				//��փs���̐ݒ�̗L����ݒ�
				Converter.use_alternative_pin(AN.is_alternative());

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

	namespace adc{
		struct adc_block_setting{
			sfr::adc::vref_mode VrefMode;
			unsigned char ClockDiv;
			adc_block_setting() :VrefMode(sfr::adc::vref_Vref_Gnd), ClockDiv(0){}
		};
		struct adc_setting{
			unsigned char ClockDiv;
			unsigned char SamplingTime;
			sfr::adc::resolution_mode ResolutionMode;
			adc_setting() : ClockDiv(1), SamplingTime(0), ResolutionMode(sfr::adc::resolution_12bits){}
		};
	}
	//���L�^��ADC
	//	���adc_block_register�𕡐���shared_adc�����L����
	//	shared_adc�͎��̂�p�ӂ���K�v���Ȃ��Banalog_pin�����lock/unclock�œK�X�����������B
	//	analog_pin�̓ǂݏo�������͏d�����Ă��Ȃ����Ƃ̊m�F���Ȃ����B�d�����͓ǂ݂������s�ƂȂ�A0xffff���Ԃ�
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

					//�Q�Ɠd����ݒ�
					ADC.reference_voltage(Default.VrefMode);
					__asm("nop");
					//�N���b�N��Tcy�ɐݒ�
					ADC.clock_select(1);
					__asm("nop");
					//�N���b�N�����ݒ�(0�`127�܂łȂ̂ō��ʂ̃r�b�g���폜)
					ADC.clock_div((Default.ClockDiv & 0x7F));
					__asm("nop");
					//ADC�n���I
					ADC.enable(1);
					__asm("nop");

					//self calibration�҂�
					while(!ADC.module_ready());
				}

				return false;
			}
			static void unlock(){
				if(--LockCnt == 0){
					//ADC��~
					ADC.enable(0);

					//���b�N����
					ADCLock.unlock();
				}
			}
			static bool is_lock(){ return LockCnt>0; }
			//�ċN������true��Ԃ�
			static bool start(const adc::adc_block_setting* pSetting, bool ForceReset = false){
				//�ꏏ�Ȃ�p�X
				if(pSetting == Apply && !ForceReset)return false;

				//��U�X�g�b�v
				ADC.enable(0);

				if(pSetting == 0){
					//�Q�Ɠd����ݒ�
					ADC.reference_voltage(Default.VrefMode);
					__asm("nop");
					//�N���b�N��Tcy�ɐݒ�
					ADC.clock_select(1);
					__asm("nop");
					//�N���b�N�����ݒ�(0�`127�܂łȂ̂ō��ʂ̃r�b�g���폜)
					ADC.clock_div((Default.ClockDiv & 0x7F));
					__asm("nop");
					Apply = 0;
				} else{
					//�Q�Ɠd����ݒ�
					ADC.reference_voltage(Apply->VrefMode);
					__asm("nop");
					//�N���b�N��Tcy�ɐݒ�
					ADC.clock_select(1);
					__asm("nop");
					//�N���b�N�����ݒ�(0�`127�܂łȂ̂ō��ʂ̃r�b�g���폜)
					ADC.clock_div((Apply->ClockDiv & 0x7F));
					__asm("nop");
					Apply = pSetting;
				}

				//ADC�Ďn��
				ADC.enable(1);
				__asm("nop");
				//self calibration�҂�
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

					//���łɃ��b�N���ċN���ς݂Ȃ�A�����I��Default�ōċN��
					if(is_lock() && Apply == 0){
						start(0, 0, true);
						stop();
					}
				}
				static void set_default(const adc::adc_setting& Setting){
					Default = Setting;

					//���łɃ��b�N���ċN���ς݂Ȃ�A�����I��Default�ōċN��
					if(is_lock() && Apply == 0){
						Apply = reinterpret_cast<const adc::adc_setting*>(1);
						start(0, 0);
						stop();
					}
				}
				static bool lock(){
					//adc_block�����b�N
					if(block::lock())return true;

					if(++LockCnt == 0){
						//�X�^�[�g�A�b�v����
						block::ADC.adc_clock_div<converter_no_>(Default.ClockDiv);
						block::ADC.sampling_time<converter_no_>(Default.SamplingTime);
						block::ADC.resolution_bits<converter_no_>(Default.ResolutionMode);
						Apply = 0;

						//ADC ������҂�
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

					//adc_block���A�����b�N
					block::unlock();
				}
				static bool is_lock()const{ return LockCnt != 0; }
				static void use_alternative_pin(bool val_){
					block::ADC.use_alternative_pin<converter_no_>(val_);
				}
				//���s�����ꍇ��true��Ԃ�
				//block��start�Ɩ߂�l�̈Ӗ����Ⴄ�̂Œ���
				static bool start(const adc::adc_block_setting* pBlockSetting, const adc::adc_setting* pSetting, bool ForceReset = false){
					if(IsUsed)return true;
					IsUsed = true;

					//�ċN�����K�v�Ȑݒ肾�����ꍇ�́A������������I�ɍċN��
					ForceReset = block::start(pBlockSetting, ForceReset);

					//�ꏏ�Ȃ�p�X
					if(pSetting == Apply && !ForceReset)return false;

					//��U�X�g�b�v
					block::ADC.adc_work_enable<converter_no_>(false);
					block::ADC.adc_enable<converter_no_>(false);

					//�X�^�[�g�A�b�v����
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

					//ADC ������҂�
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
			uint16 operator()(void){
				xc32_assert(is_lock(), exception(0xE1));

				if(my_converter::start(pBlockSetting, pADCSetting))return 0xFFFF;

				//��փs���̐ݒ�̗L����ݒ�
				my_converter::use_alternative_pin(AN.is_alternative());

				//�ʃX�L��������`�����l����ݒ�
				ADC.individual_convert_input_select(analog_no::No);
				__asm("nop");

				//�g���K������
				my_converter::read_data();

				//�X�L�����҂�
				while(!AN.data_ready());

				//�f�[�^�����Z
				uint16 Val = AN.data();

				my_converter::stop();

				return Val;
			}
			uint16 operator()(uint16 ObserveNum_){
				xc32_assert(is_lock(), exception(0xE2));

				if(my_converter::start())return 0xFFFF;

				//��փs���̐ݒ�̗L����ݒ�
				my_converter::use_alternative_pin(AN.is_alternative());

				//�ʃX�L��������`�����l����ݒ�
				ADC.individual_convert_input_select(analog_no::No);
				__asm("nop");

				uint32 Val = 0;
				for(uint16 ObserveCnt = 0; ObserveCnt<ObserveNum_; ++ObserveCnt){
					//�g���K������
					my_converter::read_data();

					//�X�L�����҂�
					while(!AN.data_ready());

					//�f�[�^�����Z
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

	//�񓯊��^��ADC
	//	���adc_block_register�����async_functional_adc���r���I�ɗ��p����
	//	analog_pin����ǂ݂����Ă��l�͂��̏�œǂ݂������Afuture���߂�l�Ƃ��ĕԂ����
	//	�����ɁA�����ł�queue��adc�p��task���ς܂�Aoperator()(void)�̎��s���ɏ������������
	//	queue�Ŗ����I�ɏ����̏d����j�Q���Ă���
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
	template<typename adc_block_register_, unsigned int QueueSize_>
	array_queue<typename async_functional_adc<adc_block_register_, QueueSize_>::itf_request_data*, QueueSize_> async_functional_adc<adc_block_register_, QueueSize_>::RequestQueue;
}
#
#endif
