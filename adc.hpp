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
		//adc_block�p�ݒ�N���X
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
		//adc_converter�p�ݒ�N���X
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

	//�����^�Ɛ�ADC
	//	exclusive_adc�͖����I�Ɏg�p�҂����̂�p�ӂ��A���ꂼ���lock/unlock����K�v������^�C�v�B
	//	���p���ɂ́A�܂�exclusive_adc�̎��̂�p�ӂ��A����converter��p�ӂ��A���̂�����analog_pin����ǂݏo���������s���B
	//	�p�ӂ���Ă���@�\�͍ŏ����Banalog_pin���痘�p����ۂ�converter�̋����`�F�b�N��lock�ς݂��ǂ����̊m�F����s��Ȃ��B
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
		//�R�s�[�֎~
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

			//��x���ׂĐݒ���N���A����
			ADC.reset_all_config();
			
			//�Q�Ɠd����ݒ�
			ADC.reference_voltage(BlockSetting.VrefMode);
			__asm("nop");
			//�N���b�N��Tcy�ɐݒ�
			ADC.clock_select(1);
			__asm("nop");
			//�N���b�N�����ݒ�(0�`127�܂łȂ̂ō��ʂ̃r�b�g���폜)
			ADC.clock_div((BlockSetting.ClockDiv & 0x7F));
			__asm("nop");
			//ADC�n���I
			ADC.enable(1);
			__asm("nop");

			//self calibration�҂�
			while (!ADC.module_ready());

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
	public:
		//�R���o�[�^�[�@Pin���ƂɌq�����Ă���R���o�[�^�[�͈قȂ�_�ɒ���
		template<typename converter_no_>
		struct converter{
		private:
			my_type& Ref;
			bool Lock;

			adc::converter_setting ConverterSetting;
		public:
			converter(my_type& Ref_) :Ref(Ref_), Lock(false){}
		private:
			//�R�s�[�֎~
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

				//���C���f�o�C�X�����b�N����Ă��Ȃ���΁A��������Ƃ͎��s
				if(!Ref.ADC.is_lock()){
					Lock = false;
					return true;
				}

				//�X�^�[�g�A�b�v����
				Ref.ADC.template converter_clock_div<converter_no_>(ConverterSetting.ClockDiv);
				Ref.ADC.template converter_sampling_time<converter_no_>(ConverterSetting.SamplingTime);
				Ref.ADC.template converter_resolution_bits<converter_no_>(ConverterSetting.ResolutionMode);
				//ADC ������҂�
				Ref.ADC.template converter_enable<converter_no_>(true);
				while(!Ref.ADC.template converter_work_ready<converter_no_>());

				Ref.ADC.template converter_work_enable<converter_no_>(true);

				return false;
			}
			void unlock(){
				if(!Lock)return;
				Lock = false;


				//���C���f�o�C�X�����b�N����Ă��Ȃ���΁A�A�����b�N��Ƃ͎��s
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

				//��փs���̐ݒ�̗L����ݒ�
				Converter.use_alternative_pin(AN.is_alternative());

				//�`�����l����ݒ�
				Ref.ADC.individual_convert_select(analog_no::No);

				//�ʃX�L�����J�n
				Ref.ADC.individual_convert_trigger(true);
				__asm("nop");

				//�X�L�����҂�
				while (!AN.data_ready());

				//�f�[�^�����Z
				uint16 Val = AN.data();

				return Val;
			}
			uint16 operator()(uint16 ObserveNum_){
				xc32_assert(is_lock(), exception(0xE2));
				//xc32_assert(ObserveNum_ >= 0);

				//��փs���̐ݒ�̗L����ݒ�
				Converter.use_alternative_pin(AN.is_alternative());

				//�`�����l����ݒ�
				Ref.ADC.individual_convert_select(analog_no::No);

				uint32 Val = 0;
				for (uint16 ObserveCnt = 0; ObserveCnt < ObserveNum_; ++ObserveCnt) {
					//�ʃX�L�����J�n
					Ref.ADC.individual_convert_trigger(true);
					__asm("nop");

					//�X�L�����҂�
					while (!AN.data_ready());

					//�f�[�^�����Z
					Val += AN.data();
				}

				return Val/ObserveNum_;
			}
		};
	};

	//���ׂĂ̋��L�^ADC�̊�{�ƂȂ�A�������Ǘ��������ǂ�N���X
	template<typename adc_block_register_, typename identifier_>
	class basic_shared_adc{
		typedef basic_shared_adc<adc_block_register_, identifier_> my_type;
	public:
		template<typename converter_no_>
		struct converter;

		struct block{
			template<typename> friend struct converter;
		private:
			adc_block_register_ ADC;
			unique_lock<adc_block_register_> ADCLock;
		private:
			unsigned int LockCnt;
			bool IsGlobalConvert;
			adc::block_setting Setting;
		public:
			block():ADCLock(ADC), LockCnt(0), IsGlobalConvert(false), Setting(){}
		public:
			void config(const adc::block_setting& Setting_, bool IsGlobalConvert_=false){
				Setting = Setting_;
				IsGlobalConvert = IsGlobalConvert_;
			}
			bool lock(const adc::block_setting& Setting_, bool IsGlobalConvert_ = false){
				config(Setting_, IsGlobalConvert_);
				return lock();
			}
			bool lock(){
				if(++LockCnt == 1){
					if(ADCLock.lock()){
						//Lock�Ɏ��s������߂��Ă���I���
						LockCnt = 0;
						return true;
					}

					//��x���ׂĐݒ���N���A����
					ADC.reset_all_config();

					//�Q�Ɠd����ݒ�
					ADC.reference_voltage(Setting.VrefMode);
					__asm("nop");
					//�N���b�N��Tcy�ɐݒ�
					ADC.clock_select(1);
					__asm("nop");
					//�N���b�N�����ݒ�(0�`127�܂łȂ̂ō��ʂ̃r�b�g���폜)
					ADC.clock_div((Setting.ClockDiv & 0x7F));
					__asm("nop");

					//Global Convert Mode�p�ݒ�
					if(IsGlobalConvert)ADC.scan_trigger_select(1);
					__asm("nop");

					//ADC�n���I
					ADC.enable(1);
					__asm("nop");

					//self calibration�҂�
					while(!ADC.module_ready());
				}

				return false;
			}
			void unlock(){
				if(LockCnt == 0)return;

				if(--LockCnt == 0){
					//ADC��~
					ADC.enable(0);

					//���b�N����
					ADCLock.unlock();
				}
			}
			bool is_lock(){ return LockCnt > 0; }
			bool relock(const adc::block_setting& Setting_, bool ForceReset = false){
				//�ꏏ�Ȃ�p�X
				if(Setting == Setting_ && !ForceReset)return true;

				//��U�X�g�b�v
				ADC.enable(0);

				//�ݒ�X�V
				Setting = Setting_;

				//�Q�Ɠd����ݒ�
				ADC.reference_voltage(Setting.VrefMode);
				__asm("nop");
				//�N���b�N��Tcy�ɐݒ�
				ADC.clock_select(1);
				__asm("nop");
				//�N���b�N�����ݒ�(0�`127�܂łȂ̂ō��ʂ̃r�b�g���폜)
				ADC.clock_div((Setting.ClockDiv & 0x7F));
				__asm("nop");

				//Global Convert Mode�p�ݒ�
				if(IsGlobalConvert)ADC.scan_trigger_select(1);
				__asm("nop");

				//ADC�n���I
				ADC.enable(1);
				__asm("nop");

				//self calibration�҂�
				while(!ADC.module_ready());

				//ADC�Ďn��
				ADC.enable(1);
				__asm("nop");
				//self calibration�҂�
				while(!ADC.module_ready());

				return false;
			}
			unsigned int use_count()const{ return LockCnt; }
		public:
			void individual_convert_select(unsigned char no){
				ADC.individual_convert_select(no);
				__asm("nop");
			}
			void individual_convert_trigger(){
				ADC.individual_convert_trigger(true);
				__asm("nop");
			}
			//�X�L�����g���K���I���r�b�g,0:�g���K�Ȃ�,1:�O���[�o���\�t�g�E�F�A�g���K,�c
			void scan_trigger_select(unsigned char val_){ADC.scan_trigger_select(val_);}
			//�O���[�o���\�t�g�E�F�A�g���K�r�b�g
			void global_convert_trigger(){ ADC.global_convert_trigger(); }
			//��ăX�L�����iGlobal Scan�j���I���������@�ǂ݂����Ǝ����I�ɗ�����
			bool is_end_global_convert()const volatile{ return ADC.is_end_global_convert(); }
			//��ăX�L�����ɓo�^�����`�����l�������Z�b�g
			void reset_request_global_convert(){
				ADC.reset_request_global_convert();
			}
		};
		static block Block;
	public:
		template<typename converter_no_>
		struct converter{
		private:
			bool IsUsed;
			bool IsGlobalConvert;
			unsigned int LockCnt;
			adc::converter_setting Setting;
		public:
			converter():IsUsed(false), IsGlobalConvert(false), LockCnt(0), Setting(){}
		public:
			void config(const adc::converter_setting& Setting_, bool IsGlobalConvert_ = false){
				Setting = Setting_;
				IsGlobalConvert = IsGlobalConvert_;
			}
			bool lock(const adc::converter_setting& Setting_, bool IsGlobalConvert_ = false){
				config(Setting_, IsGlobalConvert_);
				return lock();
			}
			bool lock(){
				//adc_block�����b�N�@���s�����牽�������I���
				if(my_type::Block.lock())return true;

				if(++LockCnt == 0){
					//�X�^�[�g�A�b�v����
					my_type::Block.ADC.template converter_clock_div<converter_no_>(Setting.ClockDiv);
					my_type::Block.ADC.template converter_sampling_time<converter_no_>(Setting.SamplingTime);
					my_type::Block.ADC.template converter_resolution_bits<converter_no_>(Setting.ResolutionMode);

					//Global Convert Mode�p�ݒ�
					if(IsGlobalConvert)my_type::Block.ADC.template converter_scan_trigger_select<converter_no_>(3);

					//ADC ������҂�
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

				//adc_block���A�����b�N
				my_type::Block.unlock();
			}
			bool is_lock()const{ return LockCnt != 0; }
			bool relock(const adc::converter_setting& Setting_, bool ForceReset = false){
				//�ꏏ�Ȃ�p�X
				if(Setting == Setting_ && !ForceReset)return true;

				//�ݒ�X�V
				Setting = Setting_;

				//��U�X�g�b�v
				my_type::Block.ADC.template converter_work_enable<converter_no_>(false);
				my_type::Block.ADC.template converter_enable<converter_no_>(false);

				//�X�^�[�g�A�b�v����
				my_type::Block.ADC.template converter_clock_div<converter_no_>(Setting.ClockDiv);
				my_type::Block.ADC.template converter_sampling_time<converter_no_>(Setting.SamplingTime);
				my_type::Block.ADC.template converter_resolution_bits<converter_no_>(Setting.ResolutionMode);

				//Global Convert Mode�p�ݒ�
				if(IsGlobalConvert)my_type::Block.ADC.template converter_scan_trigger_select<converter_no_>(3);

				//ADC ������҂�
				my_type::Block.ADC.template converter_enable<converter_no_>(true);
				while(!my_type::Block.ADC.template converter_work_ready<converter_no_>());
				my_type::Block.ADC.template converter_work_enable<converter_no_>(true);

				return false;
			}
			unsigned int use_count()const{ return LockCnt; }
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

	//�����^���LADC
	//	shared_adc�͎��̂�p�ӂ���K�v���Ȃ��B�����analog_pin�����lock/unclock�œK�X������/�I�[�������B
	//	�t�Ɍ����΁Ashared_adc��������邽�߂ɂ́A���ׂĂ�analog_pin��unlock����K�v������B
	//	analog_pin�̓ǂݏo�������͏d�����Ă��Ȃ����Ƃ̊m�F���Ȃ����B�d�����͓ǂ݂������s�ƂȂ�A0xffff���Ԃ�
	template<typename adc_block_register_, typename identifier_>
	class shared_adc{
		typedef shared_adc<adc_block_register_, identifier_> my_type;
		struct my_identifier{};//�Ǝ���identifier�����@����́Aidentifier_���g���܂킳��Ă���ꍇ�ɁAbasic_shared_adc����������̂�h�����߁B
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
			typedef typename my_type::template cv<converter_no> my_converter_setting;
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

				//�����ŁAConverter�g�p���m��
				if(my_converter::Converter.start())return 0xFFFF;

				if(pBlockSetting == 0){
					//relock��true��Ԃ��������Z�b�g����K�v���Ȃ�
					ForceReset = !my_adc::Block.relock(my_type::BlockSetting);
				} else{
					ForceReset = !my_adc::Block.relock(*pBlockSetting);
				}

				if(pConverterSetting == 0){
					my_converter::Converter.relock(my_converter_setting::ConverterSetting, ForceReset);
				} else{
					my_converter::Converter.relock(*pConverterSetting, ForceReset);
				}

				//��փs���̐ݒ�̗L����ݒ�
				my_converter::Converter.use_alternative_pin(AN.is_alternative());

				//�ʃX�L��������`�����l����ݒ�
				my_adc::Block.individual_convert_select(analog_no::No);
				__asm("nop");

				//�g���K������
				my_adc::Block.individual_convert_trigger();

				//�X�L�����҂�
				while(!AN.data_ready());

				//�f�[�^�����Z
				uint16 Val = AN.data();

				//�R���o�[�^�[�g�p������
				my_converter::Converter.stop();

				return Val;
			}
			uint16 operator()(uint16 ObserveNum_){
				xc32_assert(is_lock(), exception(0xE2));

				bool ForceReset = false;

				//�����ŁAConverter�g�p���m��
				if(my_converter::Converter.start())return 0xFFFF;

				if(pBlockSetting == 0){
					//relock��true��Ԃ��������Z�b�g����K�v���Ȃ�
					ForceReset = !my_adc::Block.relock(my_type::BlockSetting);
				} else{
					ForceReset = !my_adc::Block.relock(*pBlockSetting);
				}

				if(pConverterSetting == 0){
					my_converter::Converter.relock(my_converter_setting::ConverterSetting, ForceReset);
				} else{
					my_converter::Converter.relock(*pConverterSetting, ForceReset);
				}

				//��փs���̐ݒ�̗L����ݒ�
				my_converter::Converter.use_alternative_pin(AN.is_alternative());

				//�ʃX�L��������`�����l����ݒ�
				my_adc::Block.individual_convert_select(analog_no::No);

				uint32 Val = 0;
				for(uint16 ObserveCnt = 0; ObserveCnt<ObserveNum_; ++ObserveCnt){
					//�g���K������
					my_adc::Block.individual_convert_trigger();

					//�X�L�����҂�
					while(!AN.data_ready());

					//�f�[�^�����Z
					Val += AN.data();
				}

				//�R���o�[�^�[�g�p������
				my_converter::Converter.stop();

				return Val/ObserveNum_;
			}
		};
	};
	template<typename adc_block_register_, typename identifier_>
	adc::block_setting shared_adc<adc_block_register_, identifier_>::BlockSetting;
	template<typename adc_block_register_, typename identifier_>
	template<typename converter_no_>
	adc::converter_setting shared_adc<adc_block_register_, identifier_>::cv<converter_no_>::ConverterSetting;

	//�񓯊��^�ʃR���o�[�gADC
	//	async_adc��shared_adc���l�A���̂�p�ӂ���K�v���Ȃ��Banalog_pin�����lock/unclock�œK�X������/�I�[�������B
	//	analog_pin����ǂ݂����Ă��l�͂��̏�œǂ݂����ꂸ�ɁAfuture���߂�l�Ƃ��ĕԂ����B
	//	�����ł�queue��adc�p��task���ς܂�A�����ǂݏo�����s����B
	//	�@�\�����邽�߂ɂ́A����I��converter���Ƃ�work�֐����Ăяo���K�v������B
	template<typename adc_block_register_, typename identifier_>
	class async_functional_adc{
		//=== �݌v�T�v ===
		//async_functional_adc�́A�ʃR���o�[�g�𗘗p����adc�̃f�[�^�ǂݏo����S������
		//async_functional_adc::analog_pin����Aoperator()�����s����ƁA
		//	RequestQueue�Ƀf�[�^���N�G�X�g���e���ς܂��
		//	���N�G�X�g�ɂ́A���ʏ������ݗp��promise&���܂܂��
		//	�߂�l�Ƃ��āA���p�҂�future���󂯎��
		//adc��operator()���s�ɂ���āA
		//	�����Ă���^�X�N���Ȃ���΁ARequestQueue��ǂݍ���
		//	���N�G�X�g���e�ɉ����Ĉꊇ�R���o�[�g���쓮����
		//	�f�[�^�ǂݏo�����������Ă���΁Apromise&����Ēʒm����
		//	���ׂĂ�������A�^�X�N���L���[����O��
	private:
		typedef adc_block_register_ adc_block_register;
		typedef async_functional_adc<adc_block_register_, identifier_> my_type;
		struct my_identifier{};
		typedef basic_shared_adc<adc_block_register_, my_identifier> my_adc;
	private:
		//�f�[�^���N�G�X�g���e
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
			//Converter�n start�͎��s������true��Ԃ�
			virtual bool start() = 0;
			virtual void stop() = 0;
			//AN Pin�n
			virtual uint16 try_read_data() = 0;	//���s������A�߂�l��0xffff
		};
		typedef typename xc::chain<request*>::element request_ptr_element;
	private:
		struct converter_task_interface{
			virtual void task() = 0;
		};
		typedef typename xc::chain<converter_task_interface*>::element converter_task_element;
		static xc::chain<converter_task_interface*> TaskChain;
	private:
		static adc::block_setting BlockSetting;
		template<typename converter_no_>
		struct converter_task:public converter_task_interface{
		private:
			xc::chain<request*> ReqPtrQueue;
			request* HandlingReqPtr;
			uint32 DataSum;
			uint16 DataCnt;
		public:
			//�^�X�N�֐�
			void task(){
				//���N�G�X�g���̃f�[�^������ꍇ
				if(HandlingReqPtr){
					uint16 Data = HandlingReqPtr->try_read_data();

					//�f�[�^�ǂݎ��Ɏ��s���Ă��Ȃ����
					if(Data != 0xffff){
						DataSum += Data;
						++DataCnt;

						if(DataCnt >= HandlingReqPtr->Num){
							//Converter���~
							HandlingReqPtr->stop();
							//���ʂ���������
							HandlingReqPtr->Ref.set_value(static_cast<uint16>(DataSum / DataCnt));
							//���N�G�X�g�f�[�^�I��
							HandlingReqPtr = 0;
						} else{
							//�ʃX�L��������`�����l����ݒ�
							my_adc::Block.individual_convert_select(HandlingReqPtr->AN);
							__asm("nop");
							//�g���K�������āA�ŏ��̃��N�G�X�g
							my_adc::Block.individual_convert_trigger();
						}
					}
				}

				//���N�G�X�g���̃f�[�^���Ȃ��ꍇ
				while(HandlingReqPtr == 0 && !ReqPtrQueue.empty()){
					//�擪���甲���Ă���
					HandlingReqPtr = ReqPtrQueue.front();
					ReqPtrQueue.pop_front();

					//�k���|���͂����i�����I�ɂ͂Ȃ��͂��j
					if(HandlingReqPtr == 0)continue;

					//start�Ɏ��s���邱�Ƃ́A�����I�ɂ��蓾�Ȃ��̂Ŗ���
					HandlingReqPtr->start();

					DataSum = 0;
					DataCnt = 0;

					//�ʃX�L��������`�����l����ݒ�
					my_adc::Block.individual_convert_select(HandlingReqPtr->AN);
					__asm("nop");

					//�g���K�������āA�ŏ��̃��N�G�X�g
					my_adc::Block.individual_convert_trigger();
				}
			}
			//�o�^���ꂽ���ׂẴ��N�G�X�g��j��
			void clear(){
				for(typename xc::chain<request*>::iterator Itr = ReqPtrQueue.begin(); Itr != ReqPtrQueue.end(); ++Itr){
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
			//push
			void push(request_ptr_element& Elem){ ReqPtrQueue.push_back(Elem); }
		};
		template<typename converter_no_>
		struct task_holder{
			static converter_task<converter_no_> ConverterTask;
			static converter_task_element ConverterTaskElement;
			static adc::converter_setting ConverterSetting;
		};
	public:
		static void set_default_block_setting(const adc::block_setting& BlockSetting_){
			BlockSetting = BlockSetting_;
		}
		template<typename converter_no_>
		static void set_default_converter_setting(const adc::converter_setting& ConverterSetting_){
			task_holder<converter_no_>::ConverterSetting = ConverterSetting_;
		}
	public:
		template<typename pin_register_>
		struct analog_pin{
		private:
			typedef pin_register_ pin_register;
			typedef typename pin_register_::analog_no analog_no;
			typedef sfr::adc::an<typename pin_register_::analog_no> an_register;
			typedef typename an_register::converter_no converter_no;
			typedef typename my_adc::template cv<converter_no> my_converter;
			typedef task_holder<converter_no> my_task_holder;
		private:
			struct an_request :public request{
				an_register AN;
			public:
				an_request(promise<uint16>& Ref_) :request(Ref_, analog_no::No){}
			public:
				virtual bool start(){
					//�����ŁAConverter�g�p���m��
					if(my_converter::Converter.start())return true;

					bool ForceReset = false;
					if(this->pBlockSetting == 0){
						//relock��true��Ԃ��������Z�b�g����K�v���Ȃ�
						ForceReset = !my_adc::Block.relock(my_type::BlockSetting);
					} else{
						ForceReset = !my_adc::Block.relock(*(this->pBlockSetting));
					}

					if(this->pConverterSetting == 0){
						my_converter::Converter.relock(my_task_holder::ConverterSetting, ForceReset);
					} else{
						my_converter::Converter.relock(*(this->pConverterSetting), ForceReset);
					}

					//��փs���̐ݒ�̗L����ݒ�
					my_converter::Converter.use_alternative_pin(AN.is_alternative());

					return false;
				}
				virtual void stop(){
					//�R���o�[�^�[�g�p������
					my_converter::Converter.stop();
				}
				virtual uint16 try_read_data(){
					//�X�L�����҂�
					if(!AN.data_ready())return 0xffff;
					return AN.data();
				}
			};
			an_request Request;
			request_ptr_element ReqElement;	//Request�ւ̃|�C���^��͂�ł���
		private:
			pin_register Pin;
			bool IsLock;
			promise<uint16> Promise;
		public:
			analog_pin()
				: IsLock(false)
				, Request(Promise){
				*ReqElement = &Request;
			}
			~analog_pin(){ if(is_lock())unlock(); }
			void config(const adc::block_setting* pBlockSetting_, const adc::converter_setting* pConverterSetting_){
				Request.pBlockSetting = pBlockSetting_;
				Request.pConverterSetting = pConverterSetting_;
			}
			bool lock(const adc::block_setting* pBlockSetting_, const adc::converter_setting* pConverterSetting_){
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

				if(my_task_holder::ConverterTaskElement){
					*my_task_holder::ConverterTaskElement = &my_task_holder::ConverterTask;
					TaskChain.push_back(my_task_holder::ConverterTaskElement);
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

				if(my_converter::Converter.use_count() == 0 && !my_task_holder::ConverterTaskElement){
					TaskChain.erase(TaskChain.find(my_task_holder::ConverterTaskElement));
				}

				IsLock = false;
			}
		public:
			//�f�[�^�ǂݏo��
			//	���N�G�X�g�����������s�\�ȏꍇ�͋��future���Ԃ�
			//	���炩�̌����Ŏ��s�����ꍇ�́A0xffff��future�ɏ������܂��
			future<uint16> operator()(void){ return operator()(1); }
			future<uint16> operator()(uint16 ObserveNum_){
				if(owns_request())return future<uint16>();
				if(ObserveNum_ == 0)return future<uint16>();

				//Request�����������āA���̃|�C���^������ł�ReqElement��Queue�ɂԂ�����
				Request.Num = ObserveNum_;
				task_holder<converter_no>::ConverterTask.push(ReqElement);

				return Promise.get_future();
			}
		public:
			//���݃��N�G�X�g�����H
			bool owns_request()const{ return !Promise.can_get_future() || !static_cast<bool>(ReqElement); }
		};
	public:
		void operator()(void){work();}
		static void work(){
			typename xc::chain<converter_task_interface*>::iterator Itr = TaskChain.begin();
			typename xc::chain<converter_task_interface*>::iterator End = TaskChain.end();
			for(; Itr != End; ++Itr){
				(*Itr)->task();
			}
		}
		template<typename converter_no_>
		static void clear(){
			task_holder<converter_no_>::Converter.clear();
		}
	};
	template<typename adc_block_register_, typename identifier_>
	adc::block_setting async_functional_adc<adc_block_register_, identifier_>::BlockSetting;
	template<typename adc_block_register_, typename identifier_>
	xc::chain<typename async_functional_adc <adc_block_register_, identifier_>::converter_task_interface*> async_functional_adc<adc_block_register_, identifier_>::TaskChain;
	template<typename adc_block_register_, typename identifier_>
	template<typename converter_no_>
	typename async_functional_adc<adc_block_register_,identifier_>::template converter_task<converter_no_> async_functional_adc<adc_block_register_, identifier_>::task_holder<converter_no_>::ConverterTask;
	template<typename adc_block_register_, typename identifier_>
	template<typename converter_no_>
	typename async_functional_adc <adc_block_register_, identifier_>::converter_task_element async_functional_adc<adc_block_register_, identifier_>::task_holder<converter_no_>::ConverterTaskElement;
	template<typename adc_block_register_, typename identifier_>
	template<typename converter_no_>
	adc::converter_setting async_functional_adc<adc_block_register_, identifier_>::task_holder<converter_no_>::ConverterSetting;

/*	//�񓯊��^�ꊇ�R���o�[�gADC
	//	async_adc��shared_adc���l�A���̂�p�ӂ���K�v���Ȃ��Banalog_pin�����lock/unclock�œK�X������/�I�[�������B
	//	analog_pin����ǂ݂����Ă��l�͂��̏�œǂ݂����ꂸ�ɁAfuture���߂�l�Ƃ��ĕԂ����B
	//	�����ł�queue��adc�p��task���ς܂�A�����ǂݏo�����s����B
	//	���荞�݂��g���ċ@�\���邽�߁A���p�҂�analog_pin��G��ȊO�ɉ������Ȃ��Ă悢�B
	template<typename adc_block_register_, typename identifier_>
	class async_interrupt_adc{
		//=== �݌v�T�v ===
		//async_interrupt_adc�́A�ꊇ�R���o�[�g�𗘗p����adc�̃f�[�^�ǂݏo����S������
		//async_interrupt_adc::analog_pin����Aoperator()�����s����ƁA
		//	RequestChain�Ƀf�[�^���N�G�X�g���e���ǉ������
		//	���N�G�X�g�ɂ́A���ʏ������ݗp��promise&���܂܂��
		//	�߂�l�Ƃ��āA���p�҂�future���󂯎��
		//adc�̈ꊇ�R���o�[�g�������荞�݂����s������
		//	RequestChain���ł̓ǂݏo����������Ăɒʒm
		//	���N�G�X�g���e�ɉ����Ĉꊇ�R���o�[�g���쓮����
		//	�f�[�^�ǂݏo�����������Ă���΁Apromise&����Ēʒm����
		//	������A�^�X�N���L���[����O��
	private:
		typedef adc_block_register_ adc_block_register;
		typedef async_interrupt_adc<adc_block_register_, identifier_> my_type;
		struct my_identifier{};
		typedef basic_shared_adc<adc_block_register_, my_identifier> my_adc;
	private:
		//�f�[�^���N�G�X�g���e
		struct request{
		public:
			promise<uint16>& Ref;
			const unsigned char AN;
			uint16 Num;
			uint16 Remain;
			uint32 Data;
		public:
			request(promise<uint16>& Ref_, unsigned char AN_)
				: Ref(Ref_)
				, AN(AN_)
				, Num(1)
				, Remain(0)
				, Data(0){
			}
		public:
			//Converter�n start�͎��s������true��Ԃ�
			virtual bool start() = 0;
			virtual void stop() = 0;
			//AN Pin�n
			virtual void request_data() = 0;
			virtual uint16 try_read_data() = 0;	//���s������A�߂�l��0xffff
		};
		typedef xc::sorted_chain<request*> request_ptr_chain;
		typedef typename request_ptr_chain::element request_ptr_element;
		request_ptr_chain ReqPtrQueue;
	public:
		//���荞�݊֐�
		static void interrupt_function(){
			//�܂��ARequest�f�[�^�ǂݏo������
			request_ptr_chain::iterator Itr = ReqPtrQueue.begin();
			while(Itr != ReqPtrQueue.end()){
				uint16 Datum = (*Itr)->try_read_data();
				if(Datum != 0xffff){
					(*Itr)->Data += Datum;
					--((*Itr)->Remain);

					//�I������
					if((*Itr)->Remain == 0){
						(*Itr)->set_value(static_cast<uint16>((*Itr)->Data / (*Itr)->Num));
						ReqPtrQueue.pop();
						Itr = ReqPtrQueue.begin();
						continue;
					}
				}

				++Itr;
			}

			//���ɁA�܂��K�v�ȃf�[�^�̓ǂݏo�����m�F

			//��ăX�L�����ɓo�^�����`�����l�������Z�b�g
			my_adc::Block.reset_request_global_convert();

			//�������łɕK�v�ȓǂݏo�����Ȃ���΁A��x���f����
			if(ReqPtrQueue.empty()){
				return;
			}

			Itr = ReqPtrQueue.begin();
			while(Itr != ReqPtrQueue.end()){
				(*Itr)->request_data();
				++Itr;
			}

			//�g���K�[������
			my_adc::Block.global_convert_trigger();
		}
	public:
		template<typename pin_register_>
		struct analog_pin{
		private:
			typedef pin_register_ pin_register;
			typedef typename pin_register_::analog_no analog_no;
			typedef sfr::adc::an<typename pin_register_::analog_no> an_register;
			typedef typename an_register::converter_no converter_no;
			typedef typename my_adc::template cv<converter_no> my_converter;
////			typedef typename task_holder<converter_no> my_task_holder;
		private:
			struct an_request :public request{
				an_register AN;
			public:
				an_request(promise<uint16>& Ref_) :request(Ref_, analog_no::No){}
			public:
				virtual bool start(){
					//�����ŁAConverter�g�p���m��
					if(my_converter::Converter.start())return true;

					bool ForceReset = false;
					if(pBlockSetting == 0){
						//relock��true��Ԃ��������Z�b�g����K�v���Ȃ�
						ForceReset = !my_adc::Block.relock(my_type::BlockSetting);
					} else{
						ForceReset = !my_adc::Block.relock(*pBlockSetting);
					}

					if(pConverterSetting == 0){
						my_converter::Converter.relock(my_task_holder::ConverterSetting, ForceReset);
					} else{
						my_converter::Converter.relock(*pConverterSetting, ForceReset);
					}

					//��փs���̐ݒ�̗L����ݒ�
					my_converter::Converter.use_alternative_pin(AN.is_alternative());

					return false;
				}
				virtual void stop(){
					//�R���o�[�^�[�g�p������
					my_converter::Converter.stop();
				}
				virtual void request_data(){
					AN.request_global_convert(true);
				}
				virtual uint16 read_data(){
					//�X�L�����҂�
					while(!AN.data_ready());
					return AN.data();
				}
			};
			an_request Request;
			request_ptr_element ReqElement;	//Request�ւ̃|�C���^��͂�ł���
		private:
			pin_register Pin;
			bool IsLock;
			promise<uint16> Promise;
		public:
			analog_pin()
				: IsLock(false)
				, Request(Promise){
				*ReqElement = &Request;
			}
			~analog_pin(){ if(is_lock())unlock(); }
			void config(const adc::block_setting* pBlockSetting_, const adc::converter_setting* pConverterSetting_){
				Request.pBlockSetting = pBlockSetting_;
				Request.pConverterSetting = pConverterSetting_;
			}
			bool lock(const adc::block_setting* pBlockSetting_, const adc::converter_setting* pConverterSetting_){
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

				if(my_task_holder::ConverterTaskElement){
					*my_task_holder::ConverterTaskElement = &my_task_holder::ConverterTask;
					TaskChain.push_back(my_task_holder::ConverterTaskElement);
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

				if(my_converter::Converter.use_count() == 0 && !my_task_holder::ConverterTaskElement){
					TaskChain.erase(TaskChain.find(my_task_holder::ConverterTaskElement));
				}

				IsLock = false;
			}
		public:
			//�f�[�^�ǂݏo��
			//	���N�G�X�g�����������s�\�ȏꍇ�͋��future���Ԃ�
			//	���炩�̌����Ŏ��s�����ꍇ�́A0xffff��future�ɏ������܂��
			future<uint16> operator()(void){ return operator()(1); }
			future<uint16> operator()(uint16 ObserveNum_){
				if(owns_request())return future<uint16>();
				if(ObserveNum_ == 0)return future<uint16>();

				//Request�����������āA���̃|�C���^������ł�ReqElement��Queue�ɂԂ�����
				Request.Num = ObserveNum_;
				task_holder<converter_no>::ConverterTask.push(ReqElement);

				return Promise.get_future();
			}
		public:
			//���݃��N�G�X�g�����H
			bool owns_request()const{ return !Promise.can_get_future() || !static_cast<bool>(ReqElement); }
		};


	private:
		struct converter_task_interface{
			virtual void task() = 0;
		};
		typedef typename xc::chain<converter_task_interface*>::element converter_task_element;
		static xc::chain<converter_task_interface*> TaskChain;
	private:
		static adc::block_setting BlockSetting;
		template<typename converter_no_>
		struct converter_task :public converter_task_interface{
		private:
			xc::sorted_chain<request*> ReqPtrQueue;
		public:
			//�^�X�N�֐�
			void task(){
				//���N�G�X�g���̃f�[�^������ꍇ
				if(HandlingReqPtr){
					uint16 Data = HandlingReqPtr->try_read_data();

					//�f�[�^�ǂݎ��Ɏ��s���Ă��Ȃ����
					if(Data != 0xffff){
						DataSum += Data;
						++DataCnt;

						if(DataCnt >= HandlingReqPtr->Num){
							//Converter���~
							HandlingReqPtr->stop();
							//���ʂ���������
							HandlingReqPtr->Ref.set_value(static_cast<uint16>(DataSum / DataCnt));
							//���N�G�X�g�f�[�^�I��
							HandlingReqPtr = 0;
						} else{
							//�ʃX�L��������`�����l����ݒ�
							my_adc::Block.individual_convert_select(HandlingReqPtr->AN);
							__asm("nop");
							//�g���K�������āA�ŏ��̃��N�G�X�g
							my_adc::Block.individual_convert_trigger();
						}
					}
				}

				//���N�G�X�g���̃f�[�^���Ȃ��ꍇ
				while(HandlingReqPtr == 0 && !ReqPtrQueue.empty()){
					//�擪���甲���Ă���
					HandlingReqPtr = ReqPtrQueue.front();
					ReqPtrQueue.pop_front();

					//�k���|���͂����i�����I�ɂ͂Ȃ��͂��j
					if(HandlingReqPtr == 0)continue;

					//start�Ɏ��s���邱�Ƃ́A�����I�ɂ��蓾�Ȃ��̂Ŗ���
					HandlingReqPtr->start();

					DataSum = 0;
					DataCnt = 0;

					//�ʃX�L��������`�����l����ݒ�
					my_adc::Block.individual_convert_select(HandlingReqPtr->AN);
					__asm("nop");

					//�g���K�������āA�ŏ��̃��N�G�X�g
					my_adc::Block.individual_convert_trigger();
				}
			}
			//�o�^���ꂽ���ׂẴ��N�G�X�g��j��
			void clear(){
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
			//push
			void push(request_ptr_element& Elem){ ReqPtrQueue.push_back(Elem); }
		};
		template<typename converter_no_>
		struct task_holder{
			static converter_task<converter_no_> ConverterTask;
			static converter_task_element ConverterTaskElement;
			static adc::converter_setting ConverterSetting;
		};
	public:
		static void set_block_setting(const adc::block_setting& BlockSetting_){
			BlockSetting = BlockSetting_;
		}
		template<typename converter_no_>
		static void set_converter_setting(const adc::converter_setting& ConverterSetting_){
			task_holder<converter_no_>::ConverterSetting = ConverterSetting_;
		}

	};
	template<typename adc_block_register_, typename identifier_>
	adc::block_setting async_interrupt_adc<adc_block_register_, identifier_>::BlockSetting;
	template<typename adc_block_register_, typename identifier_>
	xc::chain<typename async_interrupt_adc <adc_block_register_, identifier_>::converter_task_interface*> typename async_interrupt_adc <adc_block_register_, identifier_>::TaskChain;
	template<typename adc_block_register_, typename identifier_>
	template<typename converter_no_>
	typename async_interrupt_adc <adc_block_register_, identifier_>::converter_task<converter_no_> async_interrupt_adc<adc_block_register_, identifier_>::task_holder<converter_no_>::ConverterTask;
	template<typename adc_block_register_, typename identifier_>
	template<typename converter_no_>
	typename async_interrupt_adc <adc_block_register_, identifier_>::converter_task_element async_interrupt_adc<adc_block_register_, identifier_>::task_holder<converter_no_>::ConverterTaskElement;
	template<typename adc_block_register_, typename identifier_>
	template<typename converter_no_>
	adc::converter_setting async_interrupt_adc<adc_block_register_, identifier_>::task_holder<converter_no_>::ConverterSetting;
	//*/
}

#
#endif
