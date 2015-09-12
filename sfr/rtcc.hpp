#ifndef XC32_SFR_RTCC_INC
#define XC32_SFR_RTCC_INC 100
#
//====================RTCC====================
#include <XC32_config.hpp>
#include "device_include.h"
#include "interrupt.hpp"
#include "exclusive_mixin.hpp"
#include "sfr_register_mixin.hpp"

#if defined(XC32_PIC32MX)
#	define XC32_RTCC_IRQ 42
#	define XC32_RTCC_VEC 32
#	define XC32_RTCC_IF IFS1bits.RTCCIF
#	define XC32_RTCC_IE IEC1bits.RTCCIE
#	define XC32_RTCC_IP IPC8bits.RTCCIP
#	define XC32_RTCC_IS IPC8bits.RTCCIS
#elif defined(XC32_PIC32MZ)
#	define XC32_RTCC_IRQ 166
#	define XC32_RTCC_VEC _RTCC_VECTOR
#	define XC32_RTCC_IF IFS5bits.RTCCIF
#	define XC32_RTCC_IE IEC5bits.RTCCIE
#	define XC32_RTCC_IP IPC41bits.RTCCIP
#	define XC32_RTCC_IS IPC41bits.RTCCIS
#else
#	error Unknown device!
#endif

#ifndef XC32_SFR_RTCC_EXPLICITINTERRUPT
#	ifndef XC32_DEBUGMODE
#		define x_xc32_sfr_rtcc_interrupt(void) __ISR(XC32_RTCC_VEC, IPL7AUTO) RTCCInterrupt(void)//*/func(void)
#	else
extern "C"{void x_xc32_sfr_rtcc_interrupt(void); }
#	endif
#else
#	ifndef XC32_DEBUGMODE
#		define xc32_sfr_rtcc_interrupt(void) __ISR(XC32_RTCC_VEC, IPL7AUTO) RTCCInterrupt(void)//*/func(void)
#	else
extern "C"{void xc32_sfr_rtcc_interrupt(void); }
#	endif
#endif

namespace xc32{
	namespace sfr{
		struct rtcc:public sfr_register_mixin<rtcc>, public exclusive_mixin<rtcc>{
			//RTC Value Registers Write Enable bit : RTCCONbits.RTCWREN
			void write_enable(bool val_){RTCCONbits.RTCWREN=static_cast<unsigned char>(val_);}
			//RTCC module enbele bit : RTCCONbits.ON
			void enable(bool val_){RTCCONbits.ON=static_cast<unsigned char>(val_);}
			bool enable()const{return static_cast<bool>(RTCCONbits.ON);}
			//RTCC Value Registers Read Synchronization bit : RTCCONbits.RTCSYNC
			bool can_access()const{return (!static_cast<bool>(RTCCONbits.RTCSYNC));}
			//Alarm enable bit : RTCALRMbits.ALRMEN
			void alarm_enable(bool val_){RTCALRMbits.ALRMEN=static_cast<unsigned char>(val_);}
			bool alarm_enable()const{return static_cast<bool>(RTCALRMbits.ALRMEN);}
			//Chime enable bit : RTCALRMbits.CHIME
			void alarm_chime_enable(bool val_){RTCALRMbits.CHIME=static_cast<unsigned char>(val_);}
			//Alarm mask configuration bit : RTCALRMbits.AMASK
			void alarm_mask(unsigned char val_){RTCALRMbits.AMASK=val_;} 
			//Alarm repeat counter value bits : RTCALRMbits.ARPT
			void alarm_repeat_counter(unsigned char val_){RTCALRMbits.ARPT=val_;}
			unsigned char alarm_repeat_counter()const{return RTCALRMbits.ARPT;}
			//RTCC output enable bit : RTCCONbits.RTCOE
			void clock_output_enable(bool val_){RTCCONbits.RTCOE=static_cast<unsigned char>(val_);}
			//RTC calibration bits : RTCCONbits.CAL
			void calibration(unsigned int val_){RTCCONbits.CAL=val_;}
			//RTC time value register : RTCTIME
			void time(unsigned long val_){RTCTIME=val_;}
			unsigned long time()const{return RTCTIME;}
			//RTC date value register : RTCDATE
			void date(unsigned long val_){RTCDATE=val_;}
			unsigned long date()const{return RTCDATE;}
			//Alarm time value register : ALRMTIME
			void alarm_time(unsigned long val_){ALRMTIME=val_;}
			unsigned long alarm_time()const{return ALRMTIME;}
			//Alarm date value register : ALRMDATE
			void alarm_date(unsigned long val_){ALRMDATE=val_;}
			unsigned long alarm_date()const{return ALRMDATE;}
			//RTCC interrupt enable bit : IEC1bits.RTCCIE
			void interrupt_enable(bool val_){XC32_RTCC_IE=static_cast<unsigned char>(val_);}
			bool interrupt_enable()const{return static_cast<bool>(XC32_RTCC_IE);}
			//RTCC interrupt flag : IFS1bits.RTCCIF
			void interrupt_flag(bool val_){XC32_RTCC_IF=static_cast<unsigned char>(val_);}
			bool interrupt_flag()const{return static_cast<bool>(XC32_RTCC_IF);}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_priority_level(unsigned char val_){XC32_RTCC_IP=val_;}
			unsigned char interrupt_priority_level(){return XC32_RTCC_IP;}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_sub_priority_level(unsigned char val_){XC32_RTCC_IS=val_;}
			unsigned char interrupt_sub_priority_level(){return XC32_RTCC_IS;}
			//Control Register : I2CxCON
			void reset_all_config(){
				RTCCON &= 0x00010000;			//ONˆÈŠO‚ð0‚ÅƒtƒBƒ‹

				interrupt_enable(false);
				interrupt_flag(false);

				interrupt_function(0);
			}
		private:
			static interrupt::function* interrupt_ptr;
		public:
			const interrupt::function* interrupt_function()const{return interrupt_ptr;}
			void interrupt_function(interrupt::function* ptr_) { interrupt_ptr=ptr_; }

		};
	}
}

#
#endif
