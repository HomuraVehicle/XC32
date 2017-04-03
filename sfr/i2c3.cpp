#ifndef XC32_SFR_I2C3_CPP_INC
#define XC32_SFR_I2C3_CPP_INC 100
#
#include"i2c3.hpp"

#ifndef XC32_SFR_I2C3_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_i2c3_interrupt(void) {
		static xc32::sfr::i2c3 I2C3;

		if(I2C3.interrupt_flag()) {
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(I2C3.interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(I2C3.interrupt_function()))();
			}
			I2C3.interrupt_flag(false);
		}

	}
}
#endif

namespace xc32{
	namespace sfr{
		interrupt::function* i2c3::interrupt_ptr;
		const unsigned char i2c3::ipl = XC32_I2C3_IPL;
	}
}

#
#endif
