#ifndef XC32LIB_SFR_SPI4_CPP_INC
#define XC32LIB_SFR_SPI4_CPP_INC 100
#
#include"spi4.hpp"

#ifndef XC32LIB_SFR_SPI4_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_spi4_interrupt(void) {
		static xc32::sfr::spi4 SPI4;
		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(SPI4.rx_interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(SPI4.rx_interrupt_function()))();
		}
		SPI4.rx_interrupt_flag(false);
		/*
		if(SPI4.tx_interrupt_flag()) {
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(SPI4.tx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(SPI4.tx_interrupt_function()))();
			}
			SPI4.tx_interrupt_flag(false);
		} else if(SPI4.rx_interrupt_flag()) {
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(SPI4.rx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(SPI4.rx_interrupt_function()))();
			}
			SPI4.rx_interrupt_flag(false);
		} else return;
		*/
	}
}
#endif

namespace xc32{
	namespace sfr{
		interrupt::function* spi4::tx_interrupt_ptr;
		interrupt::function* spi4::rx_interrupt_ptr;
		const unsigned char spi4::rx_ipl = XC32LIB_SPI4_RX_IPL;
	}
}

#
#endif
