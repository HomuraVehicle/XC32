#ifndef XC32_SFR_PORTK_INC
#define XC32_SFR_PORTK_INC 100
#
#include"device_include.h"
#include<XCBase/constexpr_no.hpp>
namespace xc32 {
	namespace sfr{
		struct portK{
			#ifdef PORT_K0
			struct pin0{
				bool port()const volatile {return PORTKbits.RK0; }
				#ifndef PORT_IN_K0
				void lat(bool val) {LATKbits.LATK0=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISKbits.TRISK0=val; }
				void opendrain(bool val) {ODCKbits.ODCK0=val; }
				#ifdef PORT_ANALOG_K0
				void analog(bool val) {ANSELKbits.ANSK0=val; }
				typedef constexpr_no<PORT_ANALOG_K0> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_K1
			struct pin1{
				bool port()const volatile {return PORTKbits.RK1; }
				#ifndef PORT_IN_K1
				void lat(bool val) {LATKbits.LATK1=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISKbits.TRISK1=val; }
				void opendrain(bool val) {ODCKbits.ODCK1=val; }
				#ifdef PORT_ANALOG_K1
				void analog(bool val) {ANSELKbits.ANSK1=val; }
				typedef constexpr_no<PORT_ANALOG_K1> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_K2
			struct pin2{
				bool port()const volatile {return PORTKbits.RK2; }
				#ifndef PORT_IN_K2
				void lat(bool val) {LATKbits.LATK2=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISKbits.TRISK2=val; }
				void opendrain(bool val) {ODCKbits.ODCK2=val; }
				#ifdef PORT_ANALOG_K2
				void analog(bool val) {ANSELKbits.ANSK2=val; }
				typedef constexpr_no<PORT_ANALOG_K2> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_K3
			struct pin3{
				bool port()const volatile {return PORTKbits.RK3; }
				#ifndef PORT_IN_K3
				void lat(bool val) {LATKbits.LATK3=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISKbits.TRISK3=val; }
				void opendrain(bool val) {ODCKbits.ODCK3=val; }
				#ifdef PORT_ANALOG_K3
				void analog(bool val) {ANSELKbits.ANSK3=val; }
				typedef constexpr_no<PORT_ANALOG_K3> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_K4
			struct pin4{
				bool port()const volatile {return PORTKbits.RK4; }
				#ifndef PORT_IN_K4
				void lat(bool val) {LATKbits.LATK4=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISKbits.TRISK4=val; }
				void opendrain(bool val) {ODCKbits.ODCK4=val; }
				#ifdef PORT_ANALOG_K4
				void analog(bool val) {ANSELKbits.ANSK4=val; }
				typedef constexpr_no<PORT_ANALOG_K4> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_K5
			struct pin5{
				bool port()const volatile {return PORTKbits.RK5; }
				#ifndef PORT_IN_K5
				void lat(bool val) {LATKbits.LATK5=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISKbits.TRISK5=val; }
				void opendrain(bool val) {ODCKbits.ODCK5=val; }
				#ifdef PORT_ANALOG_K5
				void analog(bool val) {ANSELKbits.ANSK5=val; }
				typedef constexpr_no<PORT_ANALOG_K5> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_K6
			struct pin6{
				bool port()const volatile {return PORTKbits.RK6; }
				#ifndef PORT_IN_K6
				void lat(bool val) {LATKbits.LATK6=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISKbits.TRISK6=val; }
				void opendrain(bool val) {ODCKbits.ODCK6=val; }
				#ifdef PORT_ANALOG_K6
				void analog(bool val) {ANSELKbits.ANSK6=val; }
				typedef constexpr_no<PORT_ANALOG_K6> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_K7
			struct pin7{
				bool port()const volatile {return PORTKbits.RK7; }
				#ifndef PORT_IN_K7
				void lat(bool val) {LATKbits.LATK7=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISKbits.TRISK7=val; }
				void opendrain(bool val) {ODCKbits.ODCK7=val; }
				#ifdef PORT_ANALOG_K7
				void analog(bool val) {ANSELKbits.ANSK7=val; }
				typedef constexpr_no<PORT_ANALOG_K7> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_K8
			struct pin8{
				bool port()const volatile {return PORTKbits.RK8; }
				#ifndef PORT_IN_K8
				void lat(bool val) {LATKbits.LATK8=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISKbits.TRISK8=val; }
				void opendrain(bool val) {ODCKbits.ODCK8=val; }
				#ifdef PORT_ANALOG_K8
				void analog(bool val) {ANSELKbits.ANSK8=val; }
				typedef constexpr_no<PORT_ANALOG_K8> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_K9
			struct pin9{
				bool port()const volatile {return PORTKbits.RK9; }
				#ifndef PORT_IN_K9
				void lat(bool val) {LATKbits.LATK9=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISKbits.TRISK9=val; }
				void opendrain(bool val) {ODCKbits.ODCK9=val; }
				#ifdef PORT_ANALOG_K9
				void analog(bool val) {ANSELKbits.ANSK9=val; }
				typedef constexpr_no<PORT_ANALOG_K9> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_K10
			struct pin10{
				bool port()const volatile {return PORTKbits.RK10; }
				#ifndef PORT_IN_K10
				void lat(bool val) {LATKbits.LATK10=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISKbits.TRISK10=val; }
				void opendrain(bool val) {ODCKbits.ODCK10=val; }
				#ifdef PORT_ANALOG_K10
				void analog(bool val) {ANSELKbits.ANSK10=val; }
				typedef constexpr_no<PORT_ANALOG_K10> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_K11
			struct pin11{
				bool port()const volatile {return PORTKbits.RK11; }
				#ifndef PORT_IN_K11
				void lat(bool val) {LATKbits.LATK11=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISKbits.TRISK11=val; }
				void opendrain(bool val) {ODCKbits.ODCK11=val; }
				#ifdef PORT_ANALOG_K11
				void analog(bool val) {ANSELKbits.ANSK11=val; }
				typedef constexpr_no<PORT_ANALOG_K11> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_K12
			struct pin12{
				bool port()const volatile {return PORTKbits.RK12; }
				#ifndef PORT_IN_K12
				void lat(bool val) {LATKbits.LATK12=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISKbits.TRISK12=val; }
				void opendrain(bool val) {ODCKbits.ODCK12=val; }
				#ifdef PORT_ANALOG_K12
				void analog(bool val) {ANSELKbits.ANSK12=val; }
				typedef constexpr_no<PORT_ANALOG_K12> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_K13
			struct pin13{
				bool port()const volatile {return PORTKbits.RK13; }
				#ifndef PORT_IN_K13
				void lat(bool val) {LATKbits.LATK13=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISKbits.TRISK13=val; }
				void opendrain(bool val) {ODCKbits.ODCK13=val; }
				#ifdef PORT_ANALOG_K13
				void analog(bool val) {ANSELKbits.ANSK13=val; }
				typedef constexpr_no<PORT_ANALOG_K13> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_K14
			struct pin14{
				bool port()const volatile {return PORTKbits.RK14; }
				#ifndef PORT_IN_K14
				void lat(bool val) {LATKbits.LATK14=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISKbits.TRISK14=val; }
				void opendrain(bool val) {ODCKbits.ODCK14=val; }
				#ifdef PORT_ANALOG_K14
				void analog(bool val) {ANSELKbits.ANSK14=val; }
				typedef constexpr_no<PORT_ANALOG_K14> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_K15
			struct pin15{
				bool port()const volatile {return PORTKbits.RK15; }
				#ifndef PORT_IN_K15
				void lat(bool val) {LATKbits.LATK15=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISKbits.TRISK15=val; }
				void opendrain(bool val) {ODCKbits.ODCK15=val; }
				#ifdef PORT_ANALOG_K15
				void analog(bool val) {ANSELKbits.ANSK15=val; }
				typedef constexpr_no<PORT_ANALOG_K15> analog_no;
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
