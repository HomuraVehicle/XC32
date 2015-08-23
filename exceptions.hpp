#ifndef XC32LIB_EXCEPTIONS_INC
#define XC32LIB_EXCEPTIONS_INC 100
#
#include <XCBase/exceptions.hpp>
namespace xc32 {
	struct exception :public xc::exception{ 
	public:
		exception() :xc::exception(){}
		exception(code_type Code_) :xc::exception(Code_) {}
	};

}
#define XC32LIB_NOEXCEPT

#ifndef  XC32LIB_NOEXCEPT
#	define xc32_throw(except) throw except
#	define xc32_assert(condition,except) if(!(condition))xc32_throw(except)
#else
#	define xc32_throw(except)
#	define xc32_assert(condition,except)
#endif
#
#endif
