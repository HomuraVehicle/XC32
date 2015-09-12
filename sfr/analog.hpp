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
				bool data_ready()const { return (ADCDSTAT1 & 1) != 0; }
			};
			template<>
			struct an<constexpr_no<1>> {
			public:
				uint16 data()const volatile { return ADCDATA1; }
				bool data_ready()const { return (ADCDSTAT1 & 2) != 0; }
			};
			template<>
			struct an<constexpr_no<2>> {
			public:
				uint16 data()const volatile { return ADCDATA2; }
				bool data_ready()const { return (ADCDSTAT1 & 4) != 0; }
			};
			template<>
			struct an<constexpr_no<3>> {
			public:
				uint16 data()const volatile { return ADCDATA3; }
				bool data_ready()const { return (ADCDSTAT1 & 8) != 0; }
			};
			template<>
			struct an<constexpr_no<4>> {
			public:
				uint16 data()const volatile { return ADCDATA4; }
				bool data_ready()const { return (ADCDSTAT1 & 16) != 0; }
			};
			template<>
			struct an<constexpr_no<5>> {
			public:
				uint16 data()const volatile { return ADCDATA5; }
				bool data_ready()const { return (ADCDSTAT1 & 32) != 0; }
			};
			template<>
			struct an<constexpr_no<6>> {
			public:
				uint16 data()const volatile { return ADCDATA6; }
				bool data_ready()const { return (ADCDSTAT1 & 64) != 0; }
			};
			template<>
			struct an<constexpr_no<7>> {
			public:
				uint16 data()const volatile { return ADCDATA7; }
				bool data_ready()const { return (ADCDSTAT1 & 128) != 0; }
			};
			template<>
			struct an<constexpr_no<8>> {
			public:
				uint16 data()const volatile { return ADCDATA8; }
				bool data_ready()const { return (ADCDSTAT1 & 256) != 0; }
			};
			template<>
			struct an<constexpr_no<9>> {
			public:
				uint16 data()const volatile { return ADCDATA9; }
				bool data_ready()const { return (ADCDSTAT1 & 512) != 0; }
			};
			template<>
			struct an<constexpr_no<10>> {
			public:
				uint16 data()const volatile { return ADCDATA10; }
				bool data_ready()const { return (ADCDSTAT1 & 1024) != 0; }
			};
			template<>
			struct an<constexpr_no<11>> {
			public:
				uint16 data()const volatile { return ADCDATA11; }
				bool data_ready()const { return (ADCDSTAT1 & 2048u) != 0; }
			};
			template<>
			struct an<constexpr_no<12>> {
			public:
				uint16 data()const volatile { return ADCDATA12; }
				bool data_ready()const { return (ADCDSTAT1 & 4096u) != 0; }
			};
			template<>
			struct an<constexpr_no<13>> {
			public:
				uint16 data()const volatile { return ADCDATA13; }
				bool data_ready()const { return (ADCDSTAT1 & 8192u) != 0; }
			};
			template<>
			struct an<constexpr_no<14>> {
			public:
				uint16 data()const volatile { return ADCDATA14; }
				bool data_ready()const { return (ADCDSTAT1 & 16384u) != 0; }
			};
			template<>
			struct an<constexpr_no<15>> {
			public:
				uint16 data()const volatile { return ADCDATA15; }
				bool data_ready()const { return (ADCDSTAT1 & 32768u) != 0; }
			};
			template<>
			struct an<constexpr_no<16>> {
			public:
				uint16 data()const volatile { return ADCDATA16; }
				bool data_ready()const { return (ADCDSTAT1 & 65536u) != 0; }
			};
			template<>
			struct an<constexpr_no<17>> {
			public:
				uint16 data()const volatile { return ADCDATA17; }
				bool data_ready()const { return (ADCDSTAT1 & 131072u) != 0; }
			};
			template<>
			struct an<constexpr_no<18>> {
			public:
				uint16 data()const volatile { return ADCDATA18; }
				bool data_ready()const { return (ADCDSTAT1 & 262144u) != 0; }
			};
			template<>
			struct an<constexpr_no<19>> {
			public:
				uint16 data()const volatile { return ADCDATA19; }
				bool data_ready()const { return (ADCDSTAT1 & 524288u) != 0; }
			};
			template<>
			struct an<constexpr_no<20>> {
			public:
				uint16 data()const volatile { return ADCDATA20; }
				bool data_ready()const { return (ADCDSTAT1 & 1048576u) != 0; }
			};
			template<>
			struct an<constexpr_no<21>> {
			public:
				uint16 data()const volatile { return ADCDATA21; }
				bool data_ready()const { return (ADCDSTAT1 & 2097152u) != 0; }
			};
			template<>
			struct an<constexpr_no<22>> {
			public:
				uint16 data()const volatile { return ADCDATA22; }
				bool data_ready()const { return (ADCDSTAT1 & 4194304u) != 0; }
			};
			template<>
			struct an<constexpr_no<23>> {
			public:
				uint16 data()const volatile { return ADCDATA23; }
				bool data_ready()const { return (ADCDSTAT1 & 8388608u) != 0; }
			};
			template<>
			struct an<constexpr_no<24>> {
			public:
				uint16 data()const volatile { return ADCDATA24; }
				bool data_ready()const { return (ADCDSTAT1 & 16777216u) != 0; }
			};
			template<>
			struct an<constexpr_no<25>> {
			public:
				uint16 data()const volatile { return ADCDATA25; }
				bool data_ready()const { return (ADCDSTAT1 & 33554432u) != 0; }
			};
			template<>
			struct an<constexpr_no<26>> {
			public:
				uint16 data()const volatile { return ADCDATA26; }
				bool data_ready()const { return (ADCDSTAT1 & 67108864u) != 0; }
			};
			template<>
			struct an<constexpr_no<27>> {
			public:
				uint16 data()const volatile { return ADCDATA27; }
				bool data_ready()const { return (ADCDSTAT1 & 134217728u) != 0; }
			};
			template<>
			struct an<constexpr_no<28>> {
			public:
				uint16 data()const volatile { return ADCDATA28; }
				bool data_ready()const { return (ADCDSTAT1 & 268435456u) != 0; }
			};
			template<>
			struct an<constexpr_no<29>> {
			public:
				uint16 data()const volatile { return ADCDATA29; }
				bool data_ready()const { return (ADCDSTAT1 & 536870912u) != 0; }
			};
			template<>
			struct an<constexpr_no<30>> {
			public:
				uint16 data()const volatile { return ADCDATA30; }
				bool data_ready()const { return (ADCDSTAT1 & 1073741824u) != 0; }
			};
			template<>
			struct an<constexpr_no<31>> {
			public:
				uint16 data()const volatile { return ADCDATA31; }
				bool data_ready()const { return (ADCDSTAT1 & 2147483648u) != 0; }
			};

		}
	}
}
#
#endif
