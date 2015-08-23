#ifndef XC32LIB_SFR_PORTF_INC
#define XC32LIB_SFR_PORTF_INC 100
#
#include"device_include.h"
#include<XCBase/constexpr_no.hpp>
namespace xc32 {
	namespace sfr{
		struct portF{
			#ifdef PORT_F0
			struct pin0{
				bool port()const volatile {return PORTFbits.RF0; }
				#ifndef PORT_IN_F0
				void lat(bool val) {LATFbits.LATF0=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISFbits.TRISF0=val; }
				void opendrain(bool val) {ODCFbits.ODCF0=val; }
				#ifdef PORT_ANALOG_F0
				void analog(bool val) {ANSELFbits.ANSF0=val; }
				typedef constexpr_no<PORT_ANALOG_F0> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_F1
			struct pin1{
				bool port()const volatile {return PORTFbits.RF1; }
				#ifndef PORT_IN_F1
				void lat(bool val) {LATFbits.LATF1=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISFbits.TRISF1=val; }
				void opendrain(bool val) {ODCFbits.ODCF1=val; }
				#ifdef PORT_ANALOG_F1
				void analog(bool val) {ANSELFbits.ANSF1=val; }
				typedef constexpr_no<PORT_ANALOG_F1> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_F2
			struct pin2{
				bool port()const volatile {return PORTFbits.RF2; }
				#ifndef PORT_IN_F2
				void lat(bool val) {LATFbits.LATF2=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISFbits.TRISF2=val; }
				void opendrain(bool val) {ODCFbits.ODCF2=val; }
				#ifdef PORT_ANALOG_F2
				void analog(bool val) {ANSELFbits.ANSF2=val; }
				typedef constexpr_no<PORT_ANALOG_F2> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_F3
			struct pin3{
				bool port()const volatile {return PORTFbits.RF3; }
				#ifndef PORT_IN_F3
				void lat(bool val) {LATFbits.LATF3=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISFbits.TRISF3=val; }
				void opendrain(bool val) {ODCFbits.ODCF3=val; }
				#ifdef PORT_ANALOG_F3
				void analog(bool val) {ANSELFbits.ANSF3=val; }
				typedef constexpr_no<PORT_ANALOG_F3> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_F4
			struct pin4{
				bool port()const volatile {return PORTFbits.RF4; }
				#ifndef PORT_IN_F4
				void lat(bool val) {LATFbits.LATF4=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISFbits.TRISF4=val; }
				void opendrain(bool val) {ODCFbits.ODCF4=val; }
				#ifdef PORT_ANALOG_F4
				void analog(bool val) {ANSELFbits.ANSF4=val; }
				typedef constexpr_no<PORT_ANALOG_F4> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_F5
			struct pin5{
				bool port()const volatile {return PORTFbits.RF5; }
				#ifndef PORT_IN_F5
				void lat(bool val) {LATFbits.LATF5=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISFbits.TRISF5=val; }
				void opendrain(bool val) {ODCFbits.ODCF5=val; }
				#ifdef PORT_ANALOG_F5
				void analog(bool val) {ANSELFbits.ANSF5=val; }
				typedef constexpr_no<PORT_ANALOG_F5> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_F6
			struct pin6{
				bool port()const volatile {return PORTFbits.RF6; }
				#ifndef PORT_IN_F6
				void lat(bool val) {LATFbits.LATF6=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISFbits.TRISF6=val; }
				void opendrain(bool val) {ODCFbits.ODCF6=val; }
				#ifdef PORT_ANALOG_F6
				void analog(bool val) {ANSELFbits.ANSF6=val; }
				typedef constexpr_no<PORT_ANALOG_F6> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_F7
			struct pin7{
				bool port()const volatile {return PORTFbits.RF7; }
				#ifndef PORT_IN_F7
				void lat(bool val) {LATFbits.LATF7=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISFbits.TRISF7=val; }
				void opendrain(bool val) {ODCFbits.ODCF7=val; }
				#ifdef PORT_ANALOG_F7
				void analog(bool val) {ANSELFbits.ANSF7=val; }
				typedef constexpr_no<PORT_ANALOG_F7> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_F8
			struct pin8{
				bool port()const volatile {return PORTFbits.RF8; }
				#ifndef PORT_IN_F8
				void lat(bool val) {LATFbits.LATF8=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISFbits.TRISF8=val; }
				void opendrain(bool val) {ODCFbits.ODCF8=val; }
				#ifdef PORT_ANALOG_F8
				void analog(bool val) {ANSELFbits.ANSF8=val; }
				typedef constexpr_no<PORT_ANALOG_F8> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_F9
			struct pin9{
				bool port()const volatile {return PORTFbits.RF9; }
				#ifndef PORT_IN_F9
				void lat(bool val) {LATFbits.LATF9=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISFbits.TRISF9=val; }
				void opendrain(bool val) {ODCFbits.ODCF9=val; }
				#ifdef PORT_ANALOG_F9
				void analog(bool val) {ANSELFbits.ANSF9=val; }
				typedef constexpr_no<PORT_ANALOG_F9> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_F10
			struct pin10{
				bool port()const volatile {return PORTFbits.RF10; }
				#ifndef PORT_IN_F10
				void lat(bool val) {LATFbits.LATF10=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISFbits.TRISF10=val; }
				void opendrain(bool val) {ODCFbits.ODCF10=val; }
				#ifdef PORT_ANALOG_F10
				void analog(bool val) {ANSELFbits.ANSF10=val; }
				typedef constexpr_no<PORT_ANALOG_F10> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_F11
			struct pin11{
				bool port()const volatile {return PORTFbits.RF11; }
				#ifndef PORT_IN_F11
				void lat(bool val) {LATFbits.LATF11=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISFbits.TRISF11=val; }
				void opendrain(bool val) {ODCFbits.ODCF11=val; }
				#ifdef PORT_ANALOG_F11
				void analog(bool val) {ANSELFbits.ANSF11=val; }
				typedef constexpr_no<PORT_ANALOG_F11> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_F12
			struct pin12{
				bool port()const volatile {return PORTFbits.RF12; }
				#ifndef PORT_IN_F12
				void lat(bool val) {LATFbits.LATF12=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISFbits.TRISF12=val; }
				void opendrain(bool val) {ODCFbits.ODCF12=val; }
				#ifdef PORT_ANALOG_F12
				void analog(bool val) {ANSELFbits.ANSF12=val; }
				typedef constexpr_no<PORT_ANALOG_F12> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_F13
			struct pin13{
				bool port()const volatile {return PORTFbits.RF13; }
				#ifndef PORT_IN_F13
				void lat(bool val) {LATFbits.LATF13=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISFbits.TRISF13=val; }
				void opendrain(bool val) {ODCFbits.ODCF13=val; }
				#ifdef PORT_ANALOG_F13
				void analog(bool val) {ANSELFbits.ANSF13=val; }
				typedef constexpr_no<PORT_ANALOG_F13> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_F14
			struct pin14{
				bool port()const volatile {return PORTFbits.RF14; }
				#ifndef PORT_IN_F14
				void lat(bool val) {LATFbits.LATF14=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISFbits.TRISF14=val; }
				void opendrain(bool val) {ODCFbits.ODCF14=val; }
				#ifdef PORT_ANALOG_F14
				void analog(bool val) {ANSELFbits.ANSF14=val; }
				typedef constexpr_no<PORT_ANALOG_F14> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_F15
			struct pin15{
				bool port()const volatile {return PORTFbits.RF15; }
				#ifndef PORT_IN_F15
				void lat(bool val) {LATFbits.LATF15=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISFbits.TRISF15=val; }
				void opendrain(bool val) {ODCFbits.ODCF15=val; }
				#ifdef PORT_ANALOG_F15
				void analog(bool val) {ANSELFbits.ANSF15=val; }
				typedef constexpr_no<PORT_ANALOG_F15> analog_no;
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
