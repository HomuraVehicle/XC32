#ifndef XC32LIB_SFR_UART6_INC
#define XC32LIB_SFR_UART6_INC 101
#
/*=== uart6 ===
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

#if defined(XC32LIB_PIC32MX)
#	define XC32LIB_UART6_TX_IRQ 72
#	define XC32LIB_UART6_RX_IRQ 71
#	define XC32LIB_UART6_VEC 50
#	define XC32LIB_UART6_TX_IF IFS2bits.U6TXIF
#	define XC32LIB_UART6_TX_IE IEC2bits.U6TXIE
#	define XC32LIB_UART6_TX_IP IPC12bits.U6IP
#	define XC32LIB_UART6_TX_IS IPC12bits.U6IS
#	define XC32LIB_UART6_RX_IF IFS2bits.U6RXIF
#	define XC32LIB_UART6_RX_IE IEC2bits.U6RXIE
#	define XC32LIB_UART6_RX_IP IPC12bits.U6IP
#	define XC32LIB_UART6_RX_IS IPC12bits.U6IS
#elif defined(XC32LIB_PIC32MZ)
#	define XC32LIB_UART6_TX_IRQ 190
#	define XC32LIB_UART6_TX_VEC _UART6_TX_VECTOR
#	define XC32LIB_UART6_TX_IF IFS5bits.U6TXIF
#	define XC32LIB_UART6_TX_IE IEC5bits.U6TXIE
#	define XC32LIB_UART6_TX_IP IPC47bits.U6TXIP
#	define XC32LIB_UART6_TX_IS IPC47bits.U6TXIS
#	define XC32LIB_UART6_RX_IRQ 189
#	define XC32LIB_UART6_RX_VEC _UART6_RX_VECTOR
#	define XC32LIB_UART6_RX_IF IFS5bits.U6RXIF
#	define XC32LIB_UART6_RX_IE IEC5bits.U6RXIE
#	define XC32LIB_UART6_RX_IP IPC47bits.U6RXIP
#	define XC32LIB_UART6_RX_IS IPC47bits.U6RXIS
#else
#	error Unknown device!
#endif

#if defined(XC32LIB_PIC32MX)
#	ifndef XC32LIB_SFR_UART6_EXPLICITINTERRUPT
#		ifndef XC32LIB_DEBUGMODE
#			define x_xc32_sfr_uart6_interrupt(void) __ISR(XC32LIB_UART6_VEC, IPL7AUTO) U6Interrupt(void)//*/func(void)
#		else
extern "C"{void x_xc32_sfr_uart6_interrupt(void); }
#		endif
#	else
#		ifndef XC32LIB_DEBUGMODE
#			define xc32_sfr_uart6_interrupt(void) __ISR(XC32LIB_UART6_VEC, IPL7AUTO) U6Interrupt(void)//*/func(void)
#		else
extern "C"{void xc32_sfr_uart6_interrupt(void); }
#		endif
#	endif
#elif defined(XC32LIB_PIC32MZ)
#	ifndef XC32LIB_SFR_UART6_EXPLICITINTERRUPT
#		ifndef XC32LIB_DEBUGMODE
#			define x_xc32_sfr_uart6_tx_interrupt(void) __ISR(XC32LIB_UART6_TX_VEC, XC32LIB_UART6_TX_IPL_FOR_ISR) U6TXInterrupt(void)//*/func(void)
#			define x_xc32_sfr_uart6_rx_interrupt(void) __ISR(XC32LIB_UART6_RX_VEC, XC32LIB_UART6_RX_IPL_FOR_ISR) U6RXInterrupt(void)//*/func(void)
#		else
extern "C"{void x_xc32_sfr_uart6_tx_interrupt(void); void x_xc32_sfr_uart6_rx_interrupt(void); }
#		endif
#	else
#		ifndef XC32LIB_DEBUGMODE
#			define xc32_sfr_uart6_tx_interrupt(void) __ISR(XC32LIB_UART6_TX_VEC, XC32LIB_UART6_TX_IPL_FOR_ISR) U6TXInterrupt(void)//*/func(void)
#			define xc32_sfr_uart6_rx_interrupt(void) __ISR(XC32LIB_UART6_RX_VEC, XC32LIB_UART6_RX_IPL_FOR_ISR) U6RXInterrupt(void)//*/func(void)
#		else
extern "C"{void xc32_sfr_uart6_tx_interrupt(void); void xc32_sfr_uart6_rx_interrupt(void); }
#		endif
#	endif
#else
#	error Unknown device!
#endif

