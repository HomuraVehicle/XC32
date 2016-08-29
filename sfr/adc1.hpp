#ifndef XC32_SFR_ADC1_INC
#define XC32_SFR_ADC1_INC 100
#
#include"device_include.h"
#include<XCBase/type.hpp>
#include"sfr_register_mixin.hpp"
#include"exclusive_mixin.hpp"
#include"adc_base.hpp"
namespace xc32 {
	using namespace xc;
	namespace sfr {
		struct adc_block :public sfr_register_mixin<adc_block>, public exclusive_mixin<adc_block> {
		public:
			//ADC���V���[��ON
			void enable(bool val_) { ADCCON1bits.ON = static_cast<unsigned char>(val_); }
			bool enable()const { return static_cast<bool>(ADCCON1bits.ON); }
			//ADC���W���[���̎g�p�������ł�����(���W���[���̎���calibration�҂�)
			bool module_ready()const volatile { return static_cast<bool>(ADCCON2bits.BGVRRDY); }
			//�X�L�����g���K���I���r�b�g,0:�g���K�Ȃ�,1:�O���[�o���\�t�g�E�F�A�g���K,�c
			void scan_trigger_select(unsigned char val_) { ADCCON1bits.STRGSRC = val_; }
			unsigned char scan_trigger_select()const { return ADCCON1bits.STRGSRC; }
			//�O���[�o���\�t�g�E�F�A�g���K�r�b�g
			void global_software_trigger() { ADCCON3bits.GSWTRG = 1; }
			//ADC�}�X�^�[�N���b�N��(T_Q)�r�b�g�C1:Tcy,2:REFCLK3,3:FRC�I�V���[�^�o��,0:�\��ς�
			void clock_select(unsigned char val_) { ADCCON3bits.ADCSEL = val_; }
			unsigned char clock_select()const { return ADCCON3bits.ADCSEL; }
			//ADC�}�X�^�[�N���b�N������r�b�g(0�`127)�Fclock_div==0�Ȃ�T_AD = T_Q ,T_AD = 2 * T_Q * clock_div
			void clock_div(unsigned char val_) { ADCCON3bits.CONCLKDIV = val_; }
			unsigned char clock_div()const { return ADCCON3bits.CONCLKDIV; }
			//�P��ADC�ϊ��v���r�b�g
			void individual_convert(bool val_) { ADCCON3bits.RQCNVRT = static_cast<unsigned char>(val_); }
			bool individual_convert()const { return static_cast<bool>(ADCCON3bits.RQCNVRT); }
			//�P��ADC���͑I���r�b�g
			void individual_convert_input_select(unsigned char val_) { ADCCON3bits.ADINSEL = val_; }
			unsigned char individual_convert_input_select()const { return ADCCON3bits.ADINSEL; }
			//Vref�I���r�b�g.0:VrefH=AVdd VrefL=AVss,1:VrefH=Vref+ VrefL=AVss,2:VrefH=AVdd VrefL=Vref-,3:VrefH=Vref+ VrefL=Vref-
			void reference_voltage(unsigned char val_) { ADCCON3bits.VREFSEL = val_; }
			unsigned char reference_voltage()const { return ADCCON3bits.VREFSEL; }

			//ADC���Ƃ̌ŗL�̃N���b�N������(1-127) ���̒l��2�{�̎����ɂȂ�
			template<unsigned int adc_no>
			void adc_clock_div(unsigned char val_);
			template<unsigned int adc_no>
			unsigned char adc_clock_div();
			//ADC���Ƃ̃T���v�����O�^�C��(0-1023)�@val+2�̃N���b�N���������T���v�����O�ɂ�����H
			template<unsigned int adc_no>
			void sampling_time(unsigned char val_);
			template<unsigned int adc_no>
			unsigned char sampling_time();
			//ADC��bit���x�@resolution_mode����I��
			template<unsigned int adc_no>
			void resolution_bits(unsigned char val_);
			template<unsigned int adc_no>
			unsigned char resolution_bits();
			//excluded ADC��p�@���蓖�Ă̕ʂ�pinw���g����
			template<unsigned int adc_no>
			void use_alternative_input_pin(bool val_);
			template<unsigned int adc_no>
			bool use_alternative_input_pin();
			//ADC���Ƃ�clock�X�^�[�g
			template<unsigned int adc_no>
			void adc_clock_enable(bool val_);
			template<unsigned int adc_no>
			bool adc_clock_enable();
			//ADC���Ƃ̃N���b�N�����m�F�@clock_enable���work_ready��҂�
			template<unsigned int adc_no>
			bool adc_work_ready();
			//ADC���Ƃ̂��Ƃ̃^�X�N�X�^�[�g work_ready�ɂȂ�����work_enable����ƁA���p����������
			template<unsigned int adc_no>
			void adc_work_enable(bool val_);
			template<unsigned int adc_no>
			bool adc_work_enable();
		};

