#ifndef XC32LIB_SFR_TIMER5_INC
#define XC32LIB_SFR_TIMER5_INC 100
#
/*=====timer5=====*/
#include"device_include.h"
#include"exclusive_mixin.hpp"
#include"sfr_register_mixin.hpp"
#include"interrupt.hpp"
#include"timer_base.hpp"

#if defined(XC32LIB_PIC32MX)
#	define XC32LIB_TIMER5_IRQ 20
#	define XC32LIB_TIMER5_VEC 20
#	define XC32LIB_TIMER5_IF IFS0bits.T5IF
#	define XC32LIB_TIMER5_IE IEC0bits.T5IE
#	define XC32LIB_TIMER5_IP IPC5bits.T5IP
#	define XC32LIB_TIMER5_IS IPC5bits.T5IS
#elif defined(XC32LIB_PIC32MZ)
#	define XC32LIB_TIMER5_IRQ 24
#	define XC32LIB_TIMER5_VEC _TIMER_5_VECTOR
#	define XC32LIB_TIMER5_IF IFS0bits.T5IF
#	define XC32LIB_TIMER5_IE IEC0bits.T5IE
#	define XC32LIB_TIMER5_IP IPC6bits.T5IP
#	define XC32LIB_TIMER5_IS IPC6bits.T5IS
#else
#	error Unknown device!
#endif

#ifndef XC32LIB_SFR_TIMER5_EXPLICITINTERRUPT
#	ifndef XC32LIB_DEBUGMODE
#		define x_xc32_sfr_timer5_interrupt(void) __ISR(XC32LIB_TIMER5_VEC, XC32LIB_TIMER5_IPL_FOR_ISR) T5Interrupt(void)//*/func(void)
#	else
extern "C"{void x_xc32_sfr_timer5_interrupt(void); }
#	endif
#else
#	ifndef XC32LIB_DEBUGMODE
#		define xc32_sfr_timer5_interrupt(void) __ISR(XC32LIB_TIMER5_VEC, XC32LIB_TIMER5_IPL_FOR_ISR) T5Interrupt(void)//*/func(void)
#	else
extern "C"{void xc32_sfr_timer5_interrupt(void); }
#	endif
#endif

namespace xc32{
	namespace sfr{
		struct timer5:public sfr_register_mixin<timer5>, public exclusive_mixin<timer5>{
			static unsigned int timer_no(){ return 5; }
			typedef timer::normal_prescaler type_prescaler;
		public:
			//Timer clock source select bit : TxCONbits.TCS  0:Internal ,1:external
			void clock_select(bool val_){T5CONbits.TCS=static_cast<unsigned char>(val_);}
			bool clock_select()const{return static_cast<bool>(T5CONbits.TCS);}
			//Timer Gated Time Accumulation Enable bit : TxCONbits.TGATE
			void gate_enable(bool val_){T5CONbits.TGATE=static_cast<unsigned char>(val_);}
			bool gate_enable()const{return static_cast<bool>(T5CONbits.TGATE);}
			//Interrupt Flag : IFSxbits.I2CxMIF
			void interrupt_flag(bool val_){XC32LIB_TIMER5_IF=static_cast<unsigned char>(val_);}
			bool interrupt_flag()const {return static_cast<bool>(XC32LIB_TIMER5_IF);}
			//interrupt enable bit : IECxbits.I2CxMIE
			void interrupt_enable(bool val_){XC32LIB_TIMER5_IE=static_cast<unsigned char>(val_);}
			bool interrupt_enable()const{return static_cast<bool>(XC32LIB_TIMER5_IE);}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_priority_level(unsigned char val_){XC32LIB_TIMER5_IP=val_;}
			unsigned char interrupt_priority_level(){return XC32LIB_TIMER5_IP;}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_sub_priority_level(unsigned char val_){XC32LIB_TIMER5_IS=val_;}
			unsigned char interrupt_sub_priority_level(){return XC32LIB_TIMER5_IS;}
			//Timer ON bit : TxCONbits.ON
			void enable(bool val_){T5CONbits.ON=static_cast<unsigned char>(val_);}
			bool enable()const{return static_cast<bool>(T5CONbits.ON);}
			//Prescaler bits : TxCONbits.TCKPS,
			void prescaler(type_prescaler::div val_){T5CONbits.TCKPS=static_cast<unsigned char>(val_);}
			type_prescaler::div prescaler()const{return static_cast<type_prescaler::div >(T5CONbits.TCKPS);}
			//period register : PRx
			void period(unsigned int val_){PR5=val_;}
			unsigned int period()const{return PR5;}
			//timer count register : TMRx
			void count(unsigned int val_){TMR5=val_;}
			unsigned int count()const {return TMR5;}
			//control register : TxCON
			void reset_all_config(){
				T5CON &= 0x00010000;			//ONˆÈŠO‚ð0‚ÅƒtƒBƒ‹

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
