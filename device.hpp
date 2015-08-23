#ifndef XC32LIB_DEVICE_INC
#define XC32LIB_DEVICE_INC
#
#include"clock.hpp"
#include"interrupt.hpp"
namespace xc32 {
	struct device{
	public:
		bool IsLock;
		clock_block Clock;
		interrupt_block Interrupt;
	public:
		~device(){ unlock(); }
	public:
		void config(uint64 ClockHz_, clock_div::type ClockBusDiv_ = clock_div::div8){
			Clock.config(ClockHz_, ClockBusDiv_);
		}
		bool lock(uint64 ClockHz_, clock_div::type ClockBusDiv_ = clock_div::div8){
			config(ClockHz_, ClockBusDiv_);
			return lock();
		}
		bool lock(){
			if(is_lock())return false;

			//Clockê›íË
			WDTCONbits.ON = 0;
			__asm("nop");
			IEC0 = 0;
			__asm("nop");
			IEC1 = 0;
			__asm("nop");
			IEC2 = 0;
			__asm("nop");
			OSCCONbits.FRCDIV = 0;

			Clock.lock();
			Interrupt.lock();

			IsLock = true;
			return false;
		}
		bool is_lock()const{ return IsLock; }
		void unlock(){
			if(!is_lock())return;

			Clock.unlock();
			Interrupt.unlock();

			IsLock = false;
		}
	};
}
#
#endif
