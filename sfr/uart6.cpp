#ifndef XC32_SFR_UART6_CPP_INC
#define XC32_SFR_UART6_CPP_INC 100
#
#include"uart6.hpp"

#if defined(XC32_PIC32MX)
#	ifndef XC32_SFR_UART6_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_uart6_interrupt(void) {
		static xc32::sfr::uart6 UART6;

		if(UART6.tx_interrupt_flag()) {
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(UART6.tx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(UART6.tx_interrupt_function()))();
			}
			UART6.tx_interrupt_flag(false);
		} else if(UART6.rx_interrupt_flag()) {
			if(UART6.rx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(UART6.rx_interrupt_function()))();
			}
			UART6.rx_interrupt_flag(false);
			UART6.rx_buf_overflow(false);
		} else return;
	}
}
#	endif
#elif defined(XC32_PIC32MZ)
#	ifndef XC32_SFR_UART6_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_uart6_tx_interrupt(void) {
		static xc32::sfr::uart6 UART6;

		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(UART6.tx_interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(UART6.tx_interrupt_function()))();
		}
		UART6.tx_interrupt_flag(false);
	}
	void x_xc32_sfr_uart6_rx_interrupt(void) {
		static xc32::sfr::uart6 UART6;

		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(UART6.rx_interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(UART6.rx_interrupt_function()))();
		}
		UART6.rx_interrupt_flag(false);
		UART6.rx_buf_overflow(false);
	}
}
#	endif
#endif
namespace xc32{
	namespace sfr{
		interrupt::function* uart6::tx_interrupt_ptr;
		interrupt::function* uart6::rx_interrupt_ptr;
		const unsigned char uart6::tx_ipl = XC32_UART6_TX_IPL;
		const unsigned char uart6::rx_ipl = XC32_UART6_RX_IPL;
	}
}

#
#endif
