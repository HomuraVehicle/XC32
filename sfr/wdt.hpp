#ifndef XC32LIB_SFR_WDT_INC
#define XC32LIB_SFR_WDT_INC 100
#
//*********** WDT�֘A�֐� ***********************
#include<XC32Lib_config.hpp>
#include"device_include.h"
#include"exclusive_mixin.hpp"
#include"sfr_register_mixin.hpp"

#define XC32LIB_SFR_WDT_CLERAKEY 0x5743
namespace xc32{
	namespace sfr{
		struct wdt:public sfr_register_mixin<wdt>, public exclusive_mixin<wdt>{
			//WatchDog timer enable bit : WDTCONbits.ON
			void enable(bool val_){WDTCONbits.ON=static_cast<unsigned char>(val_);}
			bool enable()const{return static_cast<bool>(WDTCONbits.ON);}
			//WatchDog timer Reset bit : WTDCONbits.WDTCLR
			void clear(){
#if defined(XC32LIB_PIC32XZ)
				WDTCONbits.WDTCLR=1;
#elif defined (XC32LIB_PIC32MZ)
				WDTCONbits.WDTCLRKEY=XC32LIB_SFR_WDT_CLERAKEY;
#else
#error unknown device!
#endif
			}
		};
	}
}

#
#endif