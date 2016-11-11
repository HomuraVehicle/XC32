#ifndef XC32_SFR_ADCBASE_INC
#define XC32_SFR_ADCBASE_INC 100
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
			enum resolution_mode :unsigned{
				resolution_12bits = 0x11,
				resolution_10bits = 0x10,
				resolution_8bits = 0x01,
				resolution_6bits = 0x00
			};

		}
	}
}
#
#endif
