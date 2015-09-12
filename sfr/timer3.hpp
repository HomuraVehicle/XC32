#ifndef XC32_SFR_TIMER3_INC
#define XC32_SFR_TIMER3_INC 100
#
/*=====timer3=====*/
#include"device_include.h"
#include"exclusive_mixin.hpp"
#include"sfr_register_mixin.hpp"
#include"interrupt.hpp"
#include"timer_base.hpp"

#if defined(XC32_PIC32MX)
#	define XC32_TIMER3_IRQ 12
#	define XC32_TIMER3_VEC 12
#	define XC32_TIMER3_IF IFS0bits.T3IF
#	define XC32_TIMER3_IE IEC0bits.T3IE
#	define XC32_TIMER3_IP IPC3bits.T3IP
#	define XC32_TIMER3_IS IPC3bits.T3IS
#elif defined(XC32_PIC32MZ)
#	define XC32_TIMER3_IRQ 14
#	define XC32_TIMER3_VEC _TIMER_3_VECTOR
#	define XC32_TIMER3_IF IFS0bits.T3IF
#	define XC32_TIMER3_IE IEC0bits.T3IE
#	define XC32_TIMER3_IP IPC3bits.T3IP
#	define XC32_TIMER3_IS IPC3bits.T3IS
#else
#	error Unknown device!
#endif

#ifndef XC32_SFR_TIMER3_EXPLICITINTERRUPT
#	ifndef XC32_DEBUGMODE
#		define x_xc32_sfr_timer3_interrupt(void) __ISR(XC32_TIMER3_VEC, XC32_TIMER3_IPL_FOR_ISR) T3Interrupt(void)//*/func(void)
#	else
extern "C"{void x_xc32_sfr_timer3_interrupt(void); }
#	endif
#else
#	ifndef XC32_DEBUGMODE
#		define xc32_sfr_timer3_interrupt(void) __ISR(XC32_TIMER3_VEC, XC32_TIMER3_IPL_FOR_ISR) T3Interrupt(void)//*/func(void)
#	else
extern "C"{void xc32_sfr_timer3_interrupt(void); }
#	endif
#endif

namespace xc32{
	namespace sfr{
		struct timer3:public sfr_register_mixin<timer3>, public exclusive_mixin<timer3>{
			static unsigned int timer_no(){ return 3; }
			typedef timer::normal_prescaler type_prescaler;
		public:
			//Timer clock source select bit : TxCONbits.TCS  0:Internal ,1:external
			void clock_select(bool val_){T3CONbits.TCS=static_cast<unsigned char>(val_);}
			bool clock_select()const{return static_cast<bool>(T3CONbits.TCS);}
			//Timer Gated Time Accumulation Enable bit : TxCONbits.TGATE
			void gate_enable(bool val_){T3CONbits.TGATE=static_cast<unsigned char>(val_);}
			bool gate_enable()const{return static_cast<bool>(T3CONbits.TGATE);}
			//Interrupt Flag : IFSxbits.I2CxMIF
			void interrupt_flag(bool val_){XC32_TIMER3_IF=static_cast<unsigned char>(val_);}
			bool interrupt_flag()const {return static_cast<bool>(XC32_TIMER3_IF);}
			//interrupt enable bit : IECxbits.I2CxMIE
			void interrupt_enable(bool val_){XC32_TIMER3_IE=static_cast<unsigned char>(val_);}
			bool interrupt_enable()const{return static_cast<bool>(XC32_TIMER3_IE);}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_priority_level(unsigned char val_){XC32_TIMER3_IP=val_;}
			unsigned char interrupt_priority_level(){return XC32_TIMER3_IP;}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_sub_priority_level(unsigned char val_){XC32_TIMER3_IS=val_;}
			unsigned char interrupt_sub_priority_level(){return XC32_TIMER3_IS;}
			//Timer ON bit : TxCONbits.ON
			void enable(bool val_){T3CONbits.ON=static_cast<unsigned char>(val_);}
			bool enable()const{return static_cast<bool>(T3CONbits.ON);}
			//Prescaler bits : TxCONbits.TCKPS,
			void prescaler(type_prescaler::div val_) { T3CONbits.TCKPS = static_cast<unsigned char>(val_); }
			type_prescaler::div prescaler()const { return static_cast<type_prescaler::div >(T3CONbits.TCKPS); }
			//period register : PRx
			void period(unsigned int val_){PR3=val_;}
			unsigned int period()const{return PR3;}
			//timer count register : TMRx
			void count(unsigned int val_){TMR3=val_;}
			unsigned int count()const {return TMR3;}
			//control register : TxCON
			void reset_all_config(){
				T3CON &= 0x00010000;			//ONˆÈŠO‚ð0‚ÅƒtƒBƒ‹

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
