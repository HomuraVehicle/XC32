#ifndef XC32LIB_SFR_UART3_CPP_INC
#define XC32LIB_SFR_UART3_CPP_INC 100
#
#include"uart3.hpp"

#if defined(XC32LIB_PIC32MX)
#	ifndef XC32LIB_SFR_UART3_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_uart3_interrupt(void) {
		static xc32::sfr::uart3 UART3;

		if(UART3.tx_interrupt_flag()) {
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(UART3.tx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(UART3.tx_interrupt_function()))();
			}
			UART3.tx_interrupt_flag(false);
		} else if(UART3.rx_interrupt_flag()) {
			if(UART3.rx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(UART3.rx_interrupt_function()))();
			}
			UART3.rx_interrupt_flag(false);
			UART3.rx_buf_overflow(false);
		} else return;
	}
}
#	endif
#elif defined(XC32LIB_PIC32MZ)
#	ifndef XC32LIB_SFR_UART3_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_uart3_tx_interrupt(void) {
		static xc32::sfr::uart3 UART3;

		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(UART3.tx_interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(UART3.tx_interrupt_function()))();
		}
		UART3.tx_interrupt_flag(false);
	}
	void x_xc32_sfr_uart3_rx_interrupt(void) {
		static xc32::sfr::uart3 UART3;

		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(UART3.rx_interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(UART3.rx_interrupt_function()))();
		}
		UART3.rx_interrupt_flag(false);
		UART3.rx_buf_overflow(false);
	}
}
#	endif
#endif
namespace xc32{
	namespace sfr{
		interrupt::function* uart3::tx_interrupt_ptr;
		interrupt::function* uart3::rx_interrupt_ptr;
		const unsigned char uart3::tx_ipl = XC32LIB_UART3_TX_IPL;
		const unsigned char uart3::rx_ipl = XC32LIB_UART3_RX_IPL;
	}
}

#
#endif
