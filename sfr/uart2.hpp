#ifndef XC32_SFR_UART2_INC
#define XC32_SFR_UART2_INC 101
#
/*=== uart2 ===
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
#	define XC32_UART2_TX_IRQ 42
#	define XC32_UART2_RX_IRQ 41
#	define XC32_UART2_VEC 32
#	define XC32_UART2_TX_IF IFS1bits.U2TXIF
#	define XC32_UART2_TX_IE IEC1bits.U2TXIE
#	define XC32_UART2_TX_IP IPC8bits.U2IP
#	define XC32_UART2_TX_IS IPC8bits.U2IS
#	define XC32_UART2_RX_IF IFS1bits.U2RXIF
#	define XC32_UART2_RX_IE IEC1bits.U2RXIE
#	define XC32_UART2_RX_IP IPC8bits.U2IP
#	define XC32_UART2_RX_IS IPC8bits.U2IS
#elif defined(XC32_PIC32MZ)
#	define XC32_UART2_TX_IRQ 147
#	define XC32_UART2_TX_VEC _UART2_TX_VECTOR
#	define XC32_UART2_TX_IF IFS4bits.U2TXIF
#	define XC32_UART2_TX_IE IEC4bits.U2TXIE
#	define XC32_UART2_TX_IP IPC36bits.U2TXIP
#	define XC32_UART2_TX_IS IPC36bits.U2TXIS
#	define XC32_UART2_RX_IRQ 146
#	define XC32_UART2_RX_VEC _UART2_RX_VECTOR
#	define XC32_UART2_RX_IF IFS4bits.U2RXIF
#	define XC32_UART2_RX_IE IEC4bits.U2RXIE
#	define XC32_UART2_RX_IP IPC36bits.U2RXIP
#	define XC32_UART2_RX_IS IPC36bits.U2RXIS
#else
#	error Unknown device!
#endif

#if defined(XC32_PIC32MX)
#	ifndef XC32_SFR_UART2_EXPLICITINTERRUPT
#		ifndef XC32_DEBUGMODE
#			define x_xc32_sfr_uart2_interrupt(void) __ISR(XC32_UART2_VEC, IPL7AUTO) U2Interrupt(void)//*/func(void)
#		else
extern "C"{void x_xc32_sfr_uart2_interrupt(void); }
#		endif
#	else
#		ifndef XC32_DEBUGMODE
#			define xc32_sfr_uart2_interrupt(void) __ISR(XC32_UART2_VEC, IPL7AUTO) U2Interrupt(void)//*/func(void)
#		else
extern "C"{void xc32_sfr_uart2_interrupt(void); }
#		endif
#	endif
#elif defined(XC32_PIC32MZ)
#	ifndef XC32_SFR_UART2_EXPLICITINTERRUPT
#		ifndef XC32_DEBUGMODE
#			define x_xc32_sfr_uart2_tx_interrupt(void) __ISR(XC32_UART2_TX_VEC, XC32_UART2_TX_IPL_FOR_ISR) U2TXInterrupt(void)//*/func(void)
#			define x_xc32_sfr_uart2_rx_interrupt(void) __ISR(XC32_UART2_RX_VEC, XC32_UART2_RX_IPL_FOR_ISR) U2RXInterrupt(void)//*/func(void)
#		else
extern "C"{void x_xc32_sfr_uart2_tx_interrupt(void); void x_xc32_sfr_uart2_rx_interrupt(void); }
#		endif
#	else
#		ifndef XC32_DEBUGMODE
#			define xc32_sfr_uart2_tx_interrupt(void) __ISR(XC32_UART2_TX_VEC, XC32_UART2_TX_IPL_FOR_ISR) U2TXInterrupt(void)//*/func(void)
#			define xc32_sfr_uart2_rx_interrupt(void) __ISR(XC32_UART2_RX_VEC, XC32_UART2_RX_IPL_FOR_ISR) U2RXInterrupt(void)//*/func(void)
#		else
extern "C"{void xc32_sfr_uart2_tx_interrupt(void); void xc32_sfr_uart2_rx_interrupt(void); }
#		endif
#	endif
#else
#	error Unknown device!
#endif

