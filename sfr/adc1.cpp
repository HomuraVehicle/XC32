#ifndef XC32_SFR_ADC1_CPP_INC
#define XC32_SFR_ADC1_CPP_INC 100
#
#include"adc1.hpp"
#include"interrupt.hpp"

#if defined(XC32_PIC32MX)
#	ifndef XC32_SFR_ADC1_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_adc1_global_convert_end_interrupt(void);
}
#	endif
#elif defined(XC32_PIC32MZ)
#	ifndef XC32_SFR_ADC1_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_adc1_global_convert_end_interrupt(void){
		static xc32::sfr::adc_block ADC1;

		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(ADC1.global_convert_end_interrupt_function()){
			(*const_cast<xc32::sfr::interrupt::function*>(ADC1.global_convert_end_interrupt_function()))();
		}
		ADC1.global_convert_end_interrupt_flag(false);
	}
}
#	endif
#endif
namespace xc32{
	namespace sfr{
		interrupt::function* adc_block::global_convert_end_interrupt_ptr;
		const unsigned char adc_block::global_convert_end_ipl = XC32_ADC1_IPL;
	}
}

#
#endif
