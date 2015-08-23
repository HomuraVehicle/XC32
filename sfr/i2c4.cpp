#ifndef XC32LIB_SFR_I2C4_CPP_INC
#define XC32LIB_SFR_I2C4_CPP_INC 100
#
#include"i2c4.hpp"

#ifndef XC32LIB_SFR_I2C4_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_i2c4_interrupt(void) {
		static xc32::sfr::i2c4 I2C4;

		if(I2C4.interrupt_flag()) {
			//private�����o�̊֐��|�C���^�����s���邽�߂ɁA������const���O���Ă���
			if(I2C4.interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(I2C4.interrupt_function()))();
			}
			I2C4.interrupt_flag(false);
		}

	}
}
#endif

namespace xc32{
	namespace sfr{
		interrupt::function* i2c4::interrupt_ptr;
		const unsigned char i2c4::ipl = XC32LIB_I2C4_IPL;
	}
}

#
#endif