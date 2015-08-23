#ifndef XC32LIB_SFR_PORTH_INC
#define XC32LIB_SFR_PORTH_INC 100
#
#include"device_include.h"
#include<XCBase/constexpr_no.hpp>
namespace xc32 {
	namespace sfr{
		struct portH{
			#ifdef PORT_H0
			struct pin0{
				bool port()const volatile {return PORTHbits.RH0; }
				#ifndef PORT_IN_H0
				void lat(bool val) {LATHbits.LATH0=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISHbits.TRISH0=val; }
				void opendrain(bool val) {ODCHbits.ODCH0=val; }
				#ifdef PORT_ANALOG_H0
				void analog(bool val) {ANSELHbits.ANSH0=val; }
				typedef constexpr_no<PORT_ANALOG_H0> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_H1
			struct pin1{
				bool port()const volatile {return PORTHbits.RH1; }
				#ifndef PORT_IN_H1
				void lat(bool val) {LATHbits.LATH1=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISHbits.TRISH1=val; }
				void opendrain(bool val) {ODCHbits.ODCH1=val; }
				#ifdef PORT_ANALOG_H1
				void analog(bool val) {ANSELHbits.ANSH1=val; }
				typedef constexpr_no<PORT_ANALOG_H1> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_H2
			struct pin2{
				bool port()const volatile {return PORTHbits.RH2; }
				#ifndef PORT_IN_H2
				void lat(bool val) {LATHbits.LATH2=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISHbits.TRISH2=val; }
				void opendrain(bool val) {ODCHbits.ODCH2=val; }
				#ifdef PORT_ANALOG_H2
				void analog(bool val) {ANSELHbits.ANSH2=val; }
				typedef constexpr_no<PORT_ANALOG_H2> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_H3
			struct pin3{
				bool port()const volatile {return PORTHbits.RH3; }
				#ifndef PORT_IN_H3
				void lat(bool val) {LATHbits.LATH3=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISHbits.TRISH3=val; }
				void opendrain(bool val) {ODCHbits.ODCH3=val; }
				#ifdef PORT_ANALOG_H3
				void analog(bool val) {ANSELHbits.ANSH3=val; }
				typedef constexpr_no<PORT_ANALOG_H3> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_H4
			struct pin4{
				bool port()const volatile {return PORTHbits.RH4; }
				#ifndef PORT_IN_H4
				void lat(bool val) {LATHbits.LATH4=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISHbits.TRISH4=val; }
				void opendrain(bool val) {ODCHbits.ODCH4=val; }
				#ifdef PORT_ANALOG_H4
				void analog(bool val) {ANSELHbits.ANSH4=val; }
				typedef constexpr_no<PORT_ANALOG_H4> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_H5
			struct pin5{
				bool port()const volatile {return PORTHbits.RH5; }
				#ifndef PORT_IN_H5
				void lat(bool val) {LATHbits.LATH5=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISHbits.TRISH5=val; }
				void opendrain(bool val) {ODCHbits.ODCH5=val; }
				#ifdef PORT_ANALOG_H5
				void analog(bool val) {ANSELHbits.ANSH5=val; }
				typedef constexpr_no<PORT_ANALOG_H5> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_H6
			struct pin6{
				bool port()const volatile {return PORTHbits.RH6; }
				#ifndef PORT_IN_H6
				void lat(bool val) {LATHbits.LATH6=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISHbits.TRISH6=val; }
				void opendrain(bool val) {ODCHbits.ODCH6=val; }
				#ifdef PORT_ANALOG_H6
				void analog(bool val) {ANSELHbits.ANSH6=val; }
				typedef constexpr_no<PORT_ANALOG_H6> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_H7
			struct pin7{
				bool port()const volatile {return PORTHbits.RH7; }
				#ifndef PORT_IN_H7
				void lat(bool val) {LATHbits.LATH7=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISHbits.TRISH7=val; }
				void opendrain(bool val) {ODCHbits.ODCH7=val; }
				#ifdef PORT_ANALOG_H7
				void analog(bool val) {ANSELHbits.ANSH7=val; }
				typedef constexpr_no<PORT_ANALOG_H7> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_H8
			struct pin8{
				bool port()const volatile {return PORTHbits.RH8; }
				#ifndef PORT_IN_H8
				void lat(bool val) {LATHbits.LATH8=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISHbits.TRISH8=val; }
				void opendrain(bool val) {ODCHbits.ODCH8=val; }
				#ifdef PORT_ANALOG_H8
				void analog(bool val) {ANSELHbits.ANSH8=val; }
				typedef constexpr_no<PORT_ANALOG_H8> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_H9
			struct pin9{
				bool port()const volatile {return PORTHbits.RH9; }
				#ifndef PORT_IN_H9
				void lat(bool val) {LATHbits.LATH9=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISHbits.TRISH9=val; }
				void opendrain(bool val) {ODCHbits.ODCH9=val; }
				#ifdef PORT_ANALOG_H9
				void analog(bool val) {ANSELHbits.ANSH9=val; }
				typedef constexpr_no<PORT_ANALOG_H9> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_H10
			struct pin10{
				bool port()const volatile {return PORTHbits.RH10; }
				#ifndef PORT_IN_H10
				void lat(bool val) {LATHbits.LATH10=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISHbits.TRISH10=val; }
				void opendrain(bool val) {ODCHbits.ODCH10=val; }
				#ifdef PORT_ANALOG_H10
				void analog(bool val) {ANSELHbits.ANSH10=val; }
				typedef constexpr_no<PORT_ANALOG_H10> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_H11
			struct pin11{
				bool port()const volatile {return PORTHbits.RH11; }
				#ifndef PORT_IN_H11
				void lat(bool val) {LATHbits.LATH11=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISHbits.TRISH11=val; }
				void opendrain(bool val) {ODCHbits.ODCH11=val; }
				#ifdef PORT_ANALOG_H11
				void analog(bool val) {ANSELHbits.ANSH11=val; }
				typedef constexpr_no<PORT_ANALOG_H11> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_H12
			struct pin12{
				bool port()const volatile {return PORTHbits.RH12; }
				#ifndef PORT_IN_H12
				void lat(bool val) {LATHbits.LATH12=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISHbits.TRISH12=val; }
				void opendrain(bool val) {ODCHbits.ODCH12=val; }
				#ifdef PORT_ANALOG_H12
				void analog(bool val) {ANSELHbits.ANSH12=val; }
				typedef constexpr_no<PORT_ANALOG_H12> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_H13
			struct pin13{
				bool port()const volatile {return PORTHbits.RH13; }
				#ifndef PORT_IN_H13
				void lat(bool val) {LATHbits.LATH13=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISHbits.TRISH13=val; }
				void opendrain(bool val) {ODCHbits.ODCH13=val; }
				#ifdef PORT_ANALOG_H13
				void analog(bool val) {ANSELHbits.ANSH13=val; }
				typedef constexpr_no<PORT_ANALOG_H13> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_H14
			struct pin14{
				bool port()const volatile {return PORTHbits.RH14; }
				#ifndef PORT_IN_H14
				void lat(bool val) {LATHbits.LATH14=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISHbits.TRISH14=val; }
				void opendrain(bool val) {ODCHbits.ODCH14=val; }
				#ifdef PORT_ANALOG_H14
				void analog(bool val) {ANSELHbits.ANSH14=val; }
				typedef constexpr_no<PORT_ANALOG_H14> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_H15
			struct pin15{
				bool port()const volatile {return PORTHbits.RH15; }
				#ifndef PORT_IN_H15
				void lat(bool val) {LATHbits.LATH15=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISHbits.TRISH15=val; }
				void opendrain(bool val) {ODCHbits.ODCH15=val; }
				#ifdef PORT_ANALOG_H15
				void analog(bool val) {ANSELHbits.ANSH15=val; }
				typedef constexpr_no<PORT_ANALOG_H15> analog_no;
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
