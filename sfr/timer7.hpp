#ifndef XC32LIB_SFR_TIMER7_INC
#define XC32LIB_SFR_TIMER7_INC 100
#
/*=====timer7=====*/
#include"device_include.h"
#include"exclusive_mixin.hpp"
#include"sfr_register_mixin.hpp"
#include"interrupt.hpp"
#include"timer_base.hpp"

#if defined(XC32LIB_PIC32MX)
#elif defined(XC32LIB_PIC32MZ)
#	define XC32LIB_TIMER7_IRQ 32
#	define XC32LIB_TIMER7_VEC _TIMER_7_VECTOR
#	define XC32LIB_TIMER7_IF IFS1bits.T7IF
#	define XC32LIB_TIMER7_IE IEC1bits.T7IE
#	define XC32LIB_TIMER7_IP IPC8bits.T7IP
#	define XC32LIB_TIMER7_IS IPC8bits.T7IS
#else
#	error Unknown device!
#endif

#ifndef XC32LIB_SFR_TIMER7_EXPLICITINTERRUPT
#	ifndef XC32LIB_DEBUGMODE
#		define x_xc32_sfr_timer7_interrupt(void) __ISR(XC32LIB_TIMER7_VEC, XC32LIB_TIMER7_IPL_FOR_ISR) T7Interrupt(void)//*/func(void)
#	else
extern "C"{void x_xc32_sfr_timer7_interrupt(void); }
#	endif
#else
#	ifndef XC32LIB_DEBUGMODE
#		define xc32_sfr_timer7_interrupt(void) __ISR(XC32LIB_TIMER7_VEC, XC32LIB_TIMER7_IPL_FOR_ISR) T7Interrupt(void)//*/func(void)
#	else
extern "C"{void xc32_sfr_timer7_interrupt(void); }
#	endif
#endif

namespace xc32{
	namespace sfr{
		struct timer7:public sfr_register_mixin<timer7>, public exclusive_mixin<timer7>{
			static unsigned int timer_no(){ return 7; }
			typedef timer::normal_prescaler type_prescaler;
		public:
			//Timer clock source select bit : TxCONbits.TCS  0:Internal ,1:external
			void clock_select(bool val_){T7CONbits.TCS=static_cast<unsigned char>(val_);}
			bool clock_select()const{return static_cast<bool>(T7CONbits.TCS);}
			//Timer Gated Time Accumulation Enable bit : TxCONbits.TGATE
			void gate_enable(bool val_){T7CONbits.TGATE=static_cast<unsigned char>(val_);}
			bool gate_enable()const{return static_cast<bool>(T7CONbits.TGATE);}
			//Interrupt Flag : IFSxbits.I2CxMIF
			void interrupt_flag(bool val_){XC32LIB_TIMER7_IF=static_cast<unsigned char>(val_);}
			bool interrupt_flag()const {return static_cast<bool>(XC32LIB_TIMER7_IF);}
			//interrupt enable bit : IECxbits.I2CxMIE
			void interrupt_enable(bool val_){XC32LIB_TIMER7_IE=static_cast<unsigned char>(val_);}
			bool interrupt_enable()const{return static_cast<bool>(XC32LIB_TIMER7_IE);}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_priority_level(unsigned char val_){XC32LIB_TIMER7_IP=val_;}
			unsigned char interrupt_priority_level(){return XC32LIB_TIMER7_IP;}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_sub_priority_level(unsigned char val_){XC32LIB_TIMER7_IS=val_;}
			unsigned char interrupt_sub_priority_level(){return XC32LIB_TIMER7_IS;}
			//Timer ON bit : TxCONbits.ON
			void enable(bool val_){T7CONbits.ON=static_cast<unsigned char>(val_);}
			bool enable()const{return static_cast<bool>(T7CONbits.ON);}
			//Prescaler bits : TxCONbits.TCKPS,
			void prescaler(type_prescaler::div val_){T7CONbits.TCKPS=static_cast<unsigned char>(val_);}
			type_prescaler::div prescaler()const{return static_cast<type_prescaler::div >(T7CONbits.TCKPS);}
			//period register : PRx
			void period(unsigned int val_){PR7=val_;}
			unsigned int period()const{return PR7;}
			//timer count register : TMRx
			void count(unsigned int val_){TMR7=val_;}
			unsigned int count()const {return TMR7;}
			//control register : TxCON
			void reset_all_config(){
				T7CON &= 0x00010000;			//ONˆÈŠO‚ð0‚ÅƒtƒBƒ‹

				count(0);
				interrupt_enable(false);

				interrupt_function(0);
			}
		private:
			static interrupt::function* interrupt_ptr;
		public:
			const interrupt::function* interrupt_function()const{return interrupt_ptr;}
			void interrupt_function(interrupt::function* ptr_) { interrupt_ptr=ptr_; }
		public:
			static const unsigned char ipl;
		};
	}
}

#
#endif
