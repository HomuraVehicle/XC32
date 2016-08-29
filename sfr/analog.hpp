#ifndef XC32_SFR_ANALOG_INC
#define XC32_SFR_ANALOG_INC 100
#
#include"device_include.h"
#include<XCBase/constexpr_no.hpp>
#include<XCBase/type.hpp>
namespace xc32 {
	using namespace xc;
	namespace sfr {
		namespace adc {
			template<typename constexpr_no_>
			struct an {};

			template<>
			struct an<constexpr_no<0>> {
			public:
				uint16 data()const volatile { return ADCDATA0; }
				bool data_ready()const { return ADCDSTAT1bits.ARDY0; }
			};
			template<>
			struct an<constexpr_no<1>> {
			public:
				uint16 data()const volatile { return ADCDATA1; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY1; }
			};
			template<>
			struct an<constexpr_no<2>> {
			public:
				uint16 data()const volatile { return ADCDATA2; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY2; }
			};
			template<>
			struct an<constexpr_no<3>> {
			public:
				uint16 data()const volatile { return ADCDATA3; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY3; }
			};
			template<>
			struct an<constexpr_no<4>> {
			public:
				uint16 data()const volatile { return ADCDATA4; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY4; }
			};
			template<>
			struct an<constexpr_no<5>> {
			public:
				uint16 data()const volatile { return ADCDATA5; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY5; }
			};
			template<>
			struct an<constexpr_no<6>> {
			public:
				uint16 data()const volatile { return ADCDATA6; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY6; }
			};
			template<>
			struct an<constexpr_no<7>> {
			public:
				uint16 data()const volatile { return ADCDATA7; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY7; }
			};
			template<>
			struct an<constexpr_no<8>> {
			public:
				uint16 data()const volatile { return ADCDATA8; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY8; }
			};
			template<>
			struct an<constexpr_no<9>> {
			public:
				uint16 data()const volatile { return ADCDATA9; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY9; }
			};
			template<>
			struct an<constexpr_no<10>> {
			public:
				uint16 data()const volatile { return ADCDATA10; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY10; }
			};
			template<>
			struct an<constexpr_no<11>> {
			public:
				uint16 data()const volatile { return ADCDATA11; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY11; }
			};
			template<>
			struct an<constexpr_no<12>> {
			public:
				uint16 data()const volatile { return ADCDATA12; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY12; }
			};
			template<>
			struct an<constexpr_no<13>> {
			public:
				uint16 data()const volatile { return ADCDATA13; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY13; }
			};
			template<>
			struct an<constexpr_no<14>> {
			public:
				uint16 data()const volatile { return ADCDATA14; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY14; }
			};
			template<>
			struct an<constexpr_no<15>> {
			public:
				uint16 data()const volatile { return ADCDATA15; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY15; }
			};
			template<>
			struct an<constexpr_no<16>> {
			public:
				uint16 data()const volatile { return ADCDATA16; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY16; }
			};
			template<>
			struct an<constexpr_no<17>> {
			public:
				uint16 data()const volatile { return ADCDATA17; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY17; }
			};
			template<>
			struct an<constexpr_no<18>> {
			public:
				uint16 data()const volatile { return ADCDATA18; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY18; }
			};
			template<>
			struct an<constexpr_no<19>> {
			public:
				uint16 data()const volatile { return ADCDATA19; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY19; }
			};
			template<>
			struct an<constexpr_no<20>> {
			public:
				uint16 data()const volatile { return ADCDATA20; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY20; }
			};
			template<>
			struct an<constexpr_no<21>> {
			public:
				uint16 data()const volatile { return ADCDATA21; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY21; }
			};
			template<>
			struct an<constexpr_no<22>> {
			public:
				uint16 data()const volatile { return ADCDATA22; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY22; }
			};
			template<>
			struct an<constexpr_no<23>> {
			public:
				uint16 data()const volatile { return ADCDATA23; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY23; }
			};
			template<>
			struct an<constexpr_no<24>> {
			public:
				uint16 data()const volatile { return ADCDATA24; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY24; }
			};
			template<>
			struct an<constexpr_no<25>> {
			public:
				uint16 data()const volatile { return ADCDATA25; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY25; }
			};
			template<>
			struct an<constexpr_no<26>> {
			public:
				uint16 data()const volatile { return ADCDATA26; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY26; }
			};
			template<>
			struct an<constexpr_no<27>> {
			public:
				uint16 data()const volatile { return ADCDATA27; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY27; }
			};
			template<>
			struct an<constexpr_no<28>> {
			public:
				uint16 data()const volatile { return ADCDATA28; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY28; }
			};
			template<>
			struct an<constexpr_no<29>> {
			public:
				uint16 data()const volatile { return ADCDATA29; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY29; }
			};
			template<>
			struct an<constexpr_no<30>> {
			public:
				uint16 data()const volatile { return ADCDATA30; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY30; }
			};
			template<>
			struct an<constexpr_no<31>> {
			public:
				uint16 data()const volatile { return ADCDATA31; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY31; }
			};
			template<>
			struct an<constexpr_no<32>>{
			public:
				uint16 data()const volatile{ return ADCDATA32; }
				bool data_ready()const{ return ADCDSTAT2bits.ARDY32; }
			};
			template<>
			struct an<constexpr_no<33>>{
			public:
				uint16 data()const volatile{ return ADCDATA33; }
				bool data_ready()const{ return ADCDSTAT2bits.ARDY33; }
			};
			template<>
			struct an<constexpr_no<34>>{
			public:
				uint16 data()const volatile{ return ADCDATA34; }
				bool data_ready()const{ return ADCDSTAT2bits.ARDY34; }
			};
			template<>
			struct an<constexpr_no<35>>{
			public:
				uint16 data()const volatile{ return ADCDATA35; }
				bool data_ready()const{ return ADCDSTAT2bits.ARDY35; }
			};
			template<>
			struct an<constexpr_no<36>>{
			public:
				uint16 data()const volatile{ return ADCDATA36; }
				bool data_ready()const{ return ADCDSTAT2bits.ARDY36; }
			};
			template<>
			struct an<constexpr_no<37>>{
			public:
				uint16 data()const volatile{ return ADCDATA37; }
				bool data_ready()const{ return ADCDSTAT2bits.ARDY37; }
			};
			template<>
			struct an<constexpr_no<38>>{
			public:
				uint16 data()const volatile{ return ADCDATA38; }
				bool data_ready()const{ return ADCDSTAT2bits.ARDY38; }
			};
			template<>
			struct an<constexpr_no<39>>{
			public:
				uint16 data()const volatile{ return ADCDATA39; }
				bool data_ready()const{ return ADCDSTAT2bits.ARDY39; }
			};
			template<>
			struct an<constexpr_no<40>>{
			public:
				uint16 data()const volatile{ return ADCDATA40; }
				bool data_ready()const{ return ADCDSTAT2bits.ARDY40; }
			};
			template<>
			struct an<constexpr_no<41>>{
			public:
				uint16 data()const volatile{ return ADCDATA41; }
				bool data_ready()const{ return ADCDSTAT2bits.ARDY41; }
			};
			template<>
			struct an<constexpr_no<42>>{
			public:
				uint16 data()const volatile{ return ADCDATA42; }
				bool data_ready()const{ return ADCDSTAT2bits.ARDY42; }
			};
			template<>
			struct an<constexpr_no<43>>{
			public:
				uint16 data()const volatile{ return ADCDATA43; }
				bool data_ready()const{ return ADCDSTAT2bits.ARDY43; }
			};
			template<>
			struct an<constexpr_no<44>>{
			public:
				uint16 data()const volatile{ return ADCDATA44; }
				bool data_ready()const{ return ADCDSTAT2bits.ARDY44; }
			};
			struct an<constexpr_no<45>>{
			public:
				uint16 data()const volatile{ return ADCDATA0; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY0; }
			};
			template<>
			struct an<constexpr_no<46>>{
			public:
				uint16 data()const volatile{ return ADCDATA1; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY1; }
			};
			template<>
			struct an<constexpr_no<47>>{
			public:
				uint16 data()const volatile{ return ADCDATA2; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY2; }
			};
			template<>
			struct an<constexpr_no<48>>{
			public:
				uint16 data()const volatile{ return ADCDATA3; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY3; }
			};
			template<>
			struct an<constexpr_no<49>>{
			public:
				uint16 data()const volatile{ return ADCDATA4; }
				bool data_ready()const{ return ADCDSTAT1bits.ARDY4; }
			};

		}
	}
}
#
#endif
