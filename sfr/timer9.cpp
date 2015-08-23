#ifndef XC32_SFR_TIMER9_CPP_INC
#define XC32_SFR_TIMER9_CPP_INC 100
#
#include"timer9.hpp"

#ifndef XC32LIB_SFR_TIMER9_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_timer9_interrupt(void) {
		static xc32::sfr::timer9 Timer9;
		//privateメンバの関数ポインタを実行するために、強引にconstを外している
		if(Timer9.interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(Timer9.interrupt_function()))();
		}
		Timer9.interrupt_flag(false);
	}
}
#endif
namespace xc32 {
	namespace sfr {
		interrupt::function* timer9::interrupt_ptr;
		const unsigned char timer9::ipl = XC32LIB_TIMER9_IPL;
	}
}

#
#endif
