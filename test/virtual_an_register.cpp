#ifndef XC32LIB_TEST_VIRTUALANREGISTER_CPP_INC
#define XC32LIB_TEST_VIRTUALANREGISTER_CPP_INC 100
#
#include"virtual_an_register.hpp"
namespace xc32{
	namespace sfr{
		namespace adc{
			uint16 an< constexpr_no<test::test_analog::test_an0>>::Data = 0;
			bool an< constexpr_no<test::test_analog::test_an0>>::IsReady = true;
			uint16 an< constexpr_no<test::test_analog::test_an1>>::Data = 0;
			bool an< constexpr_no<test::test_analog::test_an1>>::IsReady = true;
			uint16 an< constexpr_no<test::test_analog::test_an2>>::Data = 0;
			bool an< constexpr_no<test::test_analog::test_an2>>::IsReady = true;
			uint16 an< constexpr_no<test::test_analog::test_an3>>::Data = 0;
			bool an< constexpr_no<test::test_analog::test_an3>>::IsReady = true;
			uint16 an< constexpr_no<test::test_analog::test_an4>>::Data = 0;
			bool an< constexpr_no<test::test_analog::test_an4>>::IsReady = true;
			uint16 an< constexpr_no<test::test_analog::test_an5>>::Data = 0;
			bool an< constexpr_no<test::test_analog::test_an5>>::IsReady = true;
			uint16 an< constexpr_no<test::test_analog::test_an6>>::Data = 0;
			bool an< constexpr_no<test::test_analog::test_an6>>::IsReady = true;
			uint16 an< constexpr_no<test::test_analog::test_an7>>::Data = 0;
			bool an< constexpr_no<test::test_analog::test_an7>>::IsReady = true;
		}
	}
}
#
#endif
