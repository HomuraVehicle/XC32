#ifndef XC32LIB_SFR_PORTD_INC
#define XC32LIB_SFR_PORTD_INC 100
#
#include"device_include.h"
#include<XCBase/constexpr_no.hpp>
namespace xc32 {
	namespace sfr{
		struct portD{
			#ifdef PORT_D0
			struct pin0{
				bool port()const volatile {return PORTDbits.RD0; }
				#ifndef PORT_IN_D0
				void lat(bool val) {LATDbits.LATD0=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISDbits.TRISD0=val; }
				void opendrain(bool val) {ODCDbits.ODCD0=val; }
				#ifdef PORT_ANALOG_D0
				void analog(bool val) {ANSELDbits.ANSD0=val; }
				typedef constexpr_no<PORT_ANALOG_D0> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_D1
			struct pin1{
				bool port()const volatile {return PORTDbits.RD1; }
				#ifndef PORT_IN_D1
				void lat(bool val) {LATDbits.LATD1=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISDbits.TRISD1=val; }
				void opendrain(bool val) {ODCDbits.ODCD1=val; }
				#ifdef PORT_ANALOG_D1
				void analog(bool val) {ANSELDbits.ANSD1=val; }
				typedef constexpr_no<PORT_ANALOG_D1> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_D2
			struct pin2{
				bool port()const volatile {return PORTDbits.RD2; }
				#ifndef PORT_IN_D2
				void lat(bool val) {LATDbits.LATD2=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISDbits.TRISD2=val; }
				void opendrain(bool val) {ODCDbits.ODCD2=val; }
				#ifdef PORT_ANALOG_D2
				void analog(bool val) {ANSELDbits.ANSD2=val; }
				typedef constexpr_no<PORT_ANALOG_D2> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_D3
			struct pin3{
				bool port()const volatile {return PORTDbits.RD3; }
				#ifndef PORT_IN_D3
				void lat(bool val) {LATDbits.LATD3=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISDbits.TRISD3=val; }
				void opendrain(bool val) {ODCDbits.ODCD3=val; }
				#ifdef PORT_ANALOG_D3
				void analog(bool val) {ANSELDbits.ANSD3=val; }
				typedef constexpr_no<PORT_ANALOG_D3> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_D4
			struct pin4{
				bool port()const volatile {return PORTDbits.RD4; }
				#ifndef PORT_IN_D4
				void lat(bool val) {LATDbits.LATD4=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISDbits.TRISD4=val; }
				void opendrain(bool val) {ODCDbits.ODCD4=val; }
				#ifdef PORT_ANALOG_D4
				void analog(bool val) {ANSELDbits.ANSD4=val; }
				typedef constexpr_no<PORT_ANALOG_D4> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_D5
			struct pin5{
				bool port()const volatile {return PORTDbits.RD5; }
				#ifndef PORT_IN_D5
				void lat(bool val) {LATDbits.LATD5=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISDbits.TRISD5=val; }
				void opendrain(bool val) {ODCDbits.ODCD5=val; }
				#ifdef PORT_ANALOG_D5
				void analog(bool val) {ANSELDbits.ANSD5=val; }
				typedef constexpr_no<PORT_ANALOG_D5> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_D6
			struct pin6{
				bool port()const volatile {return PORTDbits.RD6; }
				#ifndef PORT_IN_D6
				void lat(bool val) {LATDbits.LATD6=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISDbits.TRISD6=val; }
				void opendrain(bool val) {ODCDbits.ODCD6=val; }
				#ifdef PORT_ANALOG_D6
				void analog(bool val) {ANSELDbits.ANSD6=val; }
				typedef constexpr_no<PORT_ANALOG_D6> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_D7
			struct pin7{
				bool port()const volatile {return PORTDbits.RD7; }
				#ifndef PORT_IN_D7
				void lat(bool val) {LATDbits.LATD7=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISDbits.TRISD7=val; }
				void opendrain(bool val) {ODCDbits.ODCD7=val; }
				#ifdef PORT_ANALOG_D7
				void analog(bool val) {ANSELDbits.ANSD7=val; }
				typedef constexpr_no<PORT_ANALOG_D7> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_D8
			struct pin8{
				bool port()const volatile {return PORTDbits.RD8; }
				#ifndef PORT_IN_D8
				void lat(bool val) {LATDbits.LATD8=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISDbits.TRISD8=val; }
				void opendrain(bool val) {ODCDbits.ODCD8=val; }
				#ifdef PORT_ANALOG_D8
				void analog(bool val) {ANSELDbits.ANSD8=val; }
				typedef constexpr_no<PORT_ANALOG_D8> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_D9
			struct pin9{
				bool port()const volatile {return PORTDbits.RD9; }
				#ifndef PORT_IN_D9
				void lat(bool val) {LATDbits.LATD9=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISDbits.TRISD9=val; }
				void opendrain(bool val) {ODCDbits.ODCD9=val; }
				#ifdef PORT_ANALOG_D9
				void analog(bool val) {ANSELDbits.ANSD9=val; }
				typedef constexpr_no<PORT_ANALOG_D9> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_D10
			struct pin10{
				bool port()const volatile {return PORTDbits.RD10; }
				#ifndef PORT_IN_D10
				void lat(bool val) {LATDbits.LATD10=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISDbits.TRISD10=val; }
				void opendrain(bool val) {ODCDbits.ODCD10=val; }
				#ifdef PORT_ANALOG_D10
				void analog(bool val) {ANSELDbits.ANSD10=val; }
				typedef constexpr_no<PORT_ANALOG_D10> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_D11
			struct pin11{
				bool port()const volatile {return PORTDbits.RD11; }
				#ifndef PORT_IN_D11
				void lat(bool val) {LATDbits.LATD11=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISDbits.TRISD11=val; }
				void opendrain(bool val) {ODCDbits.ODCD11=val; }
				#ifdef PORT_ANALOG_D11
				void analog(bool val) {ANSELDbits.ANSD11=val; }
				typedef constexpr_no<PORT_ANALOG_D11> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_D12
			struct pin12{
				bool port()const volatile {return PORTDbits.RD12; }
				#ifndef PORT_IN_D12
				void lat(bool val) {LATDbits.LATD12=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISDbits.TRISD12=val; }
				void opendrain(bool val) {ODCDbits.ODCD12=val; }
				#ifdef PORT_ANALOG_D12
				void analog(bool val) {ANSELDbits.ANSD12=val; }
				typedef constexpr_no<PORT_ANALOG_D12> analog_no;
#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_D13
			struct pin13{
				bool port()const volatile {return PORTDbits.RD13; }
				#ifndef PORT_IN_D13
				void lat(bool val) {LATDbits.LATD13=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISDbits.TRISD13=val; }
				void opendrain(bool val) {ODCDbits.ODCD13=val; }
				#ifdef PORT_ANALOG_D13
				void analog(bool val) {ANSELDbits.ANSD13=val; }
				typedef constexpr_no<PORT_ANALOG_D13> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_D14
			struct pin14{
				bool port()const volatile {return PORTDbits.RD14; }
				#ifndef PORT_IN_D14
				void lat(bool val) {LATDbits.LATD14=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISDbits.TRISD14=val; }
				void opendrain(bool val) {ODCDbits.ODCD14=val; }
				#ifdef PORT_ANALOG_D14
				void analog(bool val) {ANSELDbits.ANSD14=val; }
				typedef constexpr_no<PORT_ANALOG_D14> analog_no;
				#else
				void analog(bool val) { return; }
				#endif //for PORT_ANALOG_Xnn
			};
			#endif //for PORT_NO
			#ifdef PORT_D15
			struct pin15{
				bool port()const volatile {return PORTDbits.RD15; }
				#ifndef PORT_IN_D15
				void lat(bool val) {LATDbits.LATD15=val; }
				#endif //for PORT_IN
				void tris(bool val) {TRISDbits.TRISD15=val; }
				void opendrain(bool val) {ODCDbits.ODCD15=val; }
				#ifdef PORT_ANALOG_D15
				void analog(bool val) {ANSELDbits.ANSD15=val; }
				typedef constexpr_no<PORT_ANALOG_D15> analog_no;
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
