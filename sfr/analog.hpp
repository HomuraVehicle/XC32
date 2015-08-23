#ifndef XC32LIB_SFR_ANALOG_INC
#define XC32LIB_SFR_ANALOG_INC 100
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
				uint16 data()const volatile { return AD1DATA0; }
				bool data_ready()const { return (AD1DSTAT1 & 1) != 0; }
			};
			template<>
			struct an<constexpr_no<1>> {
			public:
				uint16 data()const volatile { return AD1DATA1; }
				bool data_ready()const { return (AD1DSTAT1 & 2) != 0; }
			};
			template<>
			struct an<constexpr_no<2>> {
			public:
				uint16 data()const volatile { return AD1DATA2; }
				bool data_ready()const { return (AD1DSTAT1 & 4) != 0; }
			};
			template<>
			struct an<constexpr_no<3>> {
			public:
				uint16 data()const volatile { return AD1DATA3; }
				bool data_ready()const { return (AD1DSTAT1 & 8) != 0; }
			};
			template<>
			struct an<constexpr_no<4>> {
			public:
				uint16 data()const volatile { return AD1DATA4; }
				bool data_ready()const { return (AD1DSTAT1 & 16) != 0; }
			};
			template<>
			struct an<constexpr_no<5>> {
			public:
				uint16 data()const volatile { return AD1DATA5; }
				bool data_ready()const { return (AD1DSTAT1 & 32) != 0; }
			};
			template<>
			struct an<constexpr_no<6>> {
			public:
				uint16 data()const volatile { return AD1DATA6; }
				bool data_ready()const { return (AD1DSTAT1 & 64) != 0; }
			};
			template<>
			struct an<constexpr_no<7>> {
			public:
				uint16 data()const volatile { return AD1DATA7; }
				bool data_ready()const { return (AD1DSTAT1 & 128) != 0; }
			};
			template<>
			struct an<constexpr_no<8>> {
			public:
				uint16 data()const volatile { return AD1DATA8; }
				bool data_ready()const { return (AD1DSTAT1 & 256) != 0; }
			};
			template<>
			struct an<constexpr_no<9>> {
			public:
				uint16 data()const volatile { return AD1DATA9; }
				bool data_ready()const { return (AD1DSTAT1 & 512) != 0; }
			};
			template<>
			struct an<constexpr_no<10>> {
			public:
				uint16 data()const volatile { return AD1DATA10; }
				bool data_ready()const { return (AD1DSTAT1 & 1024) != 0; }
			};
			template<>
			struct an<constexpr_no<11>> {
			public:
				uint16 data()const volatile { return AD1DATA11; }
				bool data_ready()const { return (AD1DSTAT1 & 2048u) != 0; }
			};
			template<>
			struct an<constexpr_no<12>> {
			public:
				uint16 data()const volatile { return AD1DATA12; }
				bool data_ready()const { return (AD1DSTAT1 & 4096u) != 0; }
			};
			template<>
			struct an<constexpr_no<13>> {
			public:
				uint16 data()const volatile { return AD1DATA13; }
				bool data_ready()const { return (AD1DSTAT1 & 8192u) != 0; }
			};
			template<>
			struct an<constexpr_no<14>> {
			public:
				uint16 data()const volatile { return AD1DATA14; }
				bool data_ready()const { return (AD1DSTAT1 & 16384u) != 0; }
			};
			template<>
			struct an<constexpr_no<15>> {
			public:
				uint16 data()const volatile { return AD1DATA15; }
				bool data_ready()const { return (AD1DSTAT1 & 32768u) != 0; }
			};
			template<>
			struct an<constexpr_no<16>> {
			public:
				uint16 data()const volatile { return AD1DATA16; }
				bool data_ready()const { return (AD1DSTAT1 & 65536u) != 0; }
			};
			template<>
			struct an<constexpr_no<17>> {
			public:
				uint16 data()const volatile { return AD1DATA17; }
				bool data_ready()const { return (AD1DSTAT1 & 131072u) != 0; }
			};
			template<>
			struct an<constexpr_no<18>> {
			public:
				uint16 data()const volatile { return AD1DATA18; }
				bool data_ready()const { return (AD1DSTAT1 & 262144u) != 0; }
			};
			template<>
			struct an<constexpr_no<19>> {
			public:
				uint16 data()const volatile { return AD1DATA19; }
				bool data_ready()const { return (AD1DSTAT1 & 524288u) != 0; }
			};
			template<>
			struct an<constexpr_no<20>> {
			public:
				uint16 data()const volatile { return AD1DATA20; }
				bool data_ready()const { return (AD1DSTAT1 & 1048576u) != 0; }
			};
			template<>
			struct an<constexpr_no<21>> {
			public:
				uint16 data()const volatile { return AD1DATA21; }
				bool data_ready()const { return (AD1DSTAT1 & 2097152u) != 0; }
			};
			template<>
			struct an<constexpr_no<22>> {
			public:
				uint16 data()const volatile { return AD1DATA22; }
				bool data_ready()const { return (AD1DSTAT1 & 4194304u) != 0; }
			};
			template<>
			struct an<constexpr_no<23>> {
			public:
				uint16 data()const volatile { return AD1DATA23; }
				bool data_ready()const { return (AD1DSTAT1 & 8388608u) != 0; }
			};
			template<>
			struct an<constexpr_no<24>> {
			public:
				uint16 data()const volatile { return AD1DATA24; }
				bool data_ready()const { return (AD1DSTAT1 & 16777216u) != 0; }
			};
			template<>
			struct an<constexpr_no<25>> {
			public:
				uint16 data()const volatile { return AD1DATA25; }
				bool data_ready()const { return (AD1DSTAT1 & 33554432u) != 0; }
			};
			template<>
			struct an<constexpr_no<26>> {
			public:
				uint16 data()const volatile { return AD1DATA26; }
				bool data_ready()const { return (AD1DSTAT1 & 67108864u) != 0; }
			};
			template<>
			struct an<constexpr_no<27>> {
			public:
				uint16 data()const volatile { return AD1DATA27; }
				bool data_ready()const { return (AD1DSTAT1 & 134217728u) != 0; }
			};
			template<>
			struct an<constexpr_no<28>> {
			public:
				uint16 data()const volatile { return AD1DATA28; }
				bool data_ready()const { return (AD1DSTAT1 & 268435456u) != 0; }
			};
			template<>
			struct an<constexpr_no<29>> {
			public:
				uint16 data()const volatile { return AD1DATA29; }
				bool data_ready()const { return (AD1DSTAT1 & 536870912u) != 0; }
			};
			template<>
			struct an<constexpr_no<30>> {
			public:
				uint16 data()const volatile { return AD1DATA30; }
				bool data_ready()const { return (AD1DSTAT1 & 1073741824u) != 0; }
			};
			template<>
			struct an<constexpr_no<31>> {
			public:
				uint16 data()const volatile { return AD1DATA31; }
				bool data_ready()const { return (AD1DSTAT1 & 2147483648u) != 0; }
			};

		}
	}
}
#
#endif
