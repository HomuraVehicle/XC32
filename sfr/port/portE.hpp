#ifndef XC32_SFR_PORTE_INC
#define XC32_SFR_PORTE_INC 100
#
#include"device_include.h"
#include<XCBase/constexpr_no.hpp>
namespace xc32 {
	namespace sfr{
		struct portE{
			#ifdef PORT_E0
			struct pin0{
				bool port()const volatile {return PORTEbits.RE0; }
				#ifndef PORT_IN_E0
				void lat(bool val) {LATEbits.LATE0=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISEbits.TRISE0=val; }
				void opendrain(bool val) {ODCEbits.ODCE0=val; }
				#ifdef PORT_ANALOG_E0
				void analog(bool val) {ANSELEbits.ANSE0=val; }
				typedef constexpr_no<PORT_ANALOG_E0> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_E1
			struct pin1{
				bool port()const volatile {return PORTEbits.RE1; }
				#ifndef PORT_IN_E1
				void lat(bool val) {LATEbits.LATE1=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISEbits.TRISE1=val; }
				void opendrain(bool val) {ODCEbits.ODCE1=val; }
				#ifdef PORT_ANALOG_E1
				void analog(bool val) {ANSELEbits.ANSE1=val; }
				typedef constexpr_no<PORT_ANALOG_E1> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_E2
			struct pin2{
				bool port()const volatile {return PORTEbits.RE2; }
				#ifndef PORT_IN_E2
				void lat(bool val) {LATEbits.LATE2=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISEbits.TRISE2=val; }
				void opendrain(bool val) {ODCEbits.ODCE2=val; }
				#ifdef PORT_ANALOG_E2
				void analog(bool val) {ANSELEbits.ANSE2=val; }
				typedef constexpr_no<PORT_ANALOG_E2> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_E3
			struct pin3{
				bool port()const volatile {return PORTEbits.RE3; }
				#ifndef PORT_IN_E3
				void lat(bool val) {LATEbits.LATE3=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISEbits.TRISE3=val; }
				void opendrain(bool val) {ODCEbits.ODCE3=val; }
				#ifdef PORT_ANALOG_E3
				void analog(bool val) {ANSELEbits.ANSE3=val; }
				typedef constexpr_no<PORT_ANALOG_E3> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_E4
			struct pin4{
				bool port()const volatile {return PORTEbits.RE4; }
				#ifndef PORT_IN_E4
				void lat(bool val) {LATEbits.LATE4=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISEbits.TRISE4=val; }
				void opendrain(bool val) {ODCEbits.ODCE4=val; }
				#ifdef PORT_ANALOG_E4
				void analog(bool val) {ANSELEbits.ANSE4=val; }
				typedef constexpr_no<PORT_ANALOG_E4> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_E5
			struct pin5{
				bool port()const volatile {return PORTEbits.RE5; }
				#ifndef PORT_IN_E5
				void lat(bool val) {LATEbits.LATE5=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISEbits.TRISE5=val; }
				void opendrain(bool val) {ODCEbits.ODCE5=val; }
				#ifdef PORT_ANALOG_E5
				void analog(bool val) {ANSELEbits.ANSE5=val; }
				typedef constexpr_no<PORT_ANALOG_E5> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_E6
			struct pin6{
				bool port()const volatile {return PORTEbits.RE6; }
				#ifndef PORT_IN_E6
				void lat(bool val) {LATEbits.LATE6=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISEbits.TRISE6=val; }
				void opendrain(bool val) {ODCEbits.ODCE6=val; }
				#ifdef PORT_ANALOG_E6
				void analog(bool val) {ANSELEbits.ANSE6=val; }
				typedef constexpr_no<PORT_ANALOG_E6> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_E7
			struct pin7{
				bool port()const volatile {return PORTEbits.RE7; }
				#ifndef PORT_IN_E7
				void lat(bool val) {LATEbits.LATE7=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISEbits.TRISE7=val; }
				void opendrain(bool val) {ODCEbits.ODCE7=val; }
				#ifdef PORT_ANALOG_E7
				void analog(bool val) {ANSELEbits.ANSE7=val; }
				typedef constexpr_no<PORT_ANALOG_E7> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_E8
			struct pin8{
				bool port()const volatile {return PORTEbits.RE8; }
				#ifndef PORT_IN_E8
				void lat(bool val) {LATEbits.LATE8=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISEbits.TRISE8=val; }
				void opendrain(bool val) {ODCEbits.ODCE8=val; }
				#ifdef PORT_ANALOG_E8
				void analog(bool val) {ANSELEbits.ANSE8=val; }
				typedef constexpr_no<PORT_ANALOG_E8> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_E9
			struct pin9{
				bool port()const volatile {return PORTEbits.RE9; }
				#ifndef PORT_IN_E9
				void lat(bool val) {LATEbits.LATE9=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISEbits.TRISE9=val; }
				void opendrain(bool val) {ODCEbits.ODCE9=val; }
				#ifdef PORT_ANALOG_E9
				void analog(bool val) {ANSELEbits.ANSE9=val; }
				typedef constexpr_no<PORT_ANALOG_E9> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_E10
			struct pin10{
				bool port()const volatile {return PORTEbits.RE10; }
				#ifndef PORT_IN_E10
				void lat(bool val) {LATEbits.LATE10=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISEbits.TRISE10=val; }
				void opendrain(bool val) {ODCEbits.ODCE10=val; }
				#ifdef PORT_ANALOG_E10
				void analog(bool val) {ANSELEbits.ANSE10=val; }
				typedef constexpr_no<PORT_ANALOG_E10> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_E11
			struct pin11{
				bool port()const volatile {return PORTEbits.RE11; }
				#ifndef PORT_IN_E11
				void lat(bool val) {LATEbits.LATE11=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISEbits.TRISE11=val; }
				void opendrain(bool val) {ODCEbits.ODCE11=val; }
				#ifdef PORT_ANALOG_E11
				void analog(bool val) {ANSELEbits.ANSE11=val; }
				typedef constexpr_no<PORT_ANALOG_E11> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_E12
			struct pin12{
				bool port()const volatile {return PORTEbits.RE12; }
				#ifndef PORT_IN_E12
				void lat(bool val) {LATEbits.LATE12=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISEbits.TRISE12=val; }
				void opendrain(bool val) {ODCEbits.ODCE12=val; }
				#ifdef PORT_ANALOG_E12
				void analog(bool val) {ANSELEbits.ANSE12=val; }
				typedef constexpr_no<PORT_ANALOG_E12> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_E13
			struct pin13{
				bool port()const volatile {return PORTEbits.RE13; }
				#ifndef PORT_IN_E13
				void lat(bool val) {LATEbits.LATE13=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISEbits.TRISE13=val; }
				void opendrain(bool val) {ODCEbits.ODCE13=val; }
				#ifdef PORT_ANALOG_E13
				void analog(bool val) {ANSELEbits.ANSE13=val; }
				typedef constexpr_no<PORT_ANALOG_E13> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_E14
			struct pin14{
				bool port()const volatile {return PORTEbits.RE14; }
				#ifndef PORT_IN_E14
				void lat(bool val) {LATEbits.LATE14=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISEbits.TRISE14=val; }
				void opendrain(bool val) {ODCEbits.ODCE14=val; }
				#ifdef PORT_ANALOG_E14
				void analog(bool val) {ANSELEbits.ANSE14=val; }
				typedef constexpr_no<PORT_ANALOG_E14> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_E15
			struct pin15{
				bool port()const volatile {return PORTEbits.RE15; }
				#ifndef PORT_IN_E15
				void lat(bool val) {LATEbits.LATE15=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISEbits.TRISE15=val; }
				void opendrain(bool val) {ODCEbits.ODCE15=val; }
				#ifdef PORT_ANALOG_E15
				void analog(bool val) {ANSELEbits.ANSE15=val; }
				typedef constexpr_no<PORT_ANALOG_E15> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
		};
	}
}
#
#endif
