#ifndef XC32LIB_SFR_RTCC_CPP_INC
#define XC32LIB_SFR_RTCC_CPP_INC 100
#
#include"rtcc.hpp"

#ifndef XC32LIB_SFR_RTCC_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_rtcc_interrupt(void) {
		static xc32::sfr::rtcc RTCC;

		if(RTCC.interrupt_flag()) {
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(RTCC.interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(RTCC.interrupt_function()))();
			}
			RTCC.interrupt_flag(false);
		}

	}
}
#endif

namespace xc32{
	namespace sfr{
		interrupt::function* rtcc::interrupt_ptr;
	}
}

#
#endif
