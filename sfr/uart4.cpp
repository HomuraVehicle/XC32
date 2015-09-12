#ifndef XC32_SFR_UART4_CPP_INC
#define XC32_SFR_UART4_CPP_INC 100
#
#include"uart4.hpp"

#if defined(XC32_PIC32MX)
#	ifndef XC32_SFR_UART4_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_uart4_interrupt(void) {
		static xc32::sfr::uart4 UART4;

		if(UART4.tx_interrupt_flag()) {
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(UART4.tx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(UART4.tx_interrupt_function()))();
			}
			UART4.tx_interrupt_flag(false);
		} else if(UART4.rx_interrupt_flag()) {
			if(UART4.rx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(UART4.rx_interrupt_function()))();
			}
			UART4.rx_interrupt_flag(false);
			UART4.rx_buf_overflow(false);
		} else return;
	}
}
#	endif
#elif defined(XC32_PIC32MZ)
#	ifndef XC32_SFR_UART4_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_uart4_tx_interrupt(void) {
		static xc32::sfr::uart4 UART4;

		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(UART4.tx_interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(UART4.tx_interrupt_function()))();
		}
		UART4.tx_interrupt_flag(false);
	}
	void x_xc32_sfr_uart4_rx_interrupt(void) {
		static xc32::sfr::uart4 UART4;

		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(UART4.rx_interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(UART4.rx_interrupt_function()))();
		}
		UART4.rx_interrupt_flag(false);
		UART4.rx_buf_overflow(false);
	}
}
#	endif
#endif
namespace xc32{
	namespace sfr{
		interrupt::function* uart4::tx_interrupt_ptr;
		interrupt::function* uart4::rx_interrupt_ptr;
		const unsigned char uart4::tx_ipl = XC32_UART4_TX_IPL;
		const unsigned char uart4::rx_ipl = XC32_UART4_RX_IPL;
	}
}

#
#endif
