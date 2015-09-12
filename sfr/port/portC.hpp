#ifndef XC32_SFR_PORTC_INC
#define XC32_SFR_PORTC_INC 100
#
#include"device_include.h"
#include<XCBase/constexpr_no.hpp>
namespace xc32 {
	namespace sfr{
		struct portC{
			#ifdef PORT_C0
			struct pin0{
				bool port()const volatile {return PORTCbits.RC0; }
				#ifndef PORT_IN_C0
				void lat(bool val) {LATCbits.LATC0=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISCbits.TRISC0=val; }
				void opendrain(bool val) {ODCCbits.ODCC0=val; }
				#ifdef PORT_ANALOG_C0
				void analog(bool val) {ANSELCbits.ANSC0=val; }
				typedef constexpr_no<PORT_ANALOG_C0> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_C1
			struct pin1{
				bool port()const volatile {return PORTCbits.RC1; }
				#ifndef PORT_IN_C1
				void lat(bool val) {LATCbits.LATC1=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISCbits.TRISC1=val; }
				void opendrain(bool val) {ODCCbits.ODCC1=val; }
				#ifdef PORT_ANALOG_C1
				void analog(bool val) {ANSELCbits.ANSC1=val; }
				typedef constexpr_no<PORT_ANALOG_C1> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_C2
			struct pin2{
				bool port()const volatile {return PORTCbits.RC2; }
				#ifndef PORT_IN_C2
				void lat(bool val) {LATCbits.LATC2=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISCbits.TRISC2=val; }
				void opendrain(bool val) {ODCCbits.ODCC2=val; }
				#ifdef PORT_ANALOG_C2
				void analog(bool val) {ANSELCbits.ANSC2=val; }
				typedef constexpr_no<PORT_ANALOG_C2> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_C3
			struct pin3{
				bool port()const volatile {return PORTCbits.RC3; }
				#ifndef PORT_IN_C3
				void lat(bool val) {LATCbits.LATC3=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISCbits.TRISC3=val; }
				void opendrain(bool val) {ODCCbits.ODCC3=val; }
				#ifdef PORT_ANALOG_C3
				void analog(bool val) {ANSELCbits.ANSC3=val; }
				typedef constexpr_no<PORT_ANALOG_C3> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_C4
			struct pin4{
				bool port()const volatile {return PORTCbits.RC4; }
				#ifndef PORT_IN_C4
				void lat(bool val) {LATCbits.LATC4=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISCbits.TRISC4=val; }
				void opendrain(bool val) {ODCCbits.ODCC4=val; }
				#ifdef PORT_ANALOG_C4
				void analog(bool val) {ANSELCbits.ANSC4=val; }
				typedef constexpr_no<PORT_ANALOG_C4> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_C5
			struct pin5{
				bool port()const volatile {return PORTCbits.RC5; }
				#ifndef PORT_IN_C5
				void lat(bool val) {LATCbits.LATC5=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISCbits.TRISC5=val; }
				void opendrain(bool val) {ODCCbits.ODCC5=val; }
				#ifdef PORT_ANALOG_C5
				void analog(bool val) {ANSELCbits.ANSC5=val; }
				typedef constexpr_no<PORT_ANALOG_C5> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_C6
			struct pin6{
				bool port()const volatile {return PORTCbits.RC6; }
				#ifndef PORT_IN_C6
				void lat(bool val) {LATCbits.LATC6=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISCbits.TRISC6=val; }
				void opendrain(bool val) {ODCCbits.ODCC6=val; }
				#ifdef PORT_ANALOG_C6
				void analog(bool val) {ANSELCbits.ANSC6=val; }
				typedef constexpr_no<PORT_ANALOG_C6> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_C7
			struct pin7{
				bool port()const volatile {return PORTCbits.RC7; }
				#ifndef PORT_IN_C7
				void lat(bool val) {LATCbits.LATC7=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISCbits.TRISC7=val; }
				void opendrain(bool val) {ODCCbits.ODCC7=val; }
				#ifdef PORT_ANALOG_C7
				void analog(bool val) {ANSELCbits.ANSC7=val; }
				typedef constexpr_no<PORT_ANALOG_C7> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_C8
			struct pin8{
				bool port()const volatile {return PORTCbits.RC8; }
				#ifndef PORT_IN_C8
				void lat(bool val) {LATCbits.LATC8=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISCbits.TRISC8=val; }
				void opendrain(bool val) {ODCCbits.ODCC8=val; }
				#ifdef PORT_ANALOG_C8
				void analog(bool val) {ANSELCbits.ANSC8=val; }
				typedef constexpr_no<PORT_ANALOG_C8> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_C9
			struct pin9{
				bool port()const volatile {return PORTCbits.RC9; }
				#ifndef PORT_IN_C9
				void lat(bool val) {LATCbits.LATC9=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISCbits.TRISC9=val; }
				void opendrain(bool val) {ODCCbits.ODCC9=val; }
				#ifdef PORT_ANALOG_C9
				void analog(bool val) {ANSELCbits.ANSC9=val; }
				typedef constexpr_no<PORT_ANALOG_C9> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_C10
			struct pin10{
				bool port()const volatile {return PORTCbits.RC10; }
				#ifndef PORT_IN_C10
				void lat(bool val) {LATCbits.LATC10=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISCbits.TRISC10=val; }
				void opendrain(bool val) {ODCCbits.ODCC10=val; }
				#ifdef PORT_ANALOG_C10
				void analog(bool val) {ANSELCbits.ANSC10=val; }
				typedef constexpr_no<PORT_ANALOG_C10> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_C11
			struct pin11{
				bool port()const volatile {return PORTCbits.RC11; }
				#ifndef PORT_IN_C11
				void lat(bool val) {LATCbits.LATC11=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISCbits.TRISC11=val; }
				void opendrain(bool val) {ODCCbits.ODCC11=val; }
				#ifdef PORT_ANALOG_C11
				void analog(bool val) {ANSELCbits.ANSC11=val; }
				typedef constexpr_no<PORT_ANALOG_C11> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_C12
			struct pin12{
				bool port()const volatile {return PORTCbits.RC12; }
				#ifndef PORT_IN_C12
				void lat(bool val) {LATCbits.LATC12=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISCbits.TRISC12=val; }
				void opendrain(bool val) {ODCCbits.ODCC12=val; }
				#ifdef PORT_ANALOG_C12
				void analog(bool val) {ANSELCbits.ANSC12=val; }
				typedef constexpr_no<PORT_ANALOG_C12> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_C13
			struct pin13{
				bool port()const volatile {return PORTCbits.RC13; }
				#ifndef PORT_IN_C13
				void lat(bool val) {LATCbits.LATC13=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISCbits.TRISC13=val; }
				void opendrain(bool val) {ODCCbits.ODCC13=val; }
				#ifdef PORT_ANALOG_C13
				void analog(bool val) {ANSELCbits.ANSC13=val; }
				typedef constexpr_no<PORT_ANALOG_C13> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_C14
			struct pin14{
				bool port()const volatile {return PORTCbits.RC14; }
				#ifndef PORT_IN_C14
				void lat(bool val) {LATCbits.LATC14=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISCbits.TRISC14=val; }
				void opendrain(bool val) {ODCCbits.ODCC14=val; }
				#ifdef PORT_ANALOG_C14
				void analog(bool val) {ANSELCbits.ANSC14=val; }
				typedef constexpr_no<PORT_ANALOG_C14> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_C15
			struct pin15{
				bool port()const volatile {return PORTCbits.RC15; }
				#ifndef PORT_IN_C15
				void lat(bool val) {LATCbits.LATC15=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISCbits.TRISC15=val; }
				void opendrain(bool val) {ODCCbits.ODCC15=val; }
				#ifdef PORT_ANALOG_C15
				void analog(bool val) {ANSELCbits.ANSC15=val; }
				typedef constexpr_no<PORT_ANALOG_C15> analog_no;
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
