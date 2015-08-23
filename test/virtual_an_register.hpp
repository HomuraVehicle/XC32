#ifndef XC32LIB_TEST_VIRTUALANREGISTER_INC
#define XC32LIB_TEST_VIRTUALANREGISTER_INC 100
#
#include<XCBase/constexpr_no.hpp>
#include<XC32Lib/sfr/analog.hpp>
namespace xc32{
	using namespace xc;
	namespace test{
		enum test_analog : int { test_an0 = 100, test_an1, test_an2, test_an3, test_an4, test_an5, test_an6, test_an7 };
	}
	namespace sfr{
		namespace adc{
			template<>
			struct an < constexpr_no<test::test_analog::test_an0>> {
				static uint16 Data;
				static bool IsReady;
			public:
				uint16 data()const { return Data; }
				bool data_ready()const { return IsReady; }
			};
			template<>
			struct an < constexpr_no<test::test_analog::test_an1> > {
				static uint16 Data;
				static bool IsReady;
			public:
				uint16 data()const volatile { return Data; }
				bool data_ready()const { return IsReady; }
			};
			template<>
			struct an < constexpr_no<test::test_analog::test_an2> > {
				static uint16 Data;
				static bool IsReady;
			public:
				uint16 data()const volatile { return Data; }
				bool data_ready()const { return IsReady; }
			};
			template<>
			struct an < constexpr_no<test::test_analog::test_an3> > {
				static uint16 Data;
				static bool IsReady;
			public:
				uint16 data()const volatile { return Data; }
				bool data_ready()const { return IsReady; }
			};
			template<>
			struct an < constexpr_no<test::test_analog::test_an4>> {
				static uint16 Data;
				static bool IsReady;
			public:
				uint16 data()const { return Data; }
				bool data_ready()const { return IsReady; }
			};
			template<>
			struct an < constexpr_no<test::test_analog::test_an5> > {
				static uint16 Data;
				static bool IsReady;
			public:
				uint16 data()const volatile { return Data; }
				bool data_ready()const { return IsReady; }
			};
			template<>
			struct an < constexpr_no<test::test_analog::test_an6> > {
				static uint16 Data;
				static bool IsReady;
			public:
				uint16 data()const volatile { return Data; }
				bool data_ready()const { return IsReady; }
			};
			template<>
			struct an < constexpr_no<test::test_analog::test_an7> > {
				static uint16 Data;
				static bool IsReady;
			public:
				uint16 data()const volatile { return Data; }
				bool data_ready()const { return IsReady; }
			};
		}
	}
}
#
#endif
