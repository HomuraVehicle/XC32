#ifndef XC32_SFR_SPI1_CPP_INC
#define XC32_SFR_SPI1_CPP_INC 100
#
#include"spi1.hpp"

#ifndef XC32_SFR_SPI1_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_spi1_interrupt(void) {
		static xc32::sfr::spi1 SPI1;
		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(SPI1.rx_interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(SPI1.rx_interrupt_function()))();
		}
		SPI1.rx_interrupt_flag(false);
	/*
		if(SPI1.tx_interrupt_flag()) {
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(SPI1.tx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(SPI1.tx_interrupt_function()))();
			}
			SPI1.tx_interrupt_flag(false);
		} else if(SPI1.rx_interrupt_flag()) {
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(SPI1.rx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(SPI1.rx_interrupt_function()))();
			}
			SPI1.rx_interrupt_flag(false);
		} else return;*/
	}
}
#endif

namespace xc32{
	namespace sfr{
		interrupt::function* spi1::tx_interrupt_ptr;
		interrupt::function* spi1::rx_interrupt_ptr;
		const unsigned char spi1::rx_ipl = XC32_SPI1_RX_IPL;
	}
}

#
#endif
