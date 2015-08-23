#ifndef XC32_SFR_TIMER8_CPP_INC
#define XC32_SFR_TIMER8_CPP_INC 100
#
#include"timer8.hpp"

#ifndef XC32LIB_SFR_TIMER8_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_timer8_interrupt(void) {
		static xc32::sfr::timer8 Timer8;
		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(Timer8.interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(Timer8.interrupt_function()))();
		}
		Timer8.interrupt_flag(false);
	}
}
#endif
namespace xc32 {
	namespace sfr {
		interrupt::function* timer8::interrupt_ptr;
		const unsigned char timer8::ipl = XC32LIB_TIMER8_IPL;
	}
}

#
#endif