namespace xc32{
	namespace sfr{
		struct uart6:public sfr_register_mixin<uart6>, public exclusive_mixin<uart6>{
			static unsigned int uart_no(){ return 1; }
		public:
			//Receive Interrupt Enable bit : IECxbits.UxRXIE
			void rx_interrupt_enable(bool val_){XC32LIB_UART6_RX_IE=static_cast<unsigned char>(val_);}
			bool rx_interrupt_enable()const{return static_cast<bool>(XC32LIB_UART6_RX_IE);}
			//Receive Interrupt Flag bit : IFSxbits.UxRXIF
			void rx_interrupt_flag(bool val_){XC32LIB_UART6_RX_IF=static_cast<unsigned char>(val_);}
			bool rx_interrupt_flag()const {return static_cast<bool>(XC32LIB_UART6_RX_IF);}
			//Interrupt priority level : IPCxbits.UxIP
			void rx_interrupt_priority_level(unsigned char val_){XC32LIB_UART6_RX_IP=val_;}
			unsigned char rx_interrupt_priority_level(){return XC32LIB_UART6_RX_IP;}
			//Interrupt priority level : IPCxbits.UxIP
			void rx_interrupt_sub_priority_level(unsigned char val_){XC32LIB_UART6_RX_IS=val_;}
			unsigned char rx_interrupt_sub_priority_level(){return XC32LIB_UART6_RX_IS;}
			//Transmit Interrupt Enable bit : IECxbits.UxTXIE
			void tx_interrupt_enable(bool val_){XC32LIB_UART6_TX_IE=static_cast<unsigned char>(val_);}
			bool tx_interrupt_enable()const{return static_cast<bool>(XC32LIB_UART6_TX_IE);}
			//Transmit Interrupt Flag : IFSxbits.UxTXIF
			void tx_interrupt_flag(bool val_){XC32LIB_UART6_TX_IF=static_cast<unsigned char>(val_);}
			bool tx_interrupt_flag()const {return static_cast<bool>(XC32LIB_UART6_TX_IF);}
			//Interrupt priority level : IPCxbits.UxIP
			void tx_interrupt_priority_level(unsigned char val_){XC32LIB_UART6_TX_IP=val_;}
			unsigned char tx_interrupt_priority_level(){return XC32LIB_UART6_TX_IP;}
			//Interrupt priority level : IPCxbits.UxIP
			void tx_interrupt_sub_priority_level(unsigned char val_){XC32LIB_UART6_TX_IS=val_;}
			unsigned char tx_interrupt_sub_priority_level(){return XC32LIB_UART6_TX_IS;}
			//Receive Buffer Data Available bit : UxSTATbits.URXDA
			bool rx_buf_full()const {return static_cast<bool>(U6STAbits.URXDA);}
			//Receive Register : UxRXREG
			unsigned char rx_buf_get(){return static_cast<unsigned char>(U6RXREG);}
			//Receive Buffer Overrun Error Status bit : UxSTAbits.OERR
			void rx_buf_overflow(bool val_){U6STAbits.OERR=static_cast<unsigned char>(val_);}
			bool rx_buf_overflow()const {return static_cast<bool>(U6STAbits.OERR);}
			//Transmit Buffer Full Status bit : UxSTAbits.UTXBF
			bool tx_buf_full()const {return static_cast<bool>(U6STAbits.UTXBF);}
			//Transmit Register : UxTXREG
			void tx_buf_set(unsigned char val_){U6TXREG=val_;}
			//UART enable bit : UxMODEbits.ON
			void enable(bool val_){U6MODEbits.ON=static_cast<unsigned char>(val_);}
			bool enable()const{return static_cast<bool>(U6MODEbits.ON);}
			//Transmit enable bit : UxSTAbits.UTXEN
			void tx_enable(bool val_){U6STAbits.UTXEN=static_cast<unsigned char>(val_);}
			bool tx_enable()const{return static_cast<bool>(U6STAbits.UTXEN);}
			//Receiver Enable bit : UxSTAbits.URXEN
			void rx_enable(bool val_){U6STAbits.URXEN=static_cast<unsigned char>(val_);}
			bool rx_enable()const{return static_cast<bool>(U6STAbits.URXEN);}
			//Baud Rate Register : UxBRG
			void baud_rate_register(unsigned int val_){U6BRG=val_;}
			//Transmit Interrupt Mode Selection bits : UxSTAbits.UTXISEL1,UxSTAbits.UTXISEL0
			void tx_interrupt_mode(uart::tx_interrupt_mode::mode mode_) {
				U6STAbits.UTXISEL0=static_cast<bool>(mode_&0x01);
				U6STAbits.UTXISEL1=static_cast<bool>((mode_&0x02)!=0x00);
			}
			//Receive Interrupt Mode Selection bit : UxSTAbits.URXISEL
			void rx_interrupt_mode(uart::rx_interrupt_mode::mode mode_) {
				U6STAbits.URXISEL0=static_cast<bool>(mode_&0x01);
				U6STAbits.URXISEL1=static_cast<bool>((mode_&0x02)!=0x00);
			}
			//Flow Control bits : UxMODEbits.UEN
			void flow_control(uart::flowcontrol::mode mode_){U6MODEbits.UEN=(0x03 &  mode_);}
			//Reset all confige about UART
			void reset_all_config(){
				//UART MODE bits : UxMODE
				U6MODE &= 0x00010000;			//ON以外を0でフィル
				//UART Status and control bits : UxSTA
				U6STA=0;
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
