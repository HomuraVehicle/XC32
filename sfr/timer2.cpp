#ifndef XC32_SFR_TIMER2_CPP_INC
#define XC32_SFR_TIMER2_CPP_INC 100
#
#include"timer2.hpp"

#ifndef XC32_SFR_TIMER2_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_timer2_interrupt(void) {
		static xc32::sfr::timer2 Timer2;
//		LATFbits.LATF5 = 1;
		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(Timer2.interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(Timer2.interrupt_function()))();
		}
		Timer2.interrupt_flag(false);
	}
}
#endif
namespace xc32 {
	namespace sfr {
		interrupt::function* timer2::interrupt_ptr;
		const unsigned char timer2::ipl = XC32_TIMER2_IPL;
	}
}

#
#endif