namespace xc32{
	namespace sfr{
		struct uart2:public sfr_register_mixin<uart2>, public exclusive_mixin<uart2>{
			static unsigned int uart_no(){ return 1; }
		public:
			//Receive Interrupt Enable bit : IECxbits.UxRXIE
			void rx_interrupt_enable(bool val_){XC32_UART2_RX_IE=static_cast<unsigned char>(val_);}
			bool rx_interrupt_enable()const{return static_cast<bool>(XC32_UART2_RX_IE);}
			//Receive Interrupt Flag bit : IFSxbits.UxRXIF
			void rx_interrupt_flag(bool val_){XC32_UART2_RX_IF=static_cast<unsigned char>(val_);}
			bool rx_interrupt_flag()const {return static_cast<bool>(XC32_UART2_RX_IF);}
			//Interrupt priority level : IPCxbits.UxIP
			void rx_interrupt_priority_level(unsigned char val_){XC32_UART2_RX_IP=val_;}
			unsigned char rx_interrupt_priority_level(){return XC32_UART2_RX_IP;}
			//Interrupt priority level : IPCxbits.UxIP
			void rx_interrupt_sub_priority_level(unsigned char val_){XC32_UART2_RX_IS=val_;}
			unsigned char rx_interrupt_sub_priority_level(){return XC32_UART2_RX_IS;}
			//Transmit Interrupt Enable bit : IECxbits.UxTXIE
			void tx_interrupt_enable(bool val_){XC32_UART2_TX_IE=static_cast<unsigned char>(val_);}
			bool tx_interrupt_enable()const{return static_cast<bool>(XC32_UART2_TX_IE);}
			//Transmit Interrupt Flag : IFSxbits.UxTXIF
			void tx_interrupt_flag(bool val_){XC32_UART2_TX_IF=static_cast<unsigned char>(val_);}
			bool tx_interrupt_flag()const {return static_cast<bool>(XC32_UART2_TX_IF);}
			//Interrupt priority level : IPCxbits.UxIP
			void tx_interrupt_priority_level(unsigned char val_){XC32_UART2_TX_IP=val_;}
			unsigned char tx_interrupt_priority_level(){return XC32_UART2_TX_IP;}
			//Interrupt priority level : IPCxbits.UxIP
			void tx_interrupt_sub_priority_level(unsigned char val_){XC32_UART2_TX_IS=val_;}
			unsigned char tx_interrupt_sub_priority_level(){return XC32_UART2_TX_IS;}
			//Receive Buffer Data Available bit : UxSTATbits.URXDA
			bool rx_buf_full()const {return static_cast<bool>(U2STAbits.URXDA);}
			//Receive Register : UxRXREG
			unsigned char rx_buf_get(){return static_cast<unsigned char>(U2RXREG);}
			//Receive Buffer Overrun Error Status bit : UxSTAbits.OERR
			void rx_buf_overflow(bool val_){U2STAbits.OERR=static_cast<unsigned char>(val_);}
			bool rx_buf_overflow()const {return static_cast<bool>(U2STAbits.OERR);}
			//Transmit Buffer Full Status bit : UxSTAbits.UTXBF
			bool tx_buf_full()const {return static_cast<bool>(U2STAbits.UTXBF);}
			//Transmit Register : UxTXREG
			void tx_buf_set(unsigned char val_){U2TXREG=val_;}
			//UART enable bit : UxMODEbits.ON
			void enable(bool val_){U2MODEbits.ON=static_cast<unsigned char>(val_);}
			bool enable()const{return static_cast<bool>(U2MODEbits.ON);}
			//Transmit enable bit : UxSTAbits.UTXEN
			void tx_enable(bool val_){U2STAbits.UTXEN=static_cast<unsigned char>(val_);}
			bool tx_enable()const{return static_cast<bool>(U2STAbits.UTXEN);}
			//Receiver Enable bit : UxSTAbits.URXEN
			void rx_enable(bool val_){U2STAbits.URXEN=static_cast<unsigned char>(val_);}
			bool rx_enable()const{return static_cast<bool>(U2STAbits.URXEN);}
			//Baud Rate Register : UxBRG
			void baud_rate_register(unsigned int val_){U2BRG=val_;}
			//Transmit Interrupt Mode Selection bits : UxSTAbits.UTXISEL1,UxSTAbits.UTXISEL0
			void tx_interrupt_mode(uart::tx_interrupt_mode::mode mode_) {
				U2STAbits.UTXISEL0=static_cast<bool>(mode_&0x01);
				U2STAbits.UTXISEL1=static_cast<bool>((mode_&0x02)!=0x00);
			}
			//Receive Interrupt Mode Selection bit : UxSTAbits.URXISEL
			void rx_interrupt_mode(uart::rx_interrupt_mode::mode mode_) {
				U2STAbits.URXISEL0=static_cast<bool>(mode_&0x01);
				U2STAbits.URXISEL1=static_cast<bool>((mode_&0x02)!=0x00);
			}
			//Flow Control bits : UxMODEbits.UEN
			void flow_control(uart::flowcontrol::mode mode_){U2MODEbits.UEN=(0x03 & mode_);}
			//Reset all confige about UART
			void reset_all_config(){
				//UART MODE bits : UxMODE
				U2MODE &= 0x00010000;			//ON以外を0でフィル
				//UART Status and control bits : UxSTA
				U2STA=0;
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
