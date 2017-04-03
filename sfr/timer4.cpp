#ifndef XC32_SFR_TIMER4_CPP_INC
#define XC32_SFR_TIMER4_CPP_INC 100
#
#include"timer4.hpp"

#ifndef XC32_SFR_TIMER4_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_timer4_interrupt(void) {
		static xc32::sfr::timer4 Timer4;
		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(Timer4.interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(Timer4.interrupt_function()))();
		}
		Timer4.interrupt_flag(false);
	}
}
#endif
namespace xc32 {
	namespace sfr {
		interrupt::function* timer4::interrupt_ptr;
		const unsigned char timer4::ipl = XC32_TIMER4_IPL;
	}
}

#
#endif
