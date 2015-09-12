#ifndef XC32_SFR_PORTA_INC
#define XC32_SFR_PORTA_INC 100
#
#include"device_include.h"
#include<XCBase/constexpr_no.hpp>
namespace xc32{
	using namespace xc;
	namespace sfr{
		struct portA{
			#ifdef PORT_A0
			struct pin0{
				bool port()const volatile {return PORTAbits.RA0; }
				#ifndef PORT_IN_A0
				void lat(bool val) {LATAbits.LATA0=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISAbits.TRISA0=val; }
				void opendrain(bool val) {ODCAbits.ODCA0=val; }
				#ifdef PORT_ANALOG_A0
				void analog(bool val) {ANSELAbits.ANSA0=val; }
				typedef constexpr_no<PORT_ANALOG_A0> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_A1
			struct pin1{
				bool port()const volatile {return PORTAbits.RA1; }
				#ifndef PORT_IN_A1
				void lat(bool val) {LATAbits.LATA1=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISAbits.TRISA1=val; }
				void opendrain(bool val) {ODCAbits.ODCA1=val; }
				#ifdef PORT_ANALOG_A1
				void analog(bool val) {ANSELAbits.ANSA1=val; }
				typedef constexpr_no<PORT_ANALOG_A1> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_A2
			struct pin2{
				bool port()const volatile {return PORTAbits.RA2; }
				#ifndef PORT_IN_A2
				void lat(bool val) {LATAbits.LATA2=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISAbits.TRISA2=val; }
				void opendrain(bool val) {ODCAbits.ODCA2=val; }
				#ifdef PORT_ANALOG_A2
				void analog(bool val) {ANSELAbits.ANSA2=val; }
				typedef constexpr_no<PORT_ANALOG_A2> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_A3
			struct pin3{
				bool port()const volatile {return PORTAbits.RA3; }
				#ifndef PORT_IN_A3
				void lat(bool val) {LATAbits.LATA3=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISAbits.TRISA3=val; }
				void opendrain(bool val) {ODCAbits.ODCA3=val; }
				#ifdef PORT_ANALOG_A3
				void analog(bool val) {ANSELAbits.ANSA3=val; }
				typedef constexpr_no<PORT_ANALOG_A3> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_A4
			struct pin4{
				bool port()const volatile {return PORTAbits.RA4; }
				#ifndef PORT_IN_A4
				void lat(bool val) {LATAbits.LATA4=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISAbits.TRISA4=val; }
				void opendrain(bool val) {ODCAbits.ODCA4=val; }
				#ifdef PORT_ANALOG_A4
				void analog(bool val) {ANSELAbits.ANSA4=val; }
				typedef constexpr_no<PORT_ANALOG_A4> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_A5
			struct pin5{
				bool port()const volatile {return PORTAbits.RA5; }
				#ifndef PORT_IN_A5
				void lat(bool val) {LATAbits.LATA5=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISAbits.TRISA5=val; }
				void opendrain(bool val) {ODCAbits.ODCA5=val; }
				#ifdef PORT_ANALOG_A5
				void analog(bool val) {ANSELAbits.ANSA5=val; }
				typedef constexpr_no<PORT_ANALOG_A5> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_A6
			struct pin6{
				bool port()const volatile {return PORTAbits.RA6; }
				#ifndef PORT_IN_A6
				void lat(bool val) {LATAbits.LATA6=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISAbits.TRISA6=val; }
				void opendrain(bool val) {ODCAbits.ODCA6=val; }
				#ifdef PORT_ANALOG_A6
				void analog(bool val) {ANSELAbits.ANSA6=val; }
				typedef constexpr_no<PORT_ANALOG_A6> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_A7
			struct pin7{
				bool port()const volatile {return PORTAbits.RA7; }
				#ifndef PORT_IN_A7
				void lat(bool val) {LATAbits.LATA7=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISAbits.TRISA7=val; }
				void opendrain(bool val) {ODCAbits.ODCA7=val; }
				#ifdef PORT_ANALOG_A7
				void analog(bool val) {ANSELAbits.ANSA7=val; }
				typedef constexpr_no<PORT_ANALOG_A7> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_A8
			struct pin8{
				bool port()const volatile {return PORTAbits.RA8; }
				#ifndef PORT_IN_A8
				void lat(bool val) {LATAbits.LATA8=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISAbits.TRISA8=val; }
				void opendrain(bool val) {ODCAbits.ODCA8=val; }
				#ifdef PORT_ANALOG_A8
				void analog(bool val) {ANSELAbits.ANSA8=val; }
				typedef constexpr_no<PORT_ANALOG_A8> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_A9
			struct pin9{
				bool port()const volatile {return PORTAbits.RA9; }
				#ifndef PORT_IN_A9
				void lat(bool val) {LATAbits.LATA9=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISAbits.TRISA9=val; }
				void opendrain(bool val) {ODCAbits.ODCA9=val; }
				#ifdef PORT_ANALOG_A9
				void analog(bool val) {ANSELAbits.ANSA9=val; }
				typedef constexpr_no<PORT_ANALOG_A9> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_A10
			struct pin10{
				bool port()const volatile {return PORTAbits.RA10; }
				#ifndef PORT_IN_A10
				void lat(bool val) {LATAbits.LATA10=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISAbits.TRISA10=val; }
				void opendrain(bool val) {ODCAbits.ODCA10=val; }
				#ifdef PORT_ANALOG_A10
				void analog(bool val) {ANSELAbits.ANSA10=val; }
				typedef constexpr_no<PORT_ANALOG_A10> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_A11
			struct pin11{
				bool port()const volatile {return PORTAbits.RA11; }
				#ifndef PORT_IN_A11
				void lat(bool val) {LATAbits.LATA11=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISAbits.TRISA11=val; }
				void opendrain(bool val) {ODCAbits.ODCA11=val; }
				#ifdef PORT_ANALOG_A11
				void analog(bool val) {ANSELAbits.ANSA11=val; }
				typedef constexpr_no<PORT_ANALOG_A11> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_A12
			struct pin12{
				bool port()const volatile {return PORTAbits.RA12; }
				#ifndef PORT_IN_A12
				void lat(bool val) {LATAbits.LATA12=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISAbits.TRISA12=val; }
				void opendrain(bool val) {ODCAbits.ODCA12=val; }
				#ifdef PORT_ANALOG_A12
				void analog(bool val) {ANSELAbits.ANSA12=val; }
				typedef constexpr_no<PORT_ANALOG_A12> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_A13
			struct pin13{
				bool port()const volatile {return PORTAbits.RA13; }
				#ifndef PORT_IN_A13
				void lat(bool val) {LATAbits.LATA13=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISAbits.TRISA13=val; }
				void opendrain(bool val) {ODCAbits.ODCA13=val; }
				#ifdef PORT_ANALOG_A13
				void analog(bool val) {ANSELAbits.ANSA13=val; }
				typedef constexpr_no<PORT_ANALOG_A13> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_A14
			struct pin14{
				bool port()const volatile {return PORTAbits.RA14; }
				#ifndef PORT_IN_A14
				void lat(bool val) {LATAbits.LATA14=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISAbits.TRISA14=val; }
				void opendrain(bool val) {ODCAbits.ODCA14=val; }
				#ifdef PORT_ANALOG_A14
				void analog(bool val) {ANSELAbits.ANSA14=val; }
				typedef constexpr_no<PORT_ANALOG_A14> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_A15
			struct pin15{
				bool port()const volatile {return PORTAbits.RA15; }
				#ifndef PORT_IN_A15
				void lat(bool val) {LATAbits.LATA15=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISAbits.TRISA15=val; }
				void opendrain(bool val) {ODCAbits.ODCA15=val; }
				#ifdef PORT_ANALOG_A15
				void analog(bool val) {ANSELAbits.ANSA15=val; }
				typedef constexpr_no<PORT_ANALOG_A15> analog_no;
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