	#ifdef ADCXXX_EXCLUDED
		//ADC���Ƃ̌ŗL�̃N���b�N������(1-127) ���̒l��2�{�̎����ɂȂ�
		template<>
		void adc_block::adc_clock_div<XXX>(unsigned char val_){
			ADCXXXTIMEbits.ADCDIV = val_;
		}
		template<>
		unsigned char adc_block::adc_clock_div<XXX>(){
			return ADCXXXTIMEbits.ADCDIV;
		}
		//ADC���Ƃ̃T���v�����O�^�C��(0-1023)�@val+2�̃N���b�N���������T���v�����O�ɂ�����H
		template<>
		void adc_block::sampling_time<XXX>(unsigned char val_){
			ADCXXXTIMEbits.SAMC = val_;
		}
		template<>
		unsigned char adc_block::sampling_time<XXX>(){
			return ADCXXXTIMEbits.SAMC;
		}
		//ADC��bit���x�@resolution_mode����I��
		template<>
		void adc_block::resolution_bits<XXX>(unsigned char val_){
			ADCXXXTIMEbits.SELRES = val_;
		}
		template<>
		unsigned char adc_block::resolution_bits<XXX>(){
			return ADCXXXTIMEbits.SELRES;
		}
		//excluded ADC��p�@���蓖�Ă̕ʂ�pinw���g����
		template<>
		void adc_block::use_alternative_input_pin<XXX>(bool val_){
			ADCTRGMODEbits.SHXXXALT = val_;
		}
		template<>
		bool adc_block::use_alternative_input_pin<XXX>(){
			return ADCTRGMODEbits.SHXXXALT;
		}
		//ADC���Ƃ�clock�X�^�[�g
		template<>
		void adc_block::adc_clock_enable<XXX>(bool val_){
			ADCANCONbits.ANENXXX = val_;
		}
		template<>
		bool adc_block::adc_clock_enable<XXX>(){
			return ADCANCONbits.ANENXXX;
		}
		//ADC���Ƃ̃N���b�N�����m�F�@clock_enable���work_ready��҂�
		template<>
		bool adc_block::adc_work_ready<XXX>(){
			return ADCANCONbits.WKRDYXXX;
		}
		//ADC���Ƃ̂��Ƃ̃^�X�N�X�^�[�g work_ready�ɂȂ�����work_enable����ƁA���p����������
		template<>
		void adc_block::adc_work_enable(bool val_){
			ADCCON3bits.DIGENXXX = val_;
		}
		template<>
		bool adc_block::adc_work_enable(){
			return ADCCON3bits.DIGENXXX;
		}
	#endif
	#ifdef ADC0_EXCLUDED
		//ADC���Ƃ̌ŗL�̃N���b�N������(1-127) ���̒l��2�{�̎����ɂȂ�
		template<>
		void adc_block::adc_clock_div<0>(unsigned char val_){
			ADC0TIMEbits.ADCDIV = val_;
		}
		template<>
		unsigned char adc_block::adc_clock_div<0>(){
			return ADC0TIMEbits.ADCDIV;
		}
		//ADC���Ƃ̃T���v�����O�^�C��(0-1023)�@val+2�̃N���b�N���������T���v�����O�ɂ�����H
		template<>
		void adc_block::sampling_time<0>(unsigned char val_){
			ADC0TIMEbits.SAMC = val_;
		}
		template<>
		unsigned char adc_block::sampling_time<0>(){
			return ADC0TIMEbits.SAMC;
		}
		//ADC��bit���x�@resolution_mode����I��
		template<>
		void adc_block::resolution_bits<0>(unsigned char val_){
			ADC0TIMEbits.SELRES = val_;
		}
		template<>
		unsigned char adc_block::resolution_bits<0>(){
			return ADC0TIMEbits.SELRES;
		}
		//excluded ADC��p�@���蓖�Ă̕ʂ�pinw���g����
		template<>
		void adc_block::use_alternative_input_pin<0>(bool val_){
			ADCTRGMODEbits.SH0ALT = val_;
		}
		template<>
		bool adc_block::use_alternative_input_pin<0>(){
			return ADCTRGMODEbits.SH0ALT;
		}
		//ADC���Ƃ�clock�X�^�[�g
		template<>
		void adc_block::adc_clock_enable<0>(bool val_){
			ADCANCONbits.ANEN0 = val_;
		}
		template<>
		bool adc_block::adc_clock_enable<0>(){
			return ADCANCONbits.ANEN0;
		}
		//ADC���Ƃ̃N���b�N�����m�F�@clock_enable���work_ready��҂�
		template<>
		bool adc_block::adc_work_ready<0>(){
			return ADCANCONbits.WKRDY0;
		}
		//ADC���Ƃ̂��Ƃ̃^�X�N�X�^�[�g work_ready�ɂȂ�����work_enable����ƁA���p����������
		template<>
		void adc_block::adc_work_enable(bool val_){
			ADCCON3bits.DIGEN0 = val_;
		}
		template<>
		bool adc_block::adc_work_enable(){
			return ADCCON3bits.DIGEN0;
		}
	#endif
	#ifdef ADC1_EXCLUDED
		//ADC���Ƃ̌ŗL�̃N���b�N������(1-127) ���̒l��2�{�̎����ɂȂ�
		template<>
		void adc_block::adc_clock_div<1>(unsigned char val_){
			ADC1TIMEbits.ADCDIV = val_;
		}
		template<>
		unsigned char adc_block::adc_clock_div<1>(){
			return ADC1TIMEbits.ADCDIV;
		}
		//ADC���Ƃ̃T���v�����O�^�C��(0-1023)�@val+2�̃N���b�N���������T���v�����O�ɂ�����H
		template<>
		void adc_block::sampling_time<1>(unsigned char val_){
			ADC1TIMEbits.SAMC = val_;
		}
		template<>
		unsigned char adc_block::sampling_time<1>(){
			return ADC1TIMEbits.SAMC;
		}
		//ADC��bit���x�@resolution_mode����I��
		template<>
		void adc_block::resolution_bits<1>(unsigned char val_){
			ADC1TIMEbits.SELRES = val_;
		}
		template<>
		unsigned char adc_block::resolution_bits<1>(){
			return ADC1TIMEbits.SELRES;
		}
		//excluded ADC��p�@���蓖�Ă̕ʂ�pinw���g����
		template<>
		void adc_block::use_alternative_input_pin<1>(bool val_){
			ADCTRGMODEbits.SH1ALT = val_;
		}
		template<>
		bool adc_block::use_alternative_input_pin<1>(){
			return ADCTRGMODEbits.SH1ALT;
		}
		//ADC���Ƃ�clock�X�^�[�g
		template<>
		void adc_block::adc_clock_enable<1>(bool val_){
			ADCANCONbits.ANEN1 = val_;
		}
		template<>
		bool adc_block::adc_clock_enable<1>(){
			return ADCANCONbits.ANEN1;
		}
		//ADC���Ƃ̃N���b�N�����m�F�@clock_enable���work_ready��҂�
		template<>
		bool adc_block::adc_work_ready<1>(){
			return ADCANCONbits.WKRDY1;
		}
		//ADC���Ƃ̂��Ƃ̃^�X�N�X�^�[�g work_ready�ɂȂ�����work_enable����ƁA���p����������
		template<>
		void adc_block::adc_work_enable(bool val_){
			ADCCON3bits.DIGEN1 = val_;
		}
		template<>
		bool adc_block::adc_work_enable(){
			return ADCCON3bits.DIGEN1;
		}
	#endif
	#ifdef ADC2_EXCLUDED
		//ADC���Ƃ̌ŗL�̃N���b�N������(1-127) ���̒l��2�{�̎����ɂȂ�
		template<>
		void adc_block::adc_clock_div<2>(unsigned char val_){
			ADC2TIMEbits.ADCDIV = val_;
		}
		template<>
		unsigned char adc_block::adc_clock_div<2>(){
			return ADC2TIMEbits.ADCDIV;
		}
		//ADC���Ƃ̃T���v�����O�^�C��(0-1023)�@val+2�̃N���b�N���������T���v�����O�ɂ�����H
		template<>
		void adc_block::sampling_time<2>(unsigned char val_){
			ADC2TIMEbits.SAMC = val_;
		}
		template<>
		unsigned char adc_block::sampling_time<2>(){
			return ADC2TIMEbits.SAMC;
		}
		//ADC��bit���x�@resolution_mode����I��
		template<>
		void adc_block::resolution_bits<2>(unsigned char val_){
			ADC2TIMEbits.SELRES = val_;
		}
		template<>
		unsigned char adc_block::resolution_bits<2>(){
			return ADC2TIMEbits.SELRES;
		}
		//excluded ADC��p�@���蓖�Ă̕ʂ�pinw���g����
		template<>
		void adc_block::use_alternative_input_pin<2>(bool val_){
			ADCTRGMODEbits.SH2ALT = val_;
		}
		template<>
		bool adc_block::use_alternative_input_pin<2>(){
			return ADCTRGMODEbits.SH2ALT;
		}
		//ADC���Ƃ�clock�X�^�[�g
		template<>
		void adc_block::adc_clock_enable<2>(bool val_){
			ADCANCONbits.ANEN2 = val_;
		}
		template<>
		bool adc_block::adc_clock_enable<2>(){
			return ADCANCONbits.ANEN2;
		}
		//ADC���Ƃ̃N���b�N�����m�F�@clock_enable���work_ready��҂�
		template<>
		bool adc_block::adc_work_ready<2>(){
			return ADCANCONbits.WKRDY2;
		}
		//ADC���Ƃ̂��Ƃ̃^�X�N�X�^�[�g work_ready�ɂȂ�����work_enable����ƁA���p����������
		template<>
		void adc_block::adc_work_enable(bool val_){
			ADCCON3bits.DIGEN2 = val_;
		}
		template<>
		bool adc_block::adc_work_enable(){
			return ADCCON3bits.DIGEN2;
		}
	#endif
	#ifdef ADC3_EXCLUDED
		//ADC���Ƃ̌ŗL�̃N���b�N������(1-127) ���̒l��2�{�̎����ɂȂ�
		template<>
		void adc_block::adc_clock_div<3>(unsigned char val_){
			ADC3TIMEbits.ADCDIV = val_;
		}
		template<>
		unsigned char adc_block::adc_clock_div<3>(){
			return ADC3TIMEbits.ADCDIV;
		}
		//ADC���Ƃ̃T���v�����O�^�C��(0-1023)�@val+2�̃N���b�N���������T���v�����O�ɂ�����H
		template<>
		void adc_block::sampling_time<3>(unsigned char val_){
			ADC3TIMEbits.SAMC = val_;
		}
		template<>
		unsigned char adc_block::sampling_time<3>(){
			return ADC3TIMEbits.SAMC;
		}
		//ADC��bit���x�@resolution_mode����I��
		template<>
		void adc_block::resolution_bits<3>(unsigned char val_){
			ADC3TIMEbits.SELRES = val_;
		}
		template<>
		unsigned char adc_block::resolution_bits<3>(){
			return ADC3TIMEbits.SELRES;
		}
		//excluded ADC��p�@���蓖�Ă̕ʂ�pinw���g����
		template<>
		void adc_block::use_alternative_input_pin<3>(bool val_){
			ADCTRGMODEbits.SH3ALT = val_;
		}
		template<>
		bool adc_block::use_alternative_input_pin<3>(){
			return ADCTRGMODEbits.SH3ALT;
		}
		//ADC���Ƃ�clock�X�^�[�g
		template<>
		void adc_block::adc_clock_enable<3>(bool val_){
			ADCANCONbits.ANEN3 = val_;
		}
		template<>
		bool adc_block::adc_clock_enable<3>(){
			return ADCANCONbits.ANEN3;
		}
		//ADC���Ƃ̃N���b�N�����m�F�@clock_enable���work_ready��҂�
		template<>
		bool adc_block::adc_work_ready<3>(){
			return ADCANCONbits.WKRDY3;
		}
		//ADC���Ƃ̂��Ƃ̃^�X�N�X�^�[�g work_ready�ɂȂ�����work_enable����ƁA���p����������
		template<>
		void adc_block::adc_work_enable(bool val_){
			ADCCON3bits.DIGEN3 = val_;
		}
		template<>
		bool adc_block::adc_work_enable(){
			return ADCCON3bits.DIGEN3;
		}
	#endif
	#ifdef ADC4_EXCLUDED
		//ADC���Ƃ̌ŗL�̃N���b�N������(1-127) ���̒l��2�{�̎����ɂȂ�
		template<>
		void adc_block::adc_clock_div<4>(unsigned char val_){
			ADC4TIMEbits.ADCDIV = val_;
		}
		template<>
		unsigned char adc_block::adc_clock_div<4>(){
			return ADC4TIMEbits.ADCDIV;
		}
		//ADC���Ƃ̃T���v�����O�^�C��(0-1023)�@val+2�̃N���b�N���������T���v�����O�ɂ�����H
		template<>
		void adc_block::sampling_time<4>(unsigned char val_){
			ADC4TIMEbits.SAMC = val_;
		}
		template<>
		unsigned char adc_block::sampling_time<4>(){
			return ADC4TIMEbits.SAMC;
		}
		//ADC��bit���x�@resolution_mode����I��
		template<>
		void adc_block::resolution_bits<4>(unsigned char val_){
			ADC4TIMEbits.SELRES = val_;
		}
		template<>
		unsigned char adc_block::resolution_bits<4>(){
			return ADC4TIMEbits.SELRES;
		}
		//excluded ADC��p�@���蓖�Ă̕ʂ�pinw���g����
		template<>
		void adc_block::use_alternative_input_pin<4>(bool val_){
			ADCTRGMODEbits.SH4ALT = val_;
		}
		template<>
		bool adc_block::use_alternative_input_pin<4>(){
			return ADCTRGMODEbits.SH4ALT;
		}
		//ADC���Ƃ�clock�X�^�[�g
		template<>
		void adc_block::adc_clock_enable<4>(bool val_){
			ADCANCONbits.ANEN4 = val_;
		}
		template<>
		bool adc_block::adc_clock_enable<4>(){
			return ADCANCONbits.ANEN4;
		}
		//ADC���Ƃ̃N���b�N�����m�F�@clock_enable���work_ready��҂�
		template<>
		bool adc_block::adc_work_ready<4>(){
			return ADCANCONbits.WKRDY4;
		}
		//ADC���Ƃ̂��Ƃ̃^�X�N�X�^�[�g work_ready�ɂȂ�����work_enable����ƁA���p����������
		template<>
		void adc_block::adc_work_enable(bool val_){
			ADCCON3bits.DIGEN4 = val_;
		}
		template<>
		bool adc_block::adc_work_enable(){
			return ADCCON3bits.DIGEN4;
		}
	#endif
	#ifdef ADC7_SHARED
		//ADC���Ƃ̌ŗL�̃N���b�N������(1-127) ���̒l��2�{�̎����ɂȂ�
		template<>
		void adc_block::adc_clock_div<7>(unsigned char val_){ ADCCON2bits.ADCDIV = val_; }
		template<>
		unsigned char adc_block::adc_clock_div<7>(){ return ADCCON2bits.ADCDIV; }
		//ADC���Ƃ̃T���v�����O�^�C��(0-1023)�@val+2�̃N���b�N���������T���v�����O�ɂ�����H
		template<>
		void adc_block::sampling_time<7>(unsigned char val_){ ADCCON2bits.SAMC = val_; }
		template<>
		unsigned char adc_block::sampling_time<7>(){ return ADCCON2bits.SAMC; }
		//ADC��bit���x�@resolution_mode����I��
		template<>
		void adc_block::resolution_bits<7>(unsigned char val_){ { ADCCON1bits.SELRES = val_; }
		template<>
		unsigned char adc_block::resolution_bits<7>(){ return ADCCON1bits.SELRES; }
		//excluded ADC��p�@���蓖�Ă̕ʂ�pinw���g����
		template<>
		void adc_block::use_alternative_input_pin<7>(bool val_){}
		template<>
		bool adc_block::use_alternative_input_pin<7>(){return false;}
		//ADC���Ƃ�clock�X�^�[�g
		template<>
		void adc_block::adc_clock_enable<7>(bool val_){ADCANCONbits.ANEN7 = val_;}
		template<>
		bool adc_block::adc_clock_enable<7>(){return ADCANCONbits.ANEN7;}
		//ADC���Ƃ̃N���b�N�����m�F�@clock_enable���work_ready��҂�
		template<>
		bool adc_block::adc_work_ready<7>(){return ADCANCONbits.WKRDY7;}
		//ADC���Ƃ̂��Ƃ̃^�X�N�X�^�[�g work_ready�ɂȂ�����work_enable����ƁA���p����������
		template<>
		void adc_block::adc_work_enable(bool val_){ ADCCON3bits.DIGEN7 = val_; }
		template<>
		bool adc_block::adc_work_enable(){return ADCCON3bits.DIGEN7;}
	#endif
	}
}
#
#endif
