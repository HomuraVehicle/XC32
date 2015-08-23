#ifndef XC32LIB_SFR_PORTB_INC
#define XC32LIB_SFR_PORTB_INC 100
#
#include"device_include.h"
#include<XCBase/constexpr_no.hpp>
namespace xc32 {
	namespace sfr{
		struct portB{
			#ifdef PORT_B0
			struct pin0{
				bool port()const volatile {return PORTBbits.RB0; }
				#ifndef PORT_IN_B0
				void lat(bool val) {LATBbits.LATB0=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISBbits.TRISB0=val; }
				void opendrain(bool val) {ODCBbits.ODCB0=val; }
				#ifdef PORT_ANALOG_B0
				void analog(bool val) {ANSELBbits.ANSB0=val; }
				typedef constexpr_no<PORT_ANALOG_B0> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_B1
			struct pin1{
				bool port()const volatile {return PORTBbits.RB1; }
				#ifndef PORT_IN_B1
				void lat(bool val) {LATBbits.LATB1=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISBbits.TRISB1=val; }
				void opendrain(bool val) {ODCBbits.ODCB1=val; }
				#ifdef PORT_ANALOG_B1
				void analog(bool val) {ANSELBbits.ANSB1=val; }
				typedef constexpr_no<PORT_ANALOG_B1> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_B2
			struct pin2{
				bool port()const volatile {return PORTBbits.RB2; }
				#ifndef PORT_IN_B2
				void lat(bool val) {LATBbits.LATB2=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISBbits.TRISB2=val; }
				void opendrain(bool val) {ODCBbits.ODCB2=val; }
				#ifdef PORT_ANALOG_B2
				void analog(bool val) {ANSELBbits.ANSB2=val; }
				typedef constexpr_no<PORT_ANALOG_B2> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_B3
			struct pin3{
				bool port()const volatile {return PORTBbits.RB3; }
				#ifndef PORT_IN_B3
				void lat(bool val) {LATBbits.LATB3=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISBbits.TRISB3=val; }
				void opendrain(bool val) {ODCBbits.ODCB3=val; }
				#ifdef PORT_ANALOG_B3
				void analog(bool val) {ANSELBbits.ANSB3=val; }
				typedef constexpr_no<PORT_ANALOG_B3> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_B4
			struct pin4{
				bool port()const volatile {return PORTBbits.RB4; }
				#ifndef PORT_IN_B4
				void lat(bool val) {LATBbits.LATB4=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISBbits.TRISB4=val; }
				void opendrain(bool val) {ODCBbits.ODCB4=val; }
				#ifdef PORT_ANALOG_B4
				void analog(bool val) {ANSELBbits.ANSB4=val; }
				typedef constexpr_no<PORT_ANALOG_B4> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_B5
			struct pin5{
				bool port()const volatile {return PORTBbits.RB5; }
				#ifndef PORT_IN_B5
				void lat(bool val) {LATBbits.LATB5=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISBbits.TRISB5=val; }
				void opendrain(bool val) {ODCBbits.ODCB5=val; }
				#ifdef PORT_ANALOG_B5
				void analog(bool val) {ANSELBbits.ANSB5=val; }
				typedef constexpr_no<PORT_ANALOG_B5> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_B6
			struct pin6{
				bool port()const volatile {return PORTBbits.RB6; }
				#ifndef PORT_IN_B6
				void lat(bool val) {LATBbits.LATB6=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISBbits.TRISB6=val; }
				void opendrain(bool val) {ODCBbits.ODCB6=val; }
				#ifdef PORT_ANALOG_B6
				void analog(bool val) {ANSELBbits.ANSB6=val; }
				typedef constexpr_no<PORT_ANALOG_B6> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_B7
			struct pin7{
				bool port()const volatile {return PORTBbits.RB7; }
				#ifndef PORT_IN_B7
				void lat(bool val) {LATBbits.LATB7=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISBbits.TRISB7=val; }
				void opendrain(bool val) {ODCBbits.ODCB7=val; }
				#ifdef PORT_ANALOG_B7
				void analog(bool val) {ANSELBbits.ANSB7=val; }
				typedef constexpr_no<PORT_ANALOG_B7> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_B8
			struct pin8{
				bool port()const volatile {return PORTBbits.RB8; }
				#ifndef PORT_IN_B8
				void lat(bool val) {LATBbits.LATB8=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISBbits.TRISB8=val; }
				void opendrain(bool val) {ODCBbits.ODCB8=val; }
				#ifdef PORT_ANALOG_B8
				void analog(bool val) {ANSELBbits.ANSB8=val; }
				typedef constexpr_no<PORT_ANALOG_B8> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_B9
			struct pin9{
				bool port()const volatile {return PORTBbits.RB9; }
				#ifndef PORT_IN_B9
				void lat(bool val) {LATBbits.LATB9=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISBbits.TRISB9=val; }
				void opendrain(bool val) {ODCBbits.ODCB9=val; }
				#ifdef PORT_ANALOG_B9
				void analog(bool val) {ANSELBbits.ANSB9=val; }
				typedef constexpr_no<PORT_ANALOG_B9> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_B10
			struct pin10{
				bool port()const volatile {return PORTBbits.RB10; }
				#ifndef PORT_IN_B10
				void lat(bool val) {LATBbits.LATB10=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISBbits.TRISB10=val; }
				void opendrain(bool val) {ODCBbits.ODCB10=val; }
				#ifdef PORT_ANALOG_B10
				void analog(bool val) {ANSELBbits.ANSB10=val; }
				typedef constexpr_no<PORT_ANALOG_B10> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_B11
			struct pin11{
				bool port()const volatile {return PORTBbits.RB11; }
				#ifndef PORT_IN_B11
				void lat(bool val) {LATBbits.LATB11=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISBbits.TRISB11=val; }
				void opendrain(bool val) {ODCBbits.ODCB11=val; }
				#ifdef PORT_ANALOG_B11
				void analog(bool val) {ANSELBbits.ANSB11=val; }
				typedef constexpr_no<PORT_ANALOG_B11> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_B12
			struct pin12{
				bool port()const volatile {return PORTBbits.RB12; }
				#ifndef PORT_IN_B12
				void lat(bool val) {LATBbits.LATB12=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISBbits.TRISB12=val; }
				void opendrain(bool val) {ODCBbits.ODCB12=val; }
				#ifdef PORT_ANALOG_B12
				void analog(bool val) {ANSELBbits.ANSB12=val; }
				typedef constexpr_no<PORT_ANALOG_B12> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_B13
			struct pin13{
				bool port()const volatile {return PORTBbits.RB13; }
				#ifndef PORT_IN_B13
				void lat(bool val) {LATBbits.LATB13=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISBbits.TRISB13=val; }
				void opendrain(bool val) {ODCBbits.ODCB13=val; }
				#ifdef PORT_ANALOG_B13
				void analog(bool val) {ANSELBbits.ANSB13=val; }
				typedef constexpr_no<PORT_ANALOG_B13> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_B14
			struct pin14{
				bool port()const volatile {return PORTBbits.RB14; }
				#ifndef PORT_IN_B14
				void lat(bool val) {LATBbits.LATB14=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISBbits.TRISB14=val; }
				void opendrain(bool val) {ODCBbits.ODCB14=val; }
				#ifdef PORT_ANALOG_B14
				void analog(bool val) {ANSELBbits.ANSB14=val; }
				typedef constexpr_no<PORT_ANALOG_B14> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_B15
			struct pin15{
				bool port()const volatile {return PORTBbits.RB15; }
				#ifndef PORT_IN_B15
				void lat(bool val) {LATBbits.LATB15=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISBbits.TRISB15=val; }
				void opendrain(bool val) {ODCBbits.ODCB15=val; }
				#ifdef PORT_ANALOG_B15
				void analog(bool val) {ANSELBbits.ANSB15=val; }
				typedef constexpr_no<PORT_ANALOG_B15> analog_no;
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
