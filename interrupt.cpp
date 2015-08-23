#ifndef XC32LIB_INTERRUPT_CPP_INC
#define XC32LIB_INTERRUPT_CPP_INC 100
#
#include"interrupt.hpp"
namespace xc32 {
	namespace interrupt {
		unsigned int DefaultLockPriorityLv=7;
		mutex Mutex;
	}
}
#
#endif
