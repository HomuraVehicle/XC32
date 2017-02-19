#ifndef XC32_SFR_UART1_INC
#define XC32_SFR_UART1_INC 101
#
/*=== uart1 ===
新型割り込み関数名に変更

v1_01/140630 hmIto
	関数群のconst/を整理
	変更基準は、
		const : レジスタの内容が処理によって変更されないことが保障できるか？
		 : レジスタの内容がPic自身によって自動的に変更され得るか？
*/
#include"device_include.h"
#include"exclusive_mixin.hpp"
#include"sfr_register_mixin.hpp"
#include"interrupt.hpp"
#include"uart_base.hpp"

#if defined(XC32_PIC32MX)
#	define XC32_UART1_TX_IRQ 28
#	define XC32_UART1_RX_IRQ 27
#	define XC32_UART1_VEC 24
#	define XC32_UART1_TX_IF IFS0bits.U1TXIF
#	define XC32_UART1_TX_IE IEC0bits.U1TXIE
#	define XC32_UART1_TX_IP IPC6bits.U1IP
#	define XC32_UART1_TX_IS IPC6bits.U1IS
#	define XC32_UART1_RX_IF IFS0bits.U1RXIF
#	define XC32_UART1_RX_IE IEC0bits.U1RXIE
#	define XC32_UART1_RX_IP IPC6bits.U1IP
#	define XC32_UART1_RX_IS IPC6bits.U1IS
#elif defined(XC32_PIC32MZ)
#	define XC32_UART1_TX_IRQ 114
#	define XC32_UART1_TX_VEC _UART1_TX_VECTOR
#	define XC32_UART1_TX_IF IFS3bits.U1TXIF
#	define XC32_UART1_TX_IE IEC3bits.U1TXIE
#	define XC32_UART1_TX_IP IPC28bits.U1TXIP
#	define XC32_UART1_TX_IS IPC28bits.U1TXIS
#	define XC32_UART1_RX_IRQ 113
#	define XC32_UART1_RX_VEC _UART1_RX_VECTOR
#	define XC32_UART1_RX_IF IFS3bits.U1RXIF
#	define XC32_UART1_RX_IE IEC3bits.U1RXIE
#	define XC32_UART1_RX_IP IPC28bits.U1RXIP
#	define XC32_UART1_RX_IS IPC28bits.U1RXIS
#else
#	error Unknown device!
#endif

#if defined(XC32_PIC32MX)
#	ifndef XC32_SFR_UART1_EXPLICITINTERRUPT
#		ifndef XC32_DEBUGMODE
#			define x_xc32_sfr_uart1_interrupt(void) __ISR(XC32_UART1_VEC, IPL7AUTO) U1Interrupt(void)//*/func(void)
#		else
extern "C"{void x_xc32_sfr_uart1_interrupt(void); }
#		endif
#	else
#		ifndef XC32_DEBUGMODE
#			define xc32_sfr_uart1_interrupt(void) __ISR(XC32_UART1_VEC, IPL7AUTO) U1Interrupt(void)//*/func(void)
#		else
extern "C"{void xc32_sfr_uart1_interrupt(void); }
#		endif
#	endif
#elif defined(XC32_PIC32MZ)
#	ifndef XC32_SFR_UART1_EXPLICITINTERRUPT
#		ifndef XC32_DEBUGMODE
#			define x_xc32_sfr_uart1_tx_interrupt(void) __ISR(XC32_UART1_TX_VEC, XC32_UART1_TX_IPL_FOR_ISR) U1TXInterrupt(void)//*/func(void)
#			define x_xc32_sfr_uart1_rx_interrupt(void) __ISR(XC32_UART1_RX_VEC, XC32_UART1_RX_IPL_FOR_ISR) U1RXInterrupt(void)//*/func(void)
#		else
extern "C"{void x_xc32_sfr_uart1_tx_interrupt(void); void x_xc32_sfr_uart1_rx_interrupt(void); }
#		endif
#	else
#		ifndef XC32_DEBUGMODE
#			define xc32_sfr_uart1_tx_interrupt(void) __ISR(XC32_UART1_TX_VEC, XC32_UART1_TX_IPL_FOR_ISR) U1TXInterrupt(void)//*/func(void)
#			define xc32_sfr_uart1_rx_interrupt(void) __ISR(XC32_UART1_RX_VEC, XC32_UART1_RX_IPL_FOR_ISR) U1RXInterrupt(void)//*/func(void)
#		else
extern "C"{void xc32_sfr_uart1_tx_interrupt(void); void xc32_sfr_uart1_rx_interrupt(void); }
#		endif
#	endif
#else
#	error Unknown device!
#endif

