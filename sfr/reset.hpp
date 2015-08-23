#ifndef XC32LIB_SFR_RESET_INC
#define XC32LIB_SFR_RESET_INC 100
#
#include "device_include.h"

namespace xc32{
	namespace sfr{
		struct reset{
			//configuration mismatch reset flag : RCONbits.CMR
			bool configuration_mismatch_reset()const{return static_cast<bool>(RCONbits.CMR);}
			//external reset flag : RCONbits.EXTR
			bool external_reset()const{return static_cast<bool>(RCONbits.EXTR);}
			//software reset flag : RCONbits.SWR
			bool software_reset()const{return static_cast<bool>(RCONbits.SWR);}
			//watchdog time-out flag : RCONbits.WDTO
			bool wdt_timeout_reset()const{return static_cast<bool>(RCONbits.WDTO);}
			//brown-out reset flag : RCONbits.BOR
			bool brownout_reset()const{return static_cast<bool>(RCONbits.BOR);}
			//power-on reset flag : RCONbits.POR
			bool poweron_reset()const{return static_cast<bool>(RCONbits.POR);}
		};
	}
}

#
#endif
