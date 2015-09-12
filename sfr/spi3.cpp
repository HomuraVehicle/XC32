#ifndef XC32_SFR_SPI3_CPP_INC
#define XC32_SFR_SPI3_CPP_INC 100
#
#include"spi3.hpp"

#ifndef XC32_SFR_SPI3_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_spi3_interrupt(void) {
		static xc32::sfr::spi3 SPI3;
		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(SPI3.rx_interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(SPI3.rx_interrupt_function()))();
		}
		SPI3.rx_interrupt_flag(false);
		/*
		if(SPI3.tx_interrupt_flag()) {
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(SPI3.tx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(SPI3.tx_interrupt_function()))();
			}
			SPI3.tx_interrupt_flag(false);
		} else if(SPI3.rx_interrupt_flag()) {
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(SPI3.rx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(SPI3.rx_interrupt_function()))();
			}
			SPI3.rx_interrupt_flag(false);
		} else return;
		*/
	}
}
#endif

namespace xc32{
	namespace sfr{
		interrupt::function* spi3::tx_interrupt_ptr;
		interrupt::function* spi3::rx_interrupt_ptr;
		const unsigned char spi3::rx_ipl = XC32_SPI3_RX_IPL;
	}
}

#
#endif
