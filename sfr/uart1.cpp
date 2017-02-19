#ifndef XC32_SFR_UART1_CPP_INC
#define XC32_SFR_UART1_CPP_INC 100
#
#include"uart1.hpp"

#if defined(XC32_PIC32MX)
#	ifndef XC32_SFR_UART1_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_uart1_interrupt(void) {
		static xc32::sfr::uart1 UART1;

		if(UART1.tx_interrupt_flag()) {
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(UART1.tx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(UART1.tx_interrupt_function()))();
			}
			__asm("nop");
			UART1.tx_interrupt_flag(false);
			return;
		} else if(UART1.rx_interrupt_flag()) {
			if(UART1.rx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(UART1.rx_interrupt_function()))();
			}
			__asm("nop");
			UART1.rx_interrupt_flag(false);
			__asm("nop");
			UART1.rx_buf_overflow(false);
			return;
		} else return;
	}
}
#	endif
#elif defined(XC32_PIC32MZ)
#	ifndef XC32_SFR_UART1_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_uart1_tx_interrupt(void) {
		static xc32::sfr::uart1 UART1;

		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(UART1.tx_interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(UART1.tx_interrupt_function()))();
		}
		UART1.tx_interrupt_flag(false);
	}
	void x_xc32_sfr_uart1_rx_interrupt(void) {
		static xc32::sfr::uart1 UART1;

		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(UART1.rx_interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(UART1.rx_interrupt_function()))();
		}
		UART1.rx_interrupt_flag(false);
		UART1.rx_buf_overflow(false);
	}
}
#	endif
#endif
namespace xc32{
	namespace sfr{
		interrupt::function* uart1::tx_interrupt_ptr;
		interrupt::function* uart1::rx_interrupt_ptr;
		const unsigned char uart1::tx_ipl=XC32_UART1_TX_IPL;
		const unsigned char uart1::rx_ipl=XC32_UART1_RX_IPL;
	}
}

#
#endif
