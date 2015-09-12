#ifndef XC32_SFR_UART2_CPP_INC
#define XC32_SFR_UART2_CPP_INC 100
#
#include"uart2.hpp"

#if defined(XC32_PIC32MX)
#	ifndef XC32_SFR_UART2_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_uart2_interrupt(void) {
		static xc32::sfr::uart2 UART2;

		if(UART2.tx_interrupt_flag()) {
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(UART2.tx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(UART2.tx_interrupt_function()))();
			}
			UART2.tx_interrupt_flag(false);
		} else if(UART2.rx_interrupt_flag()) {
			if(UART2.rx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(UART2.rx_interrupt_function()))();
			}
			UART2.rx_interrupt_flag(false);
			UART2.rx_buf_overflow(false);
		} else return;
	}
}
#	endif
#elif defined(XC32_PIC32MZ)
#	ifndef XC32_SFR_UART2_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_uart2_tx_interrupt(void) {
		static xc32::sfr::uart2 UART2;

		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(UART2.tx_interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(UART2.tx_interrupt_function()))();
		}
		UART2.tx_interrupt_flag(false);
	}
	void x_xc32_sfr_uart2_rx_interrupt(void) {
		static xc32::sfr::uart2 UART2;

		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(UART2.rx_interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(UART2.rx_interrupt_function()))();
		}
		UART2.rx_interrupt_flag(false);
		UART2.rx_buf_overflow(false);
	}
}
#	endif
#endif
namespace xc32{
	namespace sfr{
		interrupt::function* uart2::tx_interrupt_ptr;
		interrupt::function* uart2::rx_interrupt_ptr;
		const unsigned char uart2::tx_ipl = XC32_UART2_TX_IPL;
		const unsigned char uart2::rx_ipl = XC32_UART2_RX_IPL;
	}
}

#
#endif
