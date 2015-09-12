#ifndef XC32_SFR_SPI2_CPP_INC
#define XC32_SFR_SPI2_CPP_INC 100
#
#include"spi2.hpp"

#ifndef XC32_SFR_SPI2_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_spi2_interrupt(void) {
		static xc32::sfr::spi2 SPI2;
		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(SPI2.rx_interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(SPI2.rx_interrupt_function()))();
		}
		SPI2.rx_interrupt_flag(false);

		/*
		if(SPI2.tx_interrupt_flag()) {
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(SPI2.tx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(SPI2.tx_interrupt_function()))();
			}
			SPI2.tx_interrupt_flag(false);
		} else if(SPI2.rx_interrupt_flag()) {
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(SPI2.rx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(SPI2.rx_interrupt_function()))();
			}
			SPI2.rx_interrupt_flag(false);
		} else return;
		*/
	}
}
#endif

namespace xc32{
	namespace sfr{
		interrupt::function* spi2::tx_interrupt_ptr;
		interrupt::function* spi2::rx_interrupt_ptr;
		const unsigned char spi2::rx_ipl = XC32_SPI2_RX_IPL;
	}
}

#
#endif
