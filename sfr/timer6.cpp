#ifndef XC32_SFR_TIMER6_CPP_INC
#define XC32_SFR_TIMER6_CPP_INC 100
#
#include"timer6.hpp"

#ifndef XC32_SFR_TIMER6_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_timer6_interrupt(void) {
		static xc32::sfr::timer6 Timer6;
		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(Timer6.interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(Timer6.interrupt_function()))();
		}
		Timer6.interrupt_flag(false);
	}
}
#endif
namespace xc32 {
	namespace sfr {
		interrupt::function* timer6::interrupt_ptr;
		const unsigned char timer6::ipl = XC32_TIMER6_IPL;
	}
}

#
#endif
