#ifndef XC32LIB_SFR_TIMER2_INC
#define XC32LIB_SFR_TIMER2_INC 100
#
/*=====timer2=====*/
#include<XCBase/type_traits.hpp>
#include"device_include.h"
#include"exclusive_mixin.hpp"
#include"sfr_register_mixin.hpp"
#include"interrupt.hpp"
#include"timer_base.hpp"
#include"timer3.hpp"

#if defined(XC32LIB_PIC32MX)
#	define XC32LIB_TIMER2_IRQ 8
#	define XC32LIB_TIMER2_VEC 8
#	define XC32LIB_TIMER2_IF IFS0bits.T2IF
#	define XC32LIB_TIMER2_IE IEC0bits.T2IE
#	define XC32LIB_TIMER2_IP IPC2bits.T2IP
#	define XC32LIB_TIMER2_IS IPC2bits.T2IS
#elif defined(XC32LIB_PIC32MZ)
#	define XC32LIB_TIMER2_IRQ 9
#	define XC32LIB_TIMER2_VEC _TIMER_2_VECTOR
#	define XC32LIB_TIMER2_IF IFS0bits.T2IF
#	define XC32LIB_TIMER2_IE IEC0bits.T2IE
#	define XC32LIB_TIMER2_IP IPC2bits.T2IP
#	define XC32LIB_TIMER2_IS IPC2bits.T2IS
#else
#	error Unknown device!
#endif

#ifndef XC32LIB_SFR_TIMER2_EXPLICITINTERRUPT
#	ifndef XC32LIB_DEBUGMODE
#		define x_xc32_sfr_timer2_interrupt(void) __ISR(XC32LIB_TIMER2_VEC, XC32LIB_TIMER2_IPL_FOR_ISR) T2Interrupt(void)//*/func(void)
#	else
extern "C"{void x_xc32_sfr_timer2_interrupt(void); }
#	endif
#else
#	ifndef XC32LIB_DEBUGMODE
#		define xc32_sfr_timer2_interrupt(void) __ISR(XC32LIB_TIMER2_VEC, XC32LIB_TIMER2_IPL_FOR_ISR) T2Interrupt(void)//*/func(void)
#	else
extern "C"{void xc32_sfr_timer2_interrupt(void); }
#	endif
#endif

namespace xc32{
	using namespace xc;
	namespace sfr{
		struct timer2:public sfr_register_mixin<timer2>, public exclusive_mixin<timer2>{
			static unsigned int timer_no(){ return 2; }
			typedef timer::normal_prescaler type_prescaler;
		public:
			//Timer clock source select bit : TxCONbits.TCS  0:Internal ,1:external
			void clock_select(bool val_){T2CONbits.TCS=static_cast<unsigned char>(val_);}
			bool clock_select()const{return static_cast<bool>(T2CONbits.TCS);}
			//Timer Gated Time Accumulation Enable bit : TxCONbits.TGATE
			void gate_enable(bool val_){T2CONbits.TGATE=static_cast<unsigned char>(val_);}
			bool gate_enable()const{return static_cast<bool>(T2CONbits.TGATE);}
			//Interrupt Flag : IFSxbits.I2CxMIF
			void interrupt_flag(bool val_){XC32LIB_TIMER2_IF=static_cast<unsigned char>(val_);}
			bool interrupt_flag()const {return static_cast<bool>(XC32LIB_TIMER2_IF);}
			//interrupt enable bit : IECxbits.I2CxMIE
			void interrupt_enable(bool val_){XC32LIB_TIMER2_IE=static_cast<unsigned char>(val_);}
			bool interrupt_enable()const{return static_cast<bool>(XC32LIB_TIMER2_IE);}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_priority_level(unsigned char val_){XC32LIB_TIMER2_IP=val_;}
			unsigned char interrupt_priority_level(){return XC32LIB_TIMER2_IP;}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_sub_priority_level(unsigned char val_){XC32LIB_TIMER2_IS=val_;}
			unsigned char interrupt_sub_priority_level(){return XC32LIB_TIMER2_IS;}
			//Timer ON bit : TxCONbits.ON
			void enable(bool val_){T2CONbits.ON=static_cast<unsigned char>(val_);}
			bool enable()const{return static_cast<bool>(T2CONbits.ON);}
			//Prescaler bits : TxCONbits.TCKPS,
			void prescaler(type_prescaler::div val_) { T2CONbits.TCKPS = static_cast<unsigned char>(val_); }
			type_prescaler::div prescaler()const { return static_cast<type_prescaler::div >(T2CONbits.TCKPS); }
			//period register : PRx
			void period(unsigned int val_){PR2=val_;}
			unsigned int period()const{return PR2;}
			//timer count register : TMRx
			void count(unsigned int val_){TMR2=val_;}
			unsigned int count()const {return TMR2;}
			//32-Bit Timer Mode Select bit : TxCONbits.T32
			void enable_32bit(bool val_){T2CONbits.T32=static_cast<unsigned char>(val_);}
			bool enable_32bit()const{return static_cast<bool>(T2CONbits.T32);}
			//control register : TxCON
			void reset_all_config(){
				T2CON &= 0x00010000;			//ONˆÈŠO‚ð0‚ÅƒtƒBƒ‹

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
			struct is_valid_combination<sfr::timer2, sfr::timer3> :public xc::true_type{ typedef xc::true_type type; };
		}
	}
}

#
#endif
