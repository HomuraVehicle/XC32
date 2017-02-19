#ifndef XC32_SFR_SPI3_INC
#define XC32_SFR_SPI3_INC 100
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
#	define XC32_SPI3_RX_IRQ 27
#	define XC32_SPI3_RX_VEC 24
#	define XC32_SPI3_RXIF IFS0bits.SPI3RXIF
#	define XC32_SPI3_RXIE IEC0bits.SPI3RXIE
#	define XC32_SPI3_TXIF IFS0bits.SPI3TXIF
#	define XC32_SPI3_TXIE IEC0bits.SPI3TXIE
#	define XC32_SPI3_IP IPC6bits.SPI3IP
#	define XC32_SPI3_IS IPC6bits.SPI3IS
#elif defined(XC32_PIC32MZ)
#	define XC32_SPI3_RX_IRQ 155
#	define XC32_SPI3_RX_VEC _SPI3_RX_VECTOR
#	define XC32_SPI3_RXIF IFS4bits.SPI3RXIF
#	define XC32_SPI3_RXIE IEC4bits.SPI3RXIE
#	define XC32_SPI3_TXIF IFS4bits.SPI3TXIF
#	define XC32_SPI3_TXIE IEC4bits.SPI3TXIE
#	define XC32_SPI3_IP IPC38bits.SPI3RXIP
#	define XC32_SPI3_IS IPC38bits.SPI3RXIS
#else
#	error Unknown device!
#endif

#ifndef XC32_SFR_SPI3_EXPLICITINTERRUPT
#	ifndef XC32_DEBUGMODE
#		define x_xc32_sfr_spi3_interrupt(void) __ISR(XC32_SPI3_RX_VEC, XC32_SPI3_RX_IPL_FOR_ISR) SPI3Interrupt(void)//*/func(void)
#	else
extern "C"{void x_xc32_sfr_spi3_interrupt(void); }
#	endif
#else
#	ifndef XC32_DEBUGMODE
#		define xc32_sfr_spi3_interrupt(void) __ISR(XC32_SPI3_RX_VEC, XC32_SPI3_RX_IPL_FOR_ISR) SPI3Interrupt(void)//*/func(void)
#	else
extern "C"{void xc32_sfr_spi3_interrupt(void); }
#	endif
#endif

namespace xc32{
	namespace sfr{
		struct spi3:public sfr_register_mixin<spi3>, public exclusive_mixin<spi3>{
			static unsigned int spi_no(){ return 3; }
		public:
			//Clock Polarity Select bit : SPIxCONbits.CKP (1:H to L,0:L to H)
			void clock_polarity(bool val_){SPI3CONbits.CKP=static_cast<unsigned char>(val_);}
			//Master Mode Enable bit : SPIxCONbits.MSTEN (1:Master,0:Slave)
			void master_mode(bool val_){SPI3CONbits.MSTEN=static_cast<unsigned char>(val_);}
			//Slave Select Enable bit : SPIxCONbits.SSEN (1:used for SS,0:used for port function)
			void slave_select_enable(bool val_){SPI3CONbits.SSEN=static_cast<unsigned char>(val_);}
			//Receive Overflow Flag bit : SPIxSTATbits.SPIROV
			void receive_overflow(bool val_){SPI3STATbits.SPIROV=static_cast<unsigned char>(val_);}
			bool receive_overflow()const {return static_cast<bool>(SPI3STATbits.SPIROV);}
			//SPI Peripheral On bit : SPIxCONbits.ON
			void enable(bool val_){SPI3CONbits.ON=static_cast<unsigned char>(val_);}
			bool enable()const{return static_cast<bool>(SPI3CONbits.ON);}
			//SPI Buffer Register : SPIxBUF
			void buffer(unsigned char val_){SPI3BUF=val_;}
			unsigned char buffer(){return static_cast<unsigned char>(SPI3BUF);}
			//SPI Receive Buffer Full Status bit : SPIxSTATbits.SPIRBF
			bool receive_buf_full()const {return static_cast<bool>(SPI3STATbits.SPIRBF);}
			//SPI Baud Rate Ragister : SPIxBRG
			/*
				F_SCK = F_PB/(2*(BRG + 1))
				F_SCK：SPIのMasterのクロックスピード
				F_PB ：システム側クロック PLL後
			*/
			void baud_rate_register(unsigned int val_){SPI3BRG=val_;}
			//Control register : SPIxCON
			void reset_all_config(){
				SPI3CON &= 0x00010000;			//ON以外を0でフィル
				rx_interrupt_enable(false);
				rx_interrupt_flag(false);
				tx_interrupt_enable(false);
				tx_interrupt_flag(false);

				tx_interrupt_function(0);
				rx_interrupt_function(0);
			}
			//SPI Receive data available interrupt enable bit : IECxbits.SPIxRXIE
			void rx_interrupt_enable(bool val_){XC32_SPI3_TXIE=static_cast<unsigned char>(val_);}
			bool rx_interrupt_enable()const{return static_cast<bool>(XC32_SPI3_RXIE);}
			//SPI Receive data available interrupt flag bit : IFSxbits.SPIxRXIF
			void rx_interrupt_flag(bool val_){XC32_SPI3_RXIF=static_cast<unsigned char>(val_);}
			bool rx_interrupt_flag()const {return static_cast<bool>(XC32_SPI3_RXIF);}
			//SPI Transnit Buffer Empty interrupt enable bit : IECxbits.SPIxTXIE
			void tx_interrupt_enable(bool val_){XC32_SPI3_TXIE=static_cast<unsigned char>(val_);}
			bool tx_interrupt_enable()const{return static_cast<bool>(XC32_SPI3_TXIE);}
			//SPI Transmit Buffer Empty interrupt flag bit : IFSxbits.SPIxTXIF
			void tx_interrupt_flag(bool val_){XC32_SPI3_TXIF=static_cast<unsigned char>(val_);}
			bool tx_interrupt_flag()const {return static_cast<bool>(XC32_SPI3_TXIF);}
			//Interrupt priority level : IPCxbits.SPIxIP
			void interrupt_priority_level(unsigned char val_){XC32_SPI3_IP=val_;}
			unsigned char interrupt_priority_level(){return XC32_SPI3_IP;}
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_sub_priority_level(unsigned char val_){XC32_SPI3_IS=val_;}
			unsigned char interrupt_sub_priority_level(){return XC32_SPI3_IS;}
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
