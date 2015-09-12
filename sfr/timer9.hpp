#ifndef XC32_SFR_TIMER9_INC
#define XC32_SFR_TIMER9_INC 100
#
/*=====timer9=====*/
#include"device_include.h"
#include"exclusive_mixin.hpp"
#include"sfr_register_mixin.hpp"
#include"interrupt.hpp"
#include"timer_base.hpp"

#if defined(XC32_PIC32MX)
#elif defined(XC32_PIC32MZ)
#	define XC32_TIMER9_IRQ 40
#	define XC32_TIMER9_VEC _TIMER_9_VECTOR
#	define XC32_TIMER9_IF IFS1bits.T9IF
#	define XC32_TIMER9_IE IEC1bits.T9IE
#	define XC32_TIMER9_IP IPC10bits.T9IP
#	define XC32_TIMER9_IS IPC10bits.T9IS
#else
#	error Unknown device!
#endif

#ifndef XC32_SFR_TIMER9_EXPLICITINTERRUPT
#	ifndef XC32_DEBUGMODE
#		define x_xc32_sfr_timer9_interrupt(void) __ISR(XC32_TIMER9_VEC, XC32_TIMER9_IPL_FOR_ISR) T9Interrupt(void)//*/func(void)
#	else
extern "C"{void x_xc32_sfr_timer9_interrupt(void); }
#	endif
#else
#	ifndef XC32_DEBUGMODE
#		define xc32_sfr_timer9_interrupt(void) __ISR(XC32_TIMER9_VEC, XC32_TIMER9_IPL_FOR_ISR) T9Interrupt(void)//*/func(void)
#	else
extern "C"{void xc32_sfr_timer9_interrupt(void); }
#	endif
#endif

namespace xc32{
	namespace sfr{
		struct timer9:public sfr_register_mixin<timer9>, public exclusive_mixin<timer9>{
			static unsigned int timer_no(){ return 9; }
			typedef timer::normal_prescaler type_prescaler;
		public:
			//Timer clock source select bit : TxCONbits.TCS  0:Internal ,1:external
			void clock_select(bool val_){T9CONbits.TCS=static_cast<unsigned char>(val_);}
			bool clock_select()const{return static_cast<bool>(T9CONbits.TCS);}
			//Timer Gated Time Accumulation Enable bit : TxCONbits.TGATE
			void gate_enable(bool val_){T9CONbits.TGATE=static_cast<unsigned char>(val_);}
			bool gate_enable()const{return static_cast<bool>(T9CONbits.TGATE);}
			//Interrupt Flag : IFSxbits.I2CxMIF
			void interrupt_flag(bool val_){XC32_TIMER9_IF=static_cast<unsigned char>(val_);}
			bool interrupt_flag()const {return static_cast<bool>(XC32_TIMER9_IF);}
			//interrupt enable bit : IECxbits.I2CxMIE
			void interrupt_enable(bool val_){XC32_TIMER9_IE=static_cast<unsigned char>(val_);}
			bool interrupt_enable()const{return static_cast<bool>(XC32_TIMER9_IE);}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_priority_level(unsigned char val_){XC32_TIMER9_IP=val_;}
			unsigned char interrupt_priority_level(){return XC32_TIMER9_IP;}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_sub_priority_level(unsigned char val_){XC32_TIMER9_IS=val_;}
			unsigned char interrupt_sub_priority_level(){return XC32_TIMER9_IS;}
			//Timer ON bit : TxCONbits.ON
			void enable(bool val_){T9CONbits.ON=static_cast<unsigned char>(val_);}
			bool enable()const{return static_cast<bool>(T9CONbits.ON);}
			//Prescaler bits : TxCONbits.TCKPS,
			void prescaler(type_prescaler::div val_){T9CONbits.TCKPS=static_cast<unsigned char>(val_);}
			type_prescaler::div prescaler()const{return static_cast<type_prescaler::div >(T9CONbits.TCKPS);}
			//period register : PRx
			void period(unsigned int val_){PR9=val_;}
			unsigned int period()const{return PR9;}
			//timer count register : TMRx
			void count(unsigned int val_){TMR9=val_;}
			unsigned int count()const {return TMR9;}
			//control register : TxCON
			void reset_all_config(){
				T9CON &= 0x00010000;			//ONˆÈŠO‚ð0‚ÅƒtƒBƒ‹

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
