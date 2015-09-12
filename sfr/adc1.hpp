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
		struct adc1 :public sfr_register_mixin<adc1>, public exclusive_mixin<adc1> {
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
			//ADC�N���b�N��(T_Q)�r�b�g�C1:Tcy,2:REFCLK3,3:FRC�I�V���[�^�o��,0:�\��ς�
			void clock_select(unsigned char val_) { ADCCON3bits.ADCSEL = val_; }
			unsigned char clock_select()const { return ADCCON3bits.ADCSEL; }
			//ADC�N���b�N������r�b�g(0�`127)�Fclock_div==0�Ȃ�T_AD = T_Q ,T_AD = 2 * T_Q * clock_div
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
			//ADC���̓X�L�����I���r�b�g(AN0�`AN31�܂�)
			//void scan_select1(uint32 val_) { AD1CSS1 = val_; }
			//uint32 scan_select1()const { return AD1CSS1; }
			//ADC���̓X�L�����I���r�b�g(AN32�`AN44�܂�)
			//void scan_select2(uint16 val_) { AD1CSS2 = val_; }
			//uint16 scan_select2()const { return static_cast<uint16>(AD1CSS2); }
			//ADC�f�[�^���f�B�r�b�g(AN0�`AN31�܂�,�f�[�^��ǂݏo���ƃN���A�����)
			//uint32 data_ready1()const { return AD1DSTAT1; }
			//ADC�f�[�^���f�B�r�b�g(AN32�`AN44�܂�,�f�[�^��ǂݏo���ƃN���A�����)
			//uint32 data_ready2()const { return AD1DSTAT2; }
		};
	}
}
#
#endif
