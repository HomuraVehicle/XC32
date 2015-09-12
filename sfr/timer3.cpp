#ifndef XC32_SFR_TIMER3_CPP_INC
#define XC32_SFR_TIMER3_CPP_INC 100
#
#include"timer3.hpp"

#ifndef XC32_SFR_TIMER3_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_timer3_interrupt(void) {
		static xc32::sfr::timer3 Timer3;
		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(Timer3.interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(Timer3.interrupt_function()))();
		}
		Timer3.interrupt_flag(false);
	}
}
#endif
namespace xc32 {
	namespace sfr {
		interrupt::function* timer3::interrupt_ptr;
		const unsigned char timer3::ipl = XC32_TIMER3_IPL;
	}
}

#
#endif
