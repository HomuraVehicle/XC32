#ifndef XC32_SFR_ADC1_CPP_INC
#define XC32_SFR_ADC1_CPP_INC 100
#
#include"adc1.hpp"

#if defined(XC32_PIC32MX)
#	ifndef XC32_SFR_ADC1_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_adc1_interrupt(void){
		static xc32::sfr::adc1 ADC1;

		if(ADC1.tx_interrupt_flag()){
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(ADC1.tx_interrupt_function()){
				(*const_cast<xc32::sfr::interrupt::function*>(ADC1.tx_interrupt_function()))();
			}
			__asm("nop");
			ADC1.tx_interrupt_flag(false);
			return;
		} else if(ADC1.rx_interrupt_flag()){
			if(ADC1.rx_interrupt_function()){
				(*const_cast<xc32::sfr::interrupt::function*>(ADC1.rx_interrupt_function()))();
			}
			__asm("nop");
			ADC1.rx_interrupt_flag(false);
			__asm("nop");
			ADC1.rx_buf_overflow(false);
			return;
		} else return;
	}
}
#	endif
#elif defined(XC32_PIC32MZ)
#	ifndef XC32_SFR_ADC1_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_adc1_tx_interrupt(void){
		static xc32::sfr::adc_block ADC1;

		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(ADC1.tx_interrupt_function()){
			(*const_cast<xc32::sfr::interrupt::function*>(ADC1.global_scan_end_interrupt_ptr()))();
		}
		ADC1.tx_interrupt_flag(false);
	}
	void x_xc32_sfr_adc1_rx_interrupt(void){
		static xc32::sfr::adc_block ADC1;

		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(ADC1.rx_interrupt_function()){
			(*const_cast<xc32::sfr::interrupt::function*>(ADC1.global_scan_end_interrupt_ptr()))();
		}
		ADC1.rx_interrupt_flag(false);
		ADC1.rx_buf_overflow(false);
	}
}
#	endif
#endif
namespace xc32{
	namespace sfr{
		interrupt::function* adc_block::global_scan_end_interrupt_ptr;
		const unsigned char adc_block::tx_ipl = XC32_ADC1_TX_IPL;
		const unsigned char adc_block::rx_ipl = XC32_ADC1_RX_IPL;
	}
}

#
#endif
