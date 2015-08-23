#ifndef XC32LIB_SFR_PORTI_INC
#define XC32LIB_SFR_PORTI_INC 100
#
#include"device_include.h"
#include<XCBase/constexpr_no.hpp>
namespace xc32 {
	namespace sfr{
		struct portI{
			#ifdef PORT_I0
			struct pin0{
				bool port()const volatile {return PORTIbits.RI0; }
				#ifndef PORT_IN_I0
				void lat(bool val) {LATIbits.LATI0=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISIbits.TRISI0=val; }
				void opendrain(bool val) {ODCIbits.ODCI0=val; }
				#ifdef PORT_ANALOG_I0
				void analog(bool val) {ANSELIbits.ANSI0=val; }
				typedef constexpr_no<PORT_ANALOG_I0> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_I1
			struct pin1{
				bool port()const volatile {return PORTIbits.RI1; }
				#ifndef PORT_IN_I1
				void lat(bool val) {LATIbits.LATI1=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISIbits.TRISI1=val; }
				void opendrain(bool val) {ODCIbits.ODCI1=val; }
				#ifdef PORT_ANALOG_I1
				void analog(bool val) {ANSELIbits.ANSI1=val; }
				typedef constexpr_no<PORT_ANALOG_I1> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_I2
			struct pin2{
				bool port()const volatile {return PORTIbits.RI2; }
				#ifndef PORT_IN_I2
				void lat(bool val) {LATIbits.LATI2=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISIbits.TRISI2=val; }
				void opendrain(bool val) {ODCIbits.ODCI2=val; }
				#ifdef PORT_ANALOG_I2
				void analog(bool val) {ANSELIbits.ANSI2=val; }
				typedef constexpr_no<PORT_ANALOG_I2> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_I3
			struct pin3{
				bool port()const volatile {return PORTIbits.RI3; }
				#ifndef PORT_IN_I3
				void lat(bool val) {LATIbits.LATI3=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISIbits.TRISI3=val; }
				void opendrain(bool val) {ODCIbits.ODCI3=val; }
				#ifdef PORT_ANALOG_I3
				void analog(bool val) {ANSELIbits.ANSI3=val; }
				typedef constexpr_no<PORT_ANALOG_I3> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_I4
			struct pin4{
				bool port()const volatile {return PORTIbits.RI4; }
				#ifndef PORT_IN_I4
				void lat(bool val) {LATIbits.LATI4=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISIbits.TRISI4=val; }
				void opendrain(bool val) {ODCIbits.ODCI4=val; }
				#ifdef PORT_ANALOG_I4
				void analog(bool val) {ANSELIbits.ANSI4=val; }
				typedef constexpr_no<PORT_ANALOG_I4> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_I5
			struct pin5{
				bool port()const volatile {return PORTIbits.RI5; }
				#ifndef PORT_IN_I5
				void lat(bool val) {LATIbits.LATI5=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISIbits.TRISI5=val; }
				void opendrain(bool val) {ODCIbits.ODCI5=val; }
				#ifdef PORT_ANALOG_I5
				void analog(bool val) {ANSELIbits.ANSI5=val; }
				typedef constexpr_no<PORT_ANALOG_I5> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_I6
			struct pin6{
				bool port()const volatile {return PORTIbits.RI6; }
				#ifndef PORT_IN_I6
				void lat(bool val) {LATIbits.LATI6=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISIbits.TRISI6=val; }
				void opendrain(bool val) {ODCIbits.ODCI6=val; }
				#ifdef PORT_ANALOG_I6
				void analog(bool val) {ANSELIbits.ANSI6=val; }
				typedef constexpr_no<PORT_ANALOG_I6> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_I7
			struct pin7{
				bool port()const volatile {return PORTIbits.RI7; }
				#ifndef PORT_IN_I7
				void lat(bool val) {LATIbits.LATI7=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISIbits.TRISI7=val; }
				void opendrain(bool val) {ODCIbits.ODCI7=val; }
				#ifdef PORT_ANALOG_I7
				void analog(bool val) {ANSELIbits.ANSI7=val; }
				typedef constexpr_no<PORT_ANALOG_I7> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_I8
			struct pin8{
				bool port()const volatile {return PORTIbits.RI8; }
				#ifndef PORT_IN_I8
				void lat(bool val) {LATIbits.LATI8=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISIbits.TRISI8=val; }
				void opendrain(bool val) {ODCIbits.ODCI8=val; }
				#ifdef PORT_ANALOG_I8
				void analog(bool val) {ANSELIbits.ANSI8=val; }
				typedef constexpr_no<PORT_ANALOG_I8> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_I9
			struct pin9{
				bool port()const volatile {return PORTIbits.RI9; }
				#ifndef PORT_IN_I9
				void lat(bool val) {LATIbits.LATI9=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISIbits.TRISI9=val; }
				void opendrain(bool val) {ODCIbits.ODCI9=val; }
				#ifdef PORT_ANALOG_I9
				void analog(bool val) {ANSELIbits.ANSI9=val; }
				typedef constexpr_no<PORT_ANALOG_I9> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_I10
			struct pin10{
				bool port()const volatile {return PORTIbits.RI10; }
				#ifndef PORT_IN_I10
				void lat(bool val) {LATIbits.LATI10=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISIbits.TRISI10=val; }
				void opendrain(bool val) {ODCIbits.ODCI10=val; }
				#ifdef PORT_ANALOG_I10
				void analog(bool val) {ANSELIbits.ANSI10=val; }
				typedef constexpr_no<PORT_ANALOG_I10> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_I11
			struct pin11{
				bool port()const volatile {return PORTIbits.RI11; }
				#ifndef PORT_IN_I11
				void lat(bool val) {LATIbits.LATI11=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISIbits.TRISI11=val; }
				void opendrain(bool val) {ODCIbits.ODCI11=val; }
				#ifdef PORT_ANALOG_I11
				void analog(bool val) {ANSELIbits.ANSI11=val; }
				typedef constexpr_no<PORT_ANALOG_I11> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_I12
			struct pin12{
				bool port()const volatile {return PORTIbits.RI12; }
				#ifndef PORT_IN_I12
				void lat(bool val) {LATIbits.LATI12=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISIbits.TRISI12=val; }
				void opendrain(bool val) {ODCIbits.ODCI12=val; }
				#ifdef PORT_ANALOG_I12
				void analog(bool val) {ANSELIbits.ANSI12=val; }
				typedef constexpr_no<PORT_ANALOG_I12> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_I13
			struct pin13{
				bool port()const volatile {return PORTIbits.RI13; }
				#ifndef PORT_IN_I13
				void lat(bool val) {LATIbits.LATI13=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISIbits.TRISI13=val; }
				void opendrain(bool val) {ODCIbits.ODCI13=val; }
				#ifdef PORT_ANALOG_I13
				void analog(bool val) {ANSELIbits.ANSI13=val; }
				typedef constexpr_no<PORT_ANALOG_I13> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_I14
			struct pin14{
				bool port()const volatile {return PORTIbits.RI14; }
				#ifndef PORT_IN_I14
				void lat(bool val) {LATIbits.LATI14=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISIbits.TRISI14=val; }
				void opendrain(bool val) {ODCIbits.ODCI14=val; }
				#ifdef PORT_ANALOG_I14
				void analog(bool val) {ANSELIbits.ANSI14=val; }
				typedef constexpr_no<PORT_ANALOG_I14> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_I15
			struct pin15{
				bool port()const volatile {return PORTIbits.RI15; }
				#ifndef PORT_IN_I15
				void lat(bool val) {LATIbits.LATI15=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISIbits.TRISI15=val; }
				void opendrain(bool val) {ODCIbits.ODCI15=val; }
				#ifdef PORT_ANALOG_I15
				void analog(bool val) {ANSELIbits.ANSI15=val; }
				typedef constexpr_no<PORT_ANALOG_I15> analog_no;
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
