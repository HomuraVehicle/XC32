#ifndef XC32LIB_TEST_VIRTUALPINREGISTER_INC
#define XC32LIB_TEST_VIRTUALPINREGISTER_INC 100
#
#include<XCBase/constexpr_no.hpp>
#include<XC32Lib/sfr/analog.hpp>
#include"virtual_an_register.hpp"
namespace xc32{
	using namespace xc;
	namespace test{
		template<unsigned int no_, int an_no=-1>
		struct virtual_pin_register{
		public:
			static bool Val;
			static bool IsAnalog;
			static bool IsTris;
		public:
			static void register_initialize() {
				Val=false;
			}
		public:
			bool port()const volatile {return Val; }
			void lat(bool val) {Val=val; }
			void tris(bool val) { IsTris = val; }
			void opendrain(bool val) {return; }
			void analog(bool val) { IsAnalog=val; }
			typedef xc::constexpr_no<an_no> analog_no;
			typedef xc32::sfr::adc::an<analog_no> analog_register;
		};
		template<unsigned int no_>
		struct virtual_pin_register<no_, -1>{
		public:
			static bool Val;
		public:
			static void register_initialize() {
				Val = false;
			}
		public:
			bool port()const volatile { return Val; }
			void lat(bool val) { Val = val; }
			void tris(bool val) { return; }
			void opendrain(bool val) { return; }
			void analog(bool val) { return; }
		};
		template<unsigned int no_, int an_no>
		bool virtual_pin_register<no_, an_no>::Val = false;
		template<unsigned int no_, int an_no>
		bool virtual_pin_register<no_, an_no>::IsAnalog = false;
		template<unsigned int no_, int an_no>
		bool virtual_pin_register<no_, an_no>::IsTris = false;
		template<unsigned int no_>
		bool virtual_pin_register<no_, -1>::Val = false;
	}
}
#
#endif
