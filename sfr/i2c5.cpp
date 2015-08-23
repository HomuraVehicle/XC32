#ifndef XC32LIB_SFR_I2C5_CPP_INC
#define XC32LIB_SFR_I2C5_CPP_INC 100
#
#include"i2c5.hpp"

#ifndef XC32LIB_SFR_I2C5_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_i2c5_interrupt(void) {
		static xc32::sfr::i2c5 I2C5;

		if(I2C5.interrupt_flag()) {
			//privateメンバの関数ポインタを実行するために、強引にconstを外している
			if(I2C5.interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(I2C5.interrupt_function()))();
			}
			I2C5.interrupt_flag(false);
		}

	}
}
#endif

namespace xc32{
	namespace sfr{
		interrupt::function* i2c5::interrupt_ptr;
		const unsigned char i2c5::ipl = XC32LIB_I2C5_IPL;
	}
}

#
#endif
