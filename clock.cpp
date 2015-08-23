#ifndef XC32LIB_CLOCK_CPP_INC
#define XC32LIB_CLOCK_CPP_INC
#
#include"clock.hpp"
namespace xc32{
	namespace oscillator{
		mutex Mutex;
	}
	uint64 clock_block::SystemClock=0;
	clock_div::type clock_block::BusDiv=clock_div::div8;

//	clock_div::type clock::BusDiv = clock_div::div8;
//	uint64 clock::SystemClock=0;
}
#
#endif
