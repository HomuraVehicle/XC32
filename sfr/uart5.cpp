#ifndef XC32_SFR_UART5_CPP_INC
#define XC32_SFR_UART5_CPP_INC 100
#
#include"uart5.hpp"

#if defined(XC32_PIC32MX)
#	ifndef XC32_SFR_UART5_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_uart5_interrupt(void) {
		static xc32::sfr::uart5 UART5;

		if(UART5.tx_interrupt_flag()) {
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(UART5.tx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(UART5.tx_interrupt_function()))();
			}
			UART5.tx_interrupt_flag(false);
		} else if(UART5.rx_interrupt_flag()) {
			if(UART5.rx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(UART5.rx_interrupt_function()))();
			}
			UART5.rx_interrupt_flag(false);
			UART5.rx_buf_overflow(false);
		} else return;
	}
}
#	endif
#elif defined(XC32_PIC32MZ)
#	ifndef XC32_SFR_UART5_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_uart5_tx_interrupt(void) {
		static xc32::sfr::uart5 UART5;

		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(UART5.tx_interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(UART5.tx_interrupt_function()))();
		}
		UART5.tx_interrupt_flag(false);
	}
	void x_xc32_sfr_uart5_rx_interrupt(void) {
		static xc32::sfr::uart5 UART5;

		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(UART5.rx_interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(UART5.rx_interrupt_function()))();
		}
		UART5.rx_interrupt_flag(false);
		UART5.rx_buf_overflow(false);
	}
}
#	endif
#endif
namespace xc32{
	namespace sfr{
		interrupt::function* uart5::tx_interrupt_ptr;
		interrupt::function* uart5::rx_interrupt_ptr;
		const unsigned char uart5::tx_ipl = XC32_UART5_TX_IPL;
		const unsigned char uart5::rx_ipl = XC32_UART5_RX_IPL;
	}
}

#
#endif
