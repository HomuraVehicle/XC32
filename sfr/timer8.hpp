#ifndef XC32_SFR_TIMER8_INC
#define XC32_SFR_TIMER8_INC 100
#
/*=====timer8=====*/
#include<XCBase/type_traits.hpp>
#include"device_include.h"
#include"exclusive_mixin.hpp"
#include"sfr_register_mixin.hpp"
#include"interrupt.hpp"
#include"timer_base.hpp"
#include"timer9.hpp"

#if defined(XC32_PIC32MX)
#elif defined(XC32_PIC32MZ)
#	define XC32_TIMER8_IRQ 36
#	define XC32_TIMER8_VEC _TIMER_8_VECTOR
#	define XC32_TIMER8_IF IFS1bits.T8IF
#	define XC32_TIMER8_IE IEC1bits.T8IE
#	define XC32_TIMER8_IP IPC9bits.T8IP
#	define XC32_TIMER8_IS IPC9bits.T8IS
#else
#	error Unknown device!
#endif

#ifndef XC32_SFR_TIMER8_EXPLICITINTERRUPT
#	ifndef XC32_DEBUGMODE
#		define x_xc32_sfr_timer8_interrupt(void) __ISR(XC32_TIMER8_VEC, XC32_TIMER8_IPL_FOR_ISR) T8Interrupt(void)//*/func(void)
#	else
extern "C"{void x_xc32_sfr_timer8_interrupt(void); }
#	endif
#else
#	ifndef XC32_DEBUGMODE
#		define xc32_sfr_timer8_interrupt(void) __ISR(XC32_TIMER8_VEC, XC32_TIMER8_IPL_FOR_ISR) T8Interrupt(void)//*/func(void)
#	else
extern "C"{void xc32_sfr_timer8_interrupt(void); }
#	endif
#endif

namespace xc32{
	namespace sfr{
		struct timer8:public sfr_register_mixin<timer8>, public exclusive_mixin<timer8>{
			static unsigned int timer_no(){ return 8; }
			typedef timer::normal_prescaler type_prescaler;
		public:
			//Timer clock source select bit : TxCONbits.TCS  0:Internal ,1:external
			void clock_select(bool val_){T8CONbits.TCS=static_cast<unsigned char>(val_);}
			bool clock_select()const{return static_cast<bool>(T8CONbits.TCS);}
			//Timer Gated Time Accumulation Enable bit : TxCONbits.TGATE
			void gate_enable(bool val_){T8CONbits.TGATE=static_cast<unsigned char>(val_);}
			bool gate_enable()const{return static_cast<bool>(T8CONbits.TGATE);}
			//Interrupt Flag : IFSxbits.I2CxMIF
			void interrupt_flag(bool val_){XC32_TIMER8_IF=static_cast<unsigned char>(val_);}
			bool interrupt_flag()const {return static_cast<bool>(XC32_TIMER8_IF);}
			//interrupt enable bit : IECxbits.I2CxMIE
			void interrupt_enable(bool val_){XC32_TIMER8_IE=static_cast<unsigned char>(val_);}
			bool interrupt_enable()const{return static_cast<bool>(XC32_TIMER8_IE);}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_priority_level(unsigned char val_){XC32_TIMER8_IP=val_;}
			unsigned char interrupt_priority_level(){return XC32_TIMER8_IP;}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_sub_priority_level(unsigned char val_){XC32_TIMER8_IS=val_;}
			unsigned char interrupt_sub_priority_level(){return XC32_TIMER8_IS;}
			//Timer ON bit : TxCONbits.ON
			void enable(bool val_){T8CONbits.ON=static_cast<unsigned char>(val_);}
			bool enable()const{return static_cast<bool>(T8CONbits.ON);}
			//Prescaler bits : TxCONbits.TCKPS,
			void prescaler(type_prescaler::div val_){T8CONbits.TCKPS=static_cast<unsigned char>(val_);}
			type_prescaler::div prescaler()const{return static_cast<type_prescaler::div >(T8CONbits.TCKPS);}
			//period register : PRx
			void period(unsigned int val_){PR8=val_;}
			unsigned int period()const{return PR8;}
			//timer count register : TMRx
			void count(unsigned int val_){TMR8=val_;}
			unsigned int count()const {return TMR8;}
			//32-Bit Timer Mode Select bit : TxCONbits.T32
			void enable_32bit(bool val_){T8CONbits.T32=static_cast<unsigned char>(val_);}
			bool enable_32bit()const{return static_cast<bool>(T8CONbits.T32);}
			//control register : TxCON
			void reset_all_config(){
				T8CON &= 0x00010000;			//ON以外を0でフィル

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
			struct is_valid_combination<sfr::timer8, sfr::timer9> :public xc::true_type{ typedef xc::true_type type; };
		}
	}
}

#
#endif
