#ifndef XC32_SFR_SPI1_INC
#define XC32_SFR_SPI1_INC 100
#
//*********** SPI関連関数 ***********************
//SPIの初期設定を行った後、書き込んで、読み取って関数を使う
// 選択していないPINは highで保持しておく必要がある 
//
#include"device_include.h"
#include"exclusive_mixin.hpp"
#include"sfr_register_mixin.hpp"
#include"interrupt.hpp"

#if defined(XC32_PIC32MX)
#	define XC32_SPI1_RX_IRQ 24
#	define XC32_SPI1_RX_VEC 23
#	define XC32_SPI1_RXIF IFS0bits.SPI1RXIF
#	define XC32_SPI1_RXIE IEC0bits.SPI1RXIE
#	define XC32_SPI1_TXIF IFS0bits.SPI1TXIF
#	define XC32_SPI1_TXIE IEC0bits.SPI1TXIE
#	define XC32_SPI1_IP IPC5bits.SPI1IP
#	define XC32_SPI1_IS IPC5bits.SPI1IS
#elif defined(XC32_PIC32MZ)
#	define XC32_SPI1_RX_IRQ 110
#	define XC32_SPI1_RX_VEC _SPI1_RX_VECTOR
#	define XC32_SPI1_RXIF IFS3bits.SPI1RXIF
#	define XC32_SPI1_RXIE IEC3bits.SPI1RXIE
#	define XC32_SPI1_TXIF IFS3bits.SPI1TXIF
#	define XC32_SPI1_TXIE IEC3bits.SPI1TXIE
#	define XC32_SPI1_IP IPC27bits.SPI1RXIP
#	define XC32_SPI1_IS IPC27bits.SPI1RXIS
#else
#	error Unknown device!
#endif

#ifndef XC32_SFR_SPI1_EXPLICITINTERRUPT
#	ifndef XC32_DEBUGMODE
#		define x_xc32_sfr_spi1_interrupt(void) __ISR(XC32_SPI1_RX_VEC, XC32_SPI1_RX_IPL_FOR_ISR) SPI1RXInterrupt(void)//*/func(void)
#	else
extern "C"{void x_xc32_sfr_spi1_interrupt(void); }
#	endif
#else
#	ifndef XC32_DEBUGMODE
#		define xc32_sfr_spi1_interrupt(void) __ISR(XC32_SPI1_RX_VEC, XC32_SPI1_RX_IPL_FOR_ISR) SPI1RXInterrupt(void)//*/func(void)
#	else
extern "C"{void xc32_sfr_spi1_interrupt(void); }
#	endif
#endif

namespace xc32{
	namespace sfr{
		struct spi1:public sfr_register_mixin<spi1>, public exclusive_mixin<spi1>{
			static unsigned int spi_no(){ return 1; }
		public:
			//Clock Polarity Select bit : SPIxCONbits.CKP (1:H to L,0:L to H)
			void clock_polarity(bool val_){SPI1CONbits.CKP=static_cast<unsigned char>(val_);}
			//Master Mode Enable bit : SPIxCONbits.MSTEN (1:Master,0:Slave)
			void master_mode(bool val_){SPI1CONbits.MSTEN=static_cast<unsigned char>(val_);}
			//Slave Select Enable bit : SPIxCONbits.SSEN (1:used for SS,0:used for port function)
			void slave_select_enable(bool val_){SPI1CONbits.SSEN=static_cast<unsigned char>(val_);}
			//Receive Overflow Flag bit : SPIxSTATbits.SPIROV
			void receive_overflow(bool val_){SPI1STATbits.SPIROV=static_cast<unsigned char>(val_);}
			bool receive_overflow()const {return static_cast<bool>(SPI1STATbits.SPIROV);}
			//SPI Peripheral On bit : SPIxCONbits.ON
			void enable(bool val_){SPI1CONbits.ON=static_cast<unsigned char>(val_);}
			bool enable()const {return static_cast<bool>(SPI1CONbits.ON);}
			//SPI Buffer Register : SPIxBUF
			void buffer(unsigned char val_){SPI1BUF=val_;}
			unsigned char buffer(){return static_cast<unsigned char>(SPI1BUF);}
			//SPI Receive Buffer Full Status bit : SPIxSTATbits.SPIRBF
			bool receive_buf_full()const {return static_cast<bool>(SPI1STATbits.SPIRBF);}
			//SPI Baud Rate Ragister : SPIxBRG
			/*
				F_SCK = F_PB/(2*(BRG + 1))
				F_SCK：SPIのMasterのクロックスピード
				F_PB ：システム側クロック PLL後
			*/
			void baud_rate_register(unsigned int val_){SPI1BRG=val_;}
			//Control register : SPIxCON
			void reset_all_config(){
				SPI1CON &= 0x00010000;			//ON以外を0でフィル
				rx_interrupt_enable(false);
				rx_interrupt_flag(false);
				tx_interrupt_enable(false);
				tx_interrupt_flag(false);

				tx_interrupt_function(0);
				rx_interrupt_function(0);
			}
			//SPI Receive data available interrupt enable bit : IECxbits.SPIxRXIE
			void rx_interrupt_enable(bool val_){XC32_SPI1_TXIE=static_cast<unsigned char>(val_);}
			bool rx_interrupt_enable()const{return static_cast<bool>(XC32_SPI1_RXIE);}
			//SPI Receive data available interrupt flag bit : IFSxbits.SPIxRXIF
			void rx_interrupt_flag(bool val_){XC32_SPI1_RXIF=static_cast<unsigned char>(val_);}
			bool rx_interrupt_flag()const {return static_cast<bool>(XC32_SPI1_RXIF);}
			//SPI Transnit Buffer Empty interrupt enable bit : IECxbits.SPIxTXIE
			void tx_interrupt_enable(bool val_){XC32_SPI1_TXIE=static_cast<unsigned char>(val_);}
			bool tx_interrupt_enable()const{return static_cast<bool>(XC32_SPI1_TXIE);}
			//SPI Transmit Buffer Empty interrupt flag bit : IFSxbits.SPIxTXIF
			void tx_interrupt_flag(bool val_){XC32_SPI1_TXIF=static_cast<unsigned char>(val_);}
			bool tx_interrupt_flag()const {return static_cast<bool>(XC32_SPI1_TXIF);}
			//Interrupt priority level : IPCxbits.SPIxIP
			void interrupt_priority_level(unsigned char val_){XC32_SPI1_IP=val_;}
			unsigned char interrupt_priority_level(){return XC32_SPI1_IP;}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_sub_priority_level(unsigned char val_){XC32_SPI1_IS=val_;}
			unsigned char interrupt_sub_priority_level(){return XC32_SPI1_IS;}
		private:
			static interrupt::function* tx_interrupt_ptr;
			static interrupt::function* rx_interrupt_ptr;
		public:
			const interrupt::function* tx_interrupt_function()const{return tx_interrupt_ptr;}
			void tx_interrupt_function(interrupt::function* ptr_) { tx_interrupt_ptr=ptr_; }
			const interrupt::function* rx_interrupt_function()const{return rx_interrupt_ptr;}
			void rx_interrupt_function(interrupt::function* ptr_) { rx_interrupt_ptr=ptr_; }
		public:
			static const unsigned char rx_ipl;
		};
	}
}
#
#endif
