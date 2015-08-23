#ifndef XC32_SFR_TIMER1_CPP_INC
#define XC32_SFR_TIMER1_CPP_INC 100
#
#include"timer1.hpp"

#ifndef XC32LIB_SFR_TIMER1_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_timer1_interrupt(void) {
		static xc32::sfr::timer1 Timer1;
		//private�����o�̊֐��|�C���^�����s���邽�߂ɁA������const���O���Ă���
		if(Timer1.interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(Timer1.interrupt_function()))();
		}
		Timer1.interrupt_flag(false);
	}
}
#endif
namespace xc32 {
	namespace sfr {
		interrupt::function* timer1::interrupt_ptr;
		const unsigned char timer1::ipl = XC32LIB_TIMER1_IPL;
	}
}

#
#endif
