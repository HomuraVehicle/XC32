#ifndef XC32LIB_SFR_I2C2_INC
#define XC32LIB_SFR_I2C2_INC 100
#
#include<XC32Lib_config.hpp>
#include"device_include.h"
#include"interrupt.hpp"
#include"exclusive_mixin.hpp"
#include"sfr_register_mixin.hpp"

#if defined(XC32LIB_PIC32MX)
#	define XC32LIB_I2C2_IRQ 45
#	define XC32LIB_I2C2_VEC 33
#	define XC32LIB_I2C2_IF IFS1bits.I2C2MIF
#	define XC32LIB_I2C2_IE IEC1bits.I2C2MIE
#	define XC32LIB_I2C2_IP IPC8bits.I2C2MIP
#	define XC32LIB_I2C2_IS IPC8bits.I2C2MIS
#elif defined(XC32LIB_PIC32MZ)
#	define XC32LIB_I2C2_IRQ 150
#	define XC32LIB_I2C2_VEC _I2C2_MASTER_VECTOR
#	define XC32LIB_I2C2_IF IFS4bits.I2C2MIF
#	define XC32LIB_I2C2_IE IEC4bits.I2C2MIE
#	define XC32LIB_I2C2_IP IPC37bits.I2C2MIP
#	define XC32LIB_I2C2_IS IPC37bits.I2C2MIS
#else
#	error Unknown device!
#endif

#ifndef XC32LIB_SFR_I2C2_EXPLICITINTERRUPT
#	ifndef XC32LIB_DEBUGMODE
#		define x_xc32_sfr_i2c2_interrupt(void) __ISR(XC32LIB_I2C2_VEC, XC32LIB_I2C2_IPL_FOR_ISR) I2C2Interrupt(void)//*/func(void)
#	else
extern "C"{void x_xc32_sfr_i2c2_interrupt(void); }
#	endif
#else
#	ifndef XC32LIB_DEBUGMODE
#		define xc32_sfr_i2c2_interrupt(void) __ISR(XC32LIB_I2C2_VEC, XC32LIB_I2C2_IPL_FOR_ISR) I2C2Interrupt(void)//*/func(void)
#	else
extern "C"{void xc32_sfr_i2c2_interrupt(void); }
#	endif
#endif

namespace xc32{
	namespace sfr{
		struct i2c2:public sfr_register_mixin<i2c2>, public exclusive_mixin<i2c2>{
			static unsigned int i2c_no(){ return 2; }
		public:
			//Start Condition Enable bit : I2CxCONbits.SEN
			void start_enable(bool val_){I2C2CONbits.SEN=static_cast<unsigned char>(val_);}
			bool start_enable()const{return static_cast<bool>(I2C2CONbits.SEN);}
			//Restart Condition Enable bit : I2CxCONbits.RSEN
			void restart_enable(bool val_){I2C2CONbits.RSEN=static_cast<unsigned char>(val_);}
			bool restart_enable()const{return static_cast<bool>(I2C2CONbits.RSEN);}
			//Stop Condition bit : I2CxCONbits.PEN
			void stop_enable(bool val_){I2C2CONbits.PEN=static_cast<unsigned char>(val_);}
			bool stop_enable()const{return static_cast<bool>(I2C2CONbits.PEN);}
			//Receive Enable bit : I2CxCONbits.RCEN
			void receive_enable(bool val_){I2C2CONbits.RCEN=static_cast<unsigned char>(val_);}
			bool receive_enable()const{return static_cast<bool>(I2C2CONbits.RCEN);}
			//ACK Sequence Enable bit : I2CxCONbits.ACKEN
			void ack_enable(bool val_){I2C2CONbits.ACKEN=static_cast<unsigned char>(val_);}
			bool ack_enable()const{return static_cast<bool>(I2C2CONbits.ACKEN);}
			//ACK Data bit : I2CxCONbits.ACKDT
			void ack_data(bool val_){I2C2CONbits.ACKDT=static_cast<unsigned char>(val_);}
			//Master Interrupt Flag : IFSxbits.I2CxMIF
			void interrupt_flag(bool val_){XC32LIB_I2C2_IF=static_cast<unsigned char>(val_);}
			bool interrupt_flag()const {return static_cast<bool>(XC32LIB_I2C2_IF);}
			//interrupt enable bit : IECxbits.I2CxMIE
			void interrupt_enable(bool val_){XC32LIB_I2C2_IE=static_cast<unsigned char>(val_);}
			bool interrupt_enable()const{return static_cast<bool>(XC32LIB_I2C2_IE);}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_priority_level(unsigned char val_){XC32LIB_I2C2_IP=val_;}
			unsigned char interrupt_priority_level(){return XC32LIB_I2C2_IP;}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_sub_priority_level(unsigned char val_){XC32LIB_I2C2_IS=val_;}
			unsigned char interrupt_sub_priority_level(){return XC32LIB_I2C2_IS;}
			//Receive Data Register : I2CxRCV
			unsigned char receive_data(){return static_cast<unsigned char>(I2C2RCV);}
			//Transmit Data Register : I2CxTRN
			void transmit_data(unsigned char val_){I2C2TRN=val_;}
			//ACK Status bti : I2CxSTATbits.ACKSTAT(0:ACK was received,1:ACK was not received)
			bool ack_status()const {return static_cast<bool>(I2C2STATbits.ACKSTAT);}
			//Receive Buffer Full Status bit : I2CxSTATbits.RBF
			bool receive_buf_full()const {static_cast<bool>(I2C2STATbits.RBF);}
			//Transmit Buffer Full Status bit : I2CxSTATbits.TBF
			bool transmit_buf_full()const{return static_cast<bool>(I2C2STATbits.TBF);}

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
			void baud_rate_register(unsigned long val_){I2C2BRG=val_;}
			//I2C Enable bit : I2CxCONbits.ON
			void enable(bool val_){I2C2CONbits.ON=static_cast<unsigned char>(val_);}
			bool enable()const{return static_cast<bool>(I2C2CONbits.ON);}
			//I2C Control Register : I2CxCON
			void reset_all_config(){
				I2C2CON &= 0x00010000;			//ON以外を0でフィル

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
