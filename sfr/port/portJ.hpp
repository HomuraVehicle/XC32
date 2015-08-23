#ifndef XC32LIB_SFR_PORTJ_INC
#define XC32LIB_SFR_PORTJ_INC 100
#
#include"device_include.h"
#include<XCBase/constexpr_no.hpp>
namespace xc32 {
	namespace sfr{
		struct portJ{
			#ifdef PORT_J0
			struct pin0{
				bool port()const volatile {return PORTJbits.RJ0; }
				#ifndef PORT_IN_J0
				void lat(bool val) {LATJbits.LATJ0=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISJbits.TRISJ0=val; }
				void opendrain(bool val) {ODCJbits.ODCJ0=val; }
				#ifdef PORT_ANALOG_J0
				void analog(bool val) {ANSELJbits.ANSJ0=val; }
				typedef constexpr_no<PORT_ANALOG_J0> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_J1
			struct pin1{
				bool port()const volatile {return PORTJbits.RJ1; }
				#ifndef PORT_IN_J1
				void lat(bool val) {LATJbits.LATJ1=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISJbits.TRISJ1=val; }
				void opendrain(bool val) {ODCJbits.ODCJ1=val; }
				#ifdef PORT_ANALOG_J1
				void analog(bool val) {ANSELJbits.ANSJ1=val; }
				typedef constexpr_no<PORT_ANALOG_J1> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_J2
			struct pin2{
				bool port()const volatile {return PORTJbits.RJ2; }
				#ifndef PORT_IN_J2
				void lat(bool val) {LATJbits.LATJ2=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISJbits.TRISJ2=val; }
				void opendrain(bool val) {ODCJbits.ODCJ2=val; }
				#ifdef PORT_ANALOG_J2
				void analog(bool val) {ANSELJbits.ANSJ2=val; }
				typedef constexpr_no<PORT_ANALOG_J2> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_J3
			struct pin3{
				bool port()const volatile {return PORTJbits.RJ3; }
				#ifndef PORT_IN_J3
				void lat(bool val) {LATJbits.LATJ3=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISJbits.TRISJ3=val; }
				void opendrain(bool val) {ODCJbits.ODCJ3=val; }
				#ifdef PORT_ANALOG_J3
				void analog(bool val) {ANSELJbits.ANSJ3=val; }
				typedef constexpr_no<PORT_ANALOG_J3> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_J4
			struct pin4{
				bool port()const volatile {return PORTJbits.RJ4; }
				#ifndef PORT_IN_J4
				void lat(bool val) {LATJbits.LATJ4=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISJbits.TRISJ4=val; }
				void opendrain(bool val) {ODCJbits.ODCJ4=val; }
				#ifdef PORT_ANALOG_J4
				void analog(bool val) {ANSELJbits.ANSJ4=val; }
				typedef constexpr_no<PORT_ANALOG_J4> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_J5
			struct pin5{
				bool port()const volatile {return PORTJbits.RJ5; }
				#ifndef PORT_IN_J5
				void lat(bool val) {LATJbits.LATJ5=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISJbits.TRISJ5=val; }
				void opendrain(bool val) {ODCJbits.ODCJ5=val; }
				#ifdef PORT_ANALOG_J5
				void analog(bool val) {ANSELJbits.ANSJ5=val; }
				typedef constexpr_no<PORT_ANALOG_J5> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_J6
			struct pin6{
				bool port()const volatile {return PORTJbits.RJ6; }
				#ifndef PORT_IN_J6
				void lat(bool val) {LATJbits.LATJ6=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISJbits.TRISJ6=val; }
				void opendrain(bool val) {ODCJbits.ODCJ6=val; }
				#ifdef PORT_ANALOG_J6
				void analog(bool val) {ANSELJbits.ANSJ6=val; }
				typedef constexpr_no<PORT_ANALOG_J6> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_J7
			struct pin7{
				bool port()const volatile {return PORTJbits.RJ7; }
				#ifndef PORT_IN_J7
				void lat(bool val) {LATJbits.LATJ7=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISJbits.TRISJ7=val; }
				void opendrain(bool val) {ODCJbits.ODCJ7=val; }
				#ifdef PORT_ANALOG_J7
				void analog(bool val) {ANSELJbits.ANSJ7=val; }
				typedef constexpr_no<PORT_ANALOG_J7> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_J8
			struct pin8{
				bool port()const volatile {return PORTJbits.RJ8; }
				#ifndef PORT_IN_J8
				void lat(bool val) {LATJbits.LATJ8=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISJbits.TRISJ8=val; }
				void opendrain(bool val) {ODCJbits.ODCJ8=val; }
				#ifdef PORT_ANALOG_J8
				void analog(bool val) {ANSELJbits.ANSJ8=val; }
				typedef constexpr_no<PORT_ANALOG_J8> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_J9
			struct pin9{
				bool port()const volatile {return PORTJbits.RJ9; }
				#ifndef PORT_IN_J9
				void lat(bool val) {LATJbits.LATJ9=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISJbits.TRISJ9=val; }
				void opendrain(bool val) {ODCJbits.ODCJ9=val; }
				#ifdef PORT_ANALOG_J9
				void analog(bool val) {ANSELJbits.ANSJ9=val; }
				typedef constexpr_no<PORT_ANALOG_J9> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_J10
			struct pin10{
				bool port()const volatile {return PORTJbits.RJ10; }
				#ifndef PORT_IN_J10
				void lat(bool val) {LATJbits.LATJ10=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISJbits.TRISJ10=val; }
				void opendrain(bool val) {ODCJbits.ODCJ10=val; }
				#ifdef PORT_ANALOG_J10
				void analog(bool val) {ANSELJbits.ANSJ10=val; }
				typedef constexpr_no<PORT_ANALOG_J10> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_J11
			struct pin11{
				bool port()const volatile {return PORTJbits.RJ11; }
				#ifndef PORT_IN_J11
				void lat(bool val) {LATJbits.LATJ11=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISJbits.TRISJ11=val; }
				void opendrain(bool val) {ODCJbits.ODCJ11=val; }
				#ifdef PORT_ANALOG_J11
				void analog(bool val) {ANSELJbits.ANSJ11=val; }
				typedef constexpr_no<PORT_ANALOG_J11> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_J12
			struct pin12{
				bool port()const volatile {return PORTJbits.RJ12; }
				#ifndef PORT_IN_J12
				void lat(bool val) {LATJbits.LATJ12=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISJbits.TRISJ12=val; }
				void opendrain(bool val) {ODCJbits.ODCJ12=val; }
				#ifdef PORT_ANALOG_J12
				void analog(bool val) {ANSELJbits.ANSJ12=val; }
				typedef constexpr_no<PORT_ANALOG_J12> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_J13
			struct pin13{
				bool port()const volatile {return PORTJbits.RJ13; }
				#ifndef PORT_IN_J13
				void lat(bool val) {LATJbits.LATJ13=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISJbits.TRISJ13=val; }
				void opendrain(bool val) {ODCJbits.ODCJ13=val; }
				#ifdef PORT_ANALOG_J13
				void analog(bool val) {ANSELJbits.ANSJ13=val; }
				typedef constexpr_no<PORT_ANALOG_J13> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_J14
			struct pin14{
				bool port()const volatile {return PORTJbits.RJ14; }
				#ifndef PORT_IN_J14
				void lat(bool val) {LATJbits.LATJ14=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISJbits.TRISJ14=val; }
				void opendrain(bool val) {ODCJbits.ODCJ14=val; }
				#ifdef PORT_ANALOG_J14
				void analog(bool val) {ANSELJbits.ANSJ14=val; }
				typedef constexpr_no<PORT_ANALOG_J14> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_J15
			struct pin15{
				bool port()const volatile {return PORTJbits.RJ15; }
				#ifndef PORT_IN_J15
				void lat(bool val) {LATJbits.LATJ15=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISJbits.TRISJ15=val; }
				void opendrain(bool val) {ODCJbits.ODCJ15=val; }
				#ifdef PORT_ANALOG_J15
				void analog(bool val) {ANSELJbits.ANSJ15=val; }
				typedef constexpr_no<PORT_ANALOG_J15> analog_no;
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
