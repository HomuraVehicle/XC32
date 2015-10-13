#ifndef XC32_SFR_I2C3_INC
#define XC32_SFR_I2C3_INC 100
#
#include<XC32_config.hpp>
#include"device_include.h"
#include"interrupt.hpp"
#include"exclusive_mixin.hpp"
#include"sfr_register_mixin.hpp"

#if defined(XC32_PIC32MX)
#	define XC32_I2C3_IRQ 28
#	define XC32_I2C3_VEC 24
#	define XC32_I2C3_IF IFS0bits.I2C3MIF
#	define XC32_I2C3_IE IEC0bits.I2C3MIE
#	define XC32_I2C3_IP IPC6bits.I2C3MIP
#	define XC32_I2C3_IS IPC6bits.I2C3MIS
#elif defined(XC32_PIC32MZ)
#	define XC32_I2C3_IRQ 162
#	define XC32_I2C3_VEC _I2C3_MASTER_VECTOR
#	define XC32_I2C3_IF IFS5bits.I2C3MIF
#	define XC32_I2C3_IE IEC5bits.I2C3MIE
#	define XC32_I2C3_IP IPC40bits.I2C3MIP
#	define XC32_I2C3_IS IPC40bits.I2C3MIS
#else
#	error Unknown device!
#endif

#ifndef XC32_SFR_I2C3_EXPLICITINTERRUPT
#	ifndef XC32_DEBUGMODE
#		define x_xc32_sfr_i2c3_interrupt(void) __ISR(XC32_I2C3_VEC, XC32_I2C3_IPL_FOR_ISR) I2C3Interrupt(void)//*/func(void)
#	else
extern "C"{void x_xc32_sfr_i2c3_interrupt(void); }
#	endif
#else
#	ifndef XC32_DEBUGMODE
#		define xc32_sfr_i2c3_interrupt(void) __ISR(XC32_I2C3_VEC, XC32_I2C3_IPL_FOR_ISR) I2C3Interrupt(void)//*/func(void)
#	else
extern "C"{void xc32_sfr_i2c3_interrupt(void); }
#	endif
#endif

namespace xc32{
	namespace sfr{
		struct i2c3:public sfr_register_mixin<i2c3>,public exclusive_mixin<i2c3>{
			static unsigned int i2c_no(){ return 3; }
		public:
			//Start Condition Enable bit : I2CxCONbits.SEN
			void start_enable(bool val_){I2C3CONbits.SEN=static_cast<unsigned char>(val_);}
			bool start_enable()const{return static_cast<bool>(I2C3CONbits.SEN);}
			//Restart Condition Enable bit : I2CxCONbits.RSEN
			void restart_enable(bool val_){I2C3CONbits.RSEN=static_cast<unsigned char>(val_);}
			bool restart_enable()const{return static_cast<bool>(I2C3CONbits.RSEN);}
			//Stop Condition bit : I2CxCONbits.PEN
			void stop_enable(bool val_){I2C3CONbits.PEN=static_cast<unsigned char>(val_);}
			bool stop_enable()const{return static_cast<bool>(I2C3CONbits.PEN);}
			//Receive Enable bit : I2CxCONbits.RCEN
			void receive_enable(bool val_){I2C3CONbits.RCEN=static_cast<unsigned char>(val_);}
			bool receive_enable()const{return static_cast<bool>(I2C3CONbits.RCEN);}
			//ACK Sequence Enable bit : I2CxCONbits.ACKEN
			void ack_enable(bool val_){I2C3CONbits.ACKEN=static_cast<unsigned char>(val_);}
			bool ack_enable()const{return static_cast<bool>(I2C3CONbits.ACKEN);}
			//ACK Data bit : I2CxCONbits.ACKDT
			void ack_data(bool val_){I2C3CONbits.ACKDT=static_cast<unsigned char>(val_);}
			//Master Interrupt Flag : IFSxbits.I2CxMIF
			void interrupt_flag(bool val_){XC32_I2C3_IF=static_cast<unsigned char>(val_);}
			bool interrupt_flag()const {return static_cast<bool>(XC32_I2C3_IF);}
			//interrupt enable bit : IECxbits.I2CxMIE
			void interrupt_enable(bool val_){XC32_I2C3_IE=static_cast<unsigned char>(val_);}
			bool interrupt_enable()const{return static_cast<bool>(XC32_I2C3_IE);}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_priority_level(unsigned char val_){XC32_I2C3_IP=val_;}
			unsigned char interrupt_priority_level(){return XC32_I2C3_IP;}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_sub_priority_level(unsigned char val_){XC32_I2C3_IS=val_;}
			unsigned char interrupt_sub_priority_level(){return XC32_I2C3_IS;}
			//Receive Data Register : I2CxRCV
			unsigned char receive_data(){return static_cast<unsigned char>(I2C3RCV);}
			//Transmit Data Register : I2CxTRN
			void transmit_data(unsigned char val_){I2C3TRN=val_;}
			//ACK Status bti : I2CxSTATbits.ACKSTAT(0:ACK was received,1:ACK was not received)
			bool ack_status()const {return static_cast<bool>(I2C3STATbits.ACKSTAT);}
			//Receive Buffer Full Status bit : I2CxSTATbits.RBF
			bool receive_buf_full()const {return static_cast<bool>(I2C3STATbits.RBF);}
			//Transmit Buffer Full Status bit : I2CxSTATbits.TBF
			bool transmit_buf_full()const{return static_cast<bool>(I2C3STATbits.TBF);}

			//Boud Rate Generator bits : I2CxBRG (ボーレートからI2Cクロックを生成するための何か設定)
			/*
				BRG= ( 1/(2*FSCL) - PGD ) * PBCLK -2
				FSCL：I2C側のクロックスピード 100k,400k,1Mの3種類が主流らしい
					100k:1.0e-5s=10000ns
					400k:2.5e-6s= 2500ns
					  1M:1.0e-6s= 1000ns
				PGD : Pulse_Gobbler_Delay デバイス固有　データシート参照
					Pic4EP512GU810:1.30e-7
				FCY : システム側のクロック PLL後　ただし，DOZE利用の場合はCPUクロックと一致しない
			*/
			void baud_rate_register(unsigned long val_){I2C3BRG=val_;}
			//I2C Enable bit : I2CxCONbits.ON
			void enable(bool val_){I2C3CONbits.ON=static_cast<unsigned char>(val_);}
			bool enable()const{return static_cast<bool>(I2C3CONbits.ON);}
			//I2C Control Register : I2CxCON
			void reset_all_config(){
				I2C3CON &= 0x00010000;			//ON以外を0でフィル

				interrupt_enable(false);
				interrupt_flag(false);

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
