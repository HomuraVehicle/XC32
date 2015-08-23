#ifndef XC32LIB_SFR_PORTG_INC
#define XC32LIB_SFR_PORTG_INC 100
#
#include"device_include.h"
#include<XCBase/constexpr_no.hpp>
namespace xc32 {
	namespace sfr{
		struct portG{
			#ifdef PORT_G0
			struct pin0{
				bool port()const volatile {return PORTGbits.RG0; }
				#ifndef PORT_IN_G0
				void lat(bool val) {LATGbits.LATG0=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISGbits.TRISG0=val; }
				void opendrain(bool val) {ODCGbits.ODCG0=val; }
				#ifdef PORT_ANALOG_G0
				void analog(bool val) {ANSELGbits.ANSG0=val; }
				typedef constexpr_no<PORT_ANALOG_G0> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_G1
			struct pin1{
				bool port()const volatile {return PORTGbits.RG1; }
				#ifndef PORT_IN_G1
				void lat(bool val) {LATGbits.LATG1=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISGbits.TRISG1=val; }
				void opendrain(bool val) {ODCGbits.ODCG1=val; }
				#ifdef PORT_ANALOG_G1
				void analog(bool val) {ANSELGbits.ANSG1=val; }
				typedef constexpr_no<PORT_ANALOG_G1> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_G2
			struct pin2{
				bool port()const volatile {return PORTGbits.RG2; }
				#ifndef PORT_IN_G2
				void lat(bool val) {LATGbits.LATG2=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISGbits.TRISG2=val; }
				void opendrain(bool val) {ODCGbits.ODCG2=val; }
				#ifdef PORT_ANALOG_G2
				void analog(bool val) {ANSELGbits.ANSG2=val; }
				typedef constexpr_no<PORT_ANALOG_G2> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_G3
			struct pin3{
				bool port()const volatile {return PORTGbits.RG3; }
				#ifndef PORT_IN_G3
				void lat(bool val) {LATGbits.LATG3=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISGbits.TRISG3=val; }
				void opendrain(bool val) {ODCGbits.ODCG3=val; }
				#ifdef PORT_ANALOG_G3
				void analog(bool val) {ANSELGbits.ANSG3=val; }
				typedef constexpr_no<PORT_ANALOG_G3> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_G4
			struct pin4{
				bool port()const volatile {return PORTGbits.RG4; }
				#ifndef PORT_IN_G4
				void lat(bool val) {LATGbits.LATG4=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISGbits.TRISG4=val; }
				void opendrain(bool val) {ODCGbits.ODCG4=val; }
				#ifdef PORT_ANALOG_G4
				void analog(bool val) {ANSELGbits.ANSG4=val; }
				typedef constexpr_no<PORT_ANALOG_G4> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_G5
			struct pin5{
				bool port()const volatile {return PORTGbits.RG5; }
				#ifndef PORT_IN_G5
				void lat(bool val) {LATGbits.LATG5=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISGbits.TRISG5=val; }
				void opendrain(bool val) {ODCGbits.ODCG5=val; }
				#ifdef PORT_ANALOG_G5
				void analog(bool val) {ANSELGbits.ANSG5=val; }
				typedef constexpr_no<PORT_ANALOG_G5> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_G6
			struct pin6{
				bool port()const volatile {return PORTGbits.RG6; }
				#ifndef PORT_IN_G6
				void lat(bool val) {LATGbits.LATG6=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISGbits.TRISG6=val; }
				void opendrain(bool val) {ODCGbits.ODCG6=val; }
				#ifdef PORT_ANALOG_G6
				void analog(bool val) {ANSELGbits.ANSG6=val; }
				typedef constexpr_no<PORT_ANALOG_G6> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_G7
			struct pin7{
				bool port()const volatile {return PORTGbits.RG7; }
				#ifndef PORT_IN_G7
				void lat(bool val) {LATGbits.LATG7=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISGbits.TRISG7=val; }
				void opendrain(bool val) {ODCGbits.ODCG7=val; }
				#ifdef PORT_ANALOG_G7
				void analog(bool val) {ANSELGbits.ANSG7=val; }
				typedef constexpr_no<PORT_ANALOG_G7> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_G8
			struct pin8{
				bool port()const volatile {return PORTGbits.RG8; }
				#ifndef PORT_IN_G8
				void lat(bool val) {LATGbits.LATG8=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISGbits.TRISG8=val; }
				void opendrain(bool val) {ODCGbits.ODCG8=val; }
				#ifdef PORT_ANALOG_G8
				void analog(bool val) {ANSELGbits.ANSG8=val; }
				typedef constexpr_no<PORT_ANALOG_G8> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_G9
			struct pin9{
				bool port()const volatile {return PORTGbits.RG9; }
				#ifndef PORT_IN_G9
				void lat(bool val) {LATGbits.LATG9=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISGbits.TRISG9=val; }
				void opendrain(bool val) {ODCGbits.ODCG9=val; }
				#ifdef PORT_ANALOG_G9
				void analog(bool val) {ANSELGbits.ANSG9=val; }
				typedef constexpr_no<PORT_ANALOG_G9> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_G10
			struct pin10{
				bool port()const volatile {return PORTGbits.RG10; }
				#ifndef PORT_IN_G10
				void lat(bool val) {LATGbits.LATG10=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISGbits.TRISG10=val; }
				void opendrain(bool val) {ODCGbits.ODCG10=val; }
				#ifdef PORT_ANALOG_G10
				void analog(bool val) {ANSELGbits.ANSG10=val; }
				typedef constexpr_no<PORT_ANALOG_G10> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_G11
			struct pin11{
				bool port()const volatile {return PORTGbits.RG11; }
				#ifndef PORT_IN_G11
				void lat(bool val) {LATGbits.LATG11=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISGbits.TRISG11=val; }
				void opendrain(bool val) {ODCGbits.ODCG11=val; }
				#ifdef PORT_ANALOG_G11
				void analog(bool val) {ANSELGbits.ANSG11=val; }
				typedef constexpr_no<PORT_ANALOG_G11> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_G12
			struct pin12{
				bool port()const volatile {return PORTGbits.RG12; }
				#ifndef PORT_IN_G12
				void lat(bool val) {LATGbits.LATG12=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISGbits.TRISG12=val; }
				void opendrain(bool val) {ODCGbits.ODCG12=val; }
				#ifdef PORT_ANALOG_G12
				void analog(bool val) {ANSELGbits.ANSG12=val; }
				typedef constexpr_no<PORT_ANALOG_G12> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_G13
			struct pin13{
				bool port()const volatile {return PORTGbits.RG13; }
				#ifndef PORT_IN_G13
				void lat(bool val) {LATGbits.LATG13=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISGbits.TRISG13=val; }
				void opendrain(bool val) {ODCGbits.ODCG13=val; }
				#ifdef PORT_ANALOG_G13
				void analog(bool val) {ANSELGbits.ANSG13=val; }
				typedef constexpr_no<PORT_ANALOG_G13> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_G14
			struct pin14{
				bool port()const volatile {return PORTGbits.RG14; }
				#ifndef PORT_IN_G14
				void lat(bool val) {LATGbits.LATG14=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISGbits.TRISG14=val; }
				void opendrain(bool val) {ODCGbits.ODCG14=val; }
				#ifdef PORT_ANALOG_G14
				void analog(bool val) {ANSELGbits.ANSG14=val; }
				typedef constexpr_no<PORT_ANALOG_G14> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_G15
			struct pin15{
				bool port()const volatile {return PORTGbits.RG15; }
				#ifndef PORT_IN_G15
				void lat(bool val) {LATGbits.LATG15=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISGbits.TRISG15=val; }
				void opendrain(bool val) {ODCGbits.ODCG15=val; }
				#ifdef PORT_ANALOG_G15
				void analog(bool val) {ANSELGbits.ANSG15=val; }
				typedef constexpr_no<PORT_ANALOG_G15> analog_no;
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
