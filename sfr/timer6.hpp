#ifndef XC32_SFR_TIMER6_INC
#define XC32_SFR_TIMER6_INC 100
#
/*=====timer6=====*/
#include<XCBase/type_traits.hpp>
#include"device_include.h"
#include"exclusive_mixin.hpp"
#include"sfr_register_mixin.hpp"
#include"interrupt.hpp"
#include"timer_base.hpp"
#include"timer7.hpp"

#if defined(XC32_PIC32MX)
#elif defined(XC32_PIC32MZ)
#	define XC32_TIMER6_IRQ 28
#	define XC32_TIMER6_VEC _TIMER_6_VECTOR
#	define XC32_TIMER6_IF IFS0bits.T6IF
#	define XC32_TIMER6_IE IEC0bits.T6IE
#	define XC32_TIMER6_IP IPC7bits.T6IP
#	define XC32_TIMER6_IS IPC7bits.T6IS
#else
#	error Unknown device!
#endif

#ifndef XC32_SFR_TIMER6_EXPLICITINTERRUPT
#	ifndef XC32_DEBUGMODE
#		define x_xc32_sfr_timer6_interrupt(void) __ISR(XC32_TIMER6_VEC, XC32_TIMER6_IPL_FOR_ISR) T6Interrupt(void)//*/func(void)
#	else
extern "C"{void x_xc32_sfr_timer6_interrupt(void); }
#	endif
#else
#	ifndef XC32_DEBUGMODE
#		define xc32_sfr_timer6_interrupt(void) __ISR(XC32_TIMER6_VEC, XC32_TIMER6_IPL_FOR_ISR) T6Interrupt(void)//*/func(void)
#	else
extern "C"{void xc32_sfr_timer6_interrupt(void); }
#	endif
#endif

namespace xc32{
	namespace sfr{
		struct timer6:public sfr_register_mixin<timer6>, public exclusive_mixin<timer6>{
			static unsigned int timer_no(){ return 6; }
			typedef timer::normal_prescaler type_prescaler;
		public:
			//Timer clock source select bit : TxCONbits.TCS  0:Internal ,1:external
			void clock_select(bool val_){T6CONbits.TCS=static_cast<unsigned char>(val_);}
			bool clock_select()const{return static_cast<bool>(T6CONbits.TCS);}
			//Timer Gated Time Accumulation Enable bit : TxCONbits.TGATE
			void gate_enable(bool val_){T6CONbits.TGATE=static_cast<unsigned char>(val_);}
			bool gate_enable()const{return static_cast<bool>(T6CONbits.TGATE);}
			//Interrupt Flag : IFSxbits.I2CxMIF
			void interrupt_flag(bool val_){XC32_TIMER6_IF=static_cast<unsigned char>(val_);}
			bool interrupt_flag()const {return static_cast<bool>(XC32_TIMER6_IF);}
			//interrupt enable bit : IECxbits.I2CxMIE
			void interrupt_enable(bool val_){XC32_TIMER6_IE=static_cast<unsigned char>(val_);}
			bool interrupt_enable()const{return static_cast<bool>(XC32_TIMER6_IE);}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_priority_level(unsigned char val_){XC32_TIMER6_IP=val_;}
			unsigned char interrupt_priority_level(){return XC32_TIMER6_IP;}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_sub_priority_level(unsigned char val_){XC32_TIMER6_IS=val_;}
			unsigned char interrupt_sub_priority_level(){return XC32_TIMER6_IS;}
			//Timer ON bit : TxCONbits.ON
			void enable(bool val_){T6CONbits.ON=static_cast<unsigned char>(val_);}
			bool enable()const{return static_cast<bool>(T6CONbits.ON);}
			//Prescaler bits : TxCONbits.TCKPS,
			void prescaler(type_prescaler::div val_){T6CONbits.TCKPS=static_cast<unsigned char>(val_);}
			type_prescaler::div prescaler()const{return static_cast<type_prescaler::div >(T6CONbits.TCKPS);}
			//period register : PRx
			void period(unsigned int val_){PR6=val_;}
			unsigned int period()const{return PR6;}
			//timer count register : TMRx
			void count(unsigned int val_){TMR6=val_;}
			unsigned int count()const {return TMR6;}
			//32-Bit Timer Mode Select bit : TxCONbits.T32
			void enable_32bit(bool val_){T6CONbits.T32=static_cast<unsigned char>(val_);}
			bool enable_32bit()const{return static_cast<bool>(T6CONbits.T32);}
			//control register : TxCON
			void reset_all_config(){
				T6CON &= 0x00010000;			//ON以外を0でフィル

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
		namespace timer {
			template<>
			struct is_valid_combination<sfr::timer6, sfr::timer7> :public xc::true_type{ typedef xc::true_type type; };
		}
	}
}

#
#endif
