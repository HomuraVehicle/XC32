#ifndef XC32_SFR_TIMER1_INC
#define XC32_SFR_TIMER1_INC 100
#
/*=====timer1=====*/
#include"device_include.h"
#include"exclusive_mixin.hpp"
#include"sfr_register_mixin.hpp"
#include"interrupt.hpp"
#include"timer_base.hpp"

#if defined(XC32_PIC32MX)
#	define XC32_TIMER1_IRQ 4
#	define XC32_TIMER1_VEC 4
#	define XC32_TIMER1_IF IFS0bits.T1IF
#	define XC32_TIMER1_IE IEC0bits.T1IE
#	define XC32_TIMER1_IP IPC1bits.T1IP
#	define XC32_TIMER1_IS IPC1bits.T1IS
#elif defined(XC32_PIC32MZ)
#	define XC32_TIMER1_IRQ 4
#	define XC32_TIMER1_VEC _TIMER_1_VECTOR
#	define XC32_TIMER1_IF IFS0bits.T1IF
#	define XC32_TIMER1_IE IEC0bits.T1IE
#	define XC32_TIMER1_IP IPC1bits.T1IP
#	define XC32_TIMER1_IS IPC1bits.T1IS
#else
#	error Unknown device!
#endif

#ifndef XC32_SFR_TIMER1_EXPLICITINTERRUPT
#	ifndef XC32_DEBUGMODE
#		define x_xc32_sfr_timer1_interrupt(void) __ISR(XC32_TIMER1_VEC, XC32_TIMER1_IPL_FOR_ISR) T1Interrupt(void)//*/func(void)
#	else
extern "C"{void x_xc32_sfr_timer1_interrupt(void); }
#	endif
#else
#	ifndef XC32_DEBUGMODE
#		define xc32_sfr_timer1_interrupt(void) __ISR(XC32_TIMER1_VEC, XC32_TIMER1_IPL_FOR_ISR) T1Interrupt(void)//*/func(void)
#	else
extern "C"{void xc32_sfr_timer1_interrupt(void); }
#	endif
#endif

namespace xc32{
	namespace sfr{
		struct timer1:public sfr_register_mixin<timer1>, public exclusive_mixin<timer1>{
			static unsigned int timer_no(){ return 1; }
			typedef timer::timer1_prescaler type_prescaler;
		public:
			//Timer clock source select bit : TxCONbits.TCS  0:Internal ,1:external
			void clock_select(bool val_){T1CONbits.TCS=static_cast<unsigned char>(val_);}
			bool clock_select()const{return static_cast<bool>(T1CONbits.TCS);}
			//Timer Gated Time Accumulation Enable bit : TxCONbits.TGATE
			void gate_enable(bool val_){T1CONbits.TGATE=static_cast<unsigned char>(val_);}
			bool gate_enable()const{return static_cast<bool>(T1CONbits.TGATE);}
			//Interrupt Flag : IFSxbits.I2CxMIF
			void interrupt_flag(bool val_){XC32_TIMER1_IF=static_cast<unsigned char>(val_);}
			bool interrupt_flag()const {return static_cast<bool>(XC32_TIMER1_IF);}
			//interrupt enable bit : IECxbits.I2CxMIE
			void interrupt_enable(bool val_){XC32_TIMER1_IE=static_cast<unsigned char>(val_);}
			bool interrupt_enable()const{return static_cast<bool>(XC32_TIMER1_IE);}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_priority_level(unsigned char val_){XC32_TIMER1_IP=val_;}
			unsigned char interrupt_priority_level(){return XC32_TIMER1_IP;}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_sub_priority_level(unsigned char val_){XC32_TIMER1_IS=val_;}
			unsigned char interrupt_sub_priority_level(){return XC32_TIMER1_IS;}
			//Timer ON bit : TxCONbits.ON
			void enable(bool val_){T1CONbits.ON=static_cast<unsigned char>(val_);}
			bool enable()const{return static_cast<bool>(T1CONbits.ON);}
			//Prescaler bits : TxCONbits.TCKPS,
//			void prescaler(timer::prescaler::div val_){T1CONbits.TCKPS=static_cast<unsigned char>(val_);}
			void prescaler(type_prescaler::div val_) { T1CONbits.TCKPS = static_cast<unsigned char>(val_); }
			type_prescaler::div prescaler()const { return static_cast<type_prescaler::div >(T1CONbits.TCKPS); }
			//period register : PRx
			void period(unsigned int val_){PR1=val_;}
			unsigned int period()const{return PR1;}
			//timer count register : TMRx
			void count(unsigned int val_){TMR1=val_;}
			unsigned int count()const {return TMR1;}
			//control register : TxCON
			void reset_all_config(){
				T1CON &= 0x00010000;			//ON以外を0でフィル

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