namespace xc32{
	namespace sfr{
		struct uart1:public sfr_register_mixin<uart1>, public exclusive_mixin<uart1>{
			static unsigned int uart_no(){ return 1; }
		public:
			//Receive Interrupt Enable bit : IECxbits.UxRXIE
			void rx_interrupt_enable(bool val_){XC32_UART1_RX_IE=static_cast<unsigned char>(val_);}
			bool rx_interrupt_enable()const{return static_cast<bool>(XC32_UART1_RX_IE);}
			//Receive Interrupt Flag bit : IFSxbits.UxRXIF
			void rx_interrupt_flag(bool val_){XC32_UART1_RX_IF=static_cast<unsigned char>(val_);}
			bool rx_interrupt_flag()const {return static_cast<bool>(XC32_UART1_RX_IF);}
			//Interrupt priority level : IPCxbits.UxIP
			void rx_interrupt_priority_level(unsigned char val_){XC32_UART1_RX_IP=val_;}
			unsigned char rx_interrupt_priority_level(){return XC32_UART1_RX_IP;}
			//Interrupt priority level : IPCxbits.UxIP
			void rx_interrupt_sub_priority_level(unsigned char val_){XC32_UART1_RX_IS=val_;}
			unsigned char rx_interrupt_sub_priority_level(){return XC32_UART1_RX_IS;}
			//Transmit Interrupt Enable bit : IECxbits.UxTXIE
			void tx_interrupt_enable(bool val_){XC32_UART1_TX_IE=static_cast<unsigned char>(val_);}
			bool tx_interrupt_enable()const{return static_cast<bool>(XC32_UART1_TX_IE);}
			//Transmit Interrupt Flag : IFSxbits.UxTXIF
			void tx_interrupt_flag(bool val_){XC32_UART1_TX_IF=static_cast<unsigned char>(val_);}
			bool tx_interrupt_flag()const {return static_cast<bool>(XC32_UART1_TX_IF);}
			//Interrupt priority level : IPCxbits.UxIP
			void tx_interrupt_priority_level(unsigned char val_){XC32_UART1_TX_IP=val_;}
			unsigned char tx_interrupt_priority_level(){return XC32_UART1_TX_IP;}
			//Interrupt priority level : IPCxbits.UxIP
			void tx_interrupt_sub_priority_level(unsigned char val_){XC32_UART1_TX_IS=val_;}
			unsigned char tx_interrupt_sub_priority_level(){return XC32_UART1_TX_IS;}
			//Receive Buffer Data Available bit : UxSTATbits.URXDA
			bool rx_buf_full()const {return static_cast<bool>(U1STAbits.URXDA);}
			//Receive Register : UxRXREG
			unsigned char rx_buf_get(){return static_cast<unsigned char>(U1RXREG);}
			//Receive Buffer Overrun Error Status bit : UxSTAbits.OERR
			void rx_buf_overflow(bool val_){U1STAbits.OERR=static_cast<unsigned char>(val_);}
			bool rx_buf_overflow()const {return static_cast<bool>(U1STAbits.OERR);}
			//Transmit Buffer Full Status bit : UxSTAbits.UTXBF
			bool tx_buf_full()const {return static_cast<bool>(U1STAbits.UTXBF);}
			//Transmit Register : UxTXREG
			void tx_buf_set(unsigned char val_){U1TXREG=val_;}
			//UART enable bit : UxMODEbits.ON
			void enable(bool val_){U1MODEbits.ON=static_cast<unsigned char>(val_);}
			bool enable()const{return static_cast<bool>(U1MODEbits.ON);}
			//Transmit enable bit : UxSTAbits.UTXEN
			void tx_enable(bool val_){U1STAbits.UTXEN=static_cast<unsigned char>(val_);}
			bool tx_enable()const{return static_cast<bool>(U1STAbits.UTXEN);}
			//Receiver Enable bit : UxSTAbits.URXEN
			void rx_enable(bool val_){U1STAbits.URXEN=static_cast<unsigned char>(val_);}
			bool rx_enable()const{return static_cast<bool>(U1STAbits.URXEN);}
			//Baud Rate Register : UxBRG
			void baud_rate_register(unsigned int val_){U1BRG=val_;}
			//Transmit Interrupt Mode Selection bits : UxSTAbits.UTXISEL1,UxSTAbits.UTXISEL0
			void tx_interrupt_mode(uart::tx_interrupt_mode::mode mode_) {
				U1STAbits.UTXISEL0=static_cast<bool>(mode_&0x01);
				U1STAbits.UTXISEL1=static_cast<bool>((mode_&0x02)!=0x00);
			}
			//Receive Interrupt Mode Selection bit : UxSTAbits.URXISEL
			void rx_interrupt_mode(uart::rx_interrupt_mode::mode mode_) {
				U1STAbits.URXISEL0=static_cast<bool>(mode_&0x01);
				U1STAbits.URXISEL1=static_cast<bool>((mode_&0x02)!=0x00);
			}
			//Flow Control bits : UxMODEbits.UEN
			void flow_control(uart::flowcontrol::mode mode_){U1MODEbits.UEN=(0x03 &  mode_);}
			//Reset all confige about UART
			void reset_all_config(){
				//UART MODE bits : UxMODE
				U1MODE &= 0x00010000;			//ON以外を0でフィル

				//UART Status and control bits : UxSTA
				U1STA=0;
				//Interrupt Reset
				rx_interrupt_enable(false);
				rx_interrupt_flag(false);
				tx_interrupt_enable(false);
				tx_interrupt_flag(false);
				rx_interrupt_function(0);
				tx_interrupt_function(0);
			}
		private:
			static interrupt::function* tx_interrupt_ptr;
			static interrupt::function* rx_interrupt_ptr;
		public:
			const interrupt::function* tx_interrupt_function()const{return tx_interrupt_ptr;}
			void tx_interrupt_function(interrupt::function* ptr_) { tx_interrupt_ptr=ptr_; }
			const interrupt::function* rx_interrupt_function()const{return rx_interrupt_ptr;}
			void rx_interrupt_function(interrupt::function* ptr_){rx_interrupt_ptr=ptr_;}
		public:
			static const unsigned char tx_ipl;
			static const unsigned char rx_ipl;
		};
	}
}

#
#endif
