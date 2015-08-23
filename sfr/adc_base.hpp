#ifndef XC32LIB_SFR_ADCBASE_INC
#define XC32LIB_SFR_ADCBASE_INC 100
#
namespace xc32 {
	namespace sfr {
		namespace adc {			
			enum vref_mode :unsigned int {
				vref_Vin_Gnd=0x00,
				vref_Vref_Gnd=0x01,
				vref_Vin_Vref=0x02,
				vref_Vref_Vref=0x03
			};

		}
	}
}
#
#endif
