#ifndef XC32_SFR_I2C2_CPP_INC
#define XC32_SFR_I2C2_CPP_INC 100
#
#include"i2c2.hpp"

#ifndef XC32_SFR_I2C2_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_i2c2_interrupt(void) {
		static xc32::sfr::i2c2 I2C2;

		if(I2C2.interrupt_flag()) {
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(I2C2.interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(I2C2.interrupt_function()))();
			}
			I2C2.interrupt_flag(false);
		}

	}
}
#endif

namespace xc32{
	namespace sfr{
		interrupt::function* i2c2::interrupt_ptr;
		const unsigned char i2c2::ipl = XC32_I2C2_IPL;
	}
}

#
#endif
