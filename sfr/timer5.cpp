#ifndef XC32_SFR_TIMER5_CPP_INC
#define XC32_SFR_TIMER5_CPP_INC 100
#
#include"timer5.hpp"

#ifndef XC32LIB_SFR_TIMER5_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_timer5_interrupt(void) {
		static xc32::sfr::timer5 Timer5;
		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(Timer5.interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(Timer5.interrupt_function()))();
		}
		Timer5.interrupt_flag(false);
	}
}
#endif
namespace xc32 {
	namespace sfr {
		interrupt::function* timer5::interrupt_ptr;
		const unsigned char timer5::ipl = XC32LIB_TIMER5_IPL;
	}
}

#
#endif
