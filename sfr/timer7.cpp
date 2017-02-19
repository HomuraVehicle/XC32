#ifndef XC32_SFR_TIMER7_CPP_INC
#define XC32_SFR_TIMER7_CPP_INC 100
#
#include"timer7.hpp"

#ifndef XC32_SFR_TIMER7_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_timer7_interrupt(void) {
		static xc32::sfr::timer7 Timer7;
		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(Timer7.interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(Timer7.interrupt_function()))();
		}
		Timer7.interrupt_flag(false);
	}
}
#endif
namespace xc32 {
	namespace sfr {
		interrupt::function* timer7::interrupt_ptr;
		const unsigned char timer7::ipl = XC32_TIMER7_IPL;
	}
}

#
#endif
