#ifndef XC32LIB_TEST_VIRTUALUARTREGISTER_INC
#define XC32LIB_TEST_VIRTUALUARTREGISTER_INC 101
#
/*=== uart1 ===
êVå^äÑÇËçûÇ›ä÷êîñºÇ…ïœçX
*/
#include<deque>
#include<XC32Lib/sfr/exclusive_mixin.hpp>
#include<XC32Lib/sfr/sfr_register_mixin.hpp>
#include<XC32Lib/sfr/interrupt.hpp>
#include<XC32Lib/sfr/uart_base.hpp>


namespace xc32{
	namespace test{
		using namespace sfr;
		template<unsigned int no_>
		struct virtual_uart_register
			: public sfr_register_mixin< virtual_uart_register<no_> >
			, public exclusive_mixin<virtual_uart_register<no_> >{
			static unsigned int uart_no(){ return 100+no_; }
			static bool rx_interrupt_IsEnable;
			static bool rx_interrupt_Flag;
			static unsigned char rx_interrupt_PriorityLevel;
			static unsigned char rx_interrupt_SubPriorityLevel;
			static bool tx_interrupt_IsEnable;
			static bool tx_interrupt_Flag;
			static unsigned char tx_interrupt_PriorityLevel;
			static unsigned char tx_interrupt_SubPriorityLevel;
			static std::deque<unsigned char> rx_Buf;
			static std::deque<unsigned char> tx_Buf;
			static bool IsEnable;
			static bool IsRxEnable;
			static bool IsTxEnable;
			static unsigned char BRG;
			static const unsigned char tx_ipl;
			static const unsigned char rx_ipl;

			static void register_initialize() {
				rx_interrupt_IsEnable=false;
				rx_interrupt_Flag=false;
				rx_interrupt_PriorityLevel=0;
				rx_interrupt_SubPriorityLevel=0;
				tx_interrupt_IsEnable=false;
				tx_interrupt_Flag=false;
				tx_interrupt_PriorityLevel=0;
				tx_interrupt_SubPriorityLevel=0;
				rx_Buf.clear();
				tx_Buf.clear();
				IsEnable=false;
				IsRxEnable=false;
				IsTxEnable=false;
				BRG=0;
				tx_interrupt_ptr=0;
				rx_interrupt_ptr=0;
			}
		public:
			//Receive Interrupt Enable bit : IECxbits.UxRXIE
			void rx_interrupt_enable(bool val_){rx_interrupt_IsEnable=static_cast<unsigned char>(val_);}
			bool rx_interrupt_enable()const{return static_cast<bool>(rx_interrupt_IsEnable);}
			//Receive Interrupt Flag bit : IFSxbits.UxRXIF
			void rx_interrupt_flag(bool val_){rx_interrupt_Flag=static_cast<unsigned char>(val_);}
			bool rx_interrupt_flag()const {return static_cast<bool>(rx_interrupt_Flag);}
			//Interrupt priority level : IPCxbits.UxIP
			void rx_interrupt_priority_level(unsigned char val_){rx_interrupt_PriorityLevel=val_;}
			unsigned char rx_interrupt_priority_level(){return rx_interrupt_PriorityLevel;}
			//Interrupt priority level : IPCxbits.UxIP
			void rx_interrupt_sub_priority_level(unsigned char val_){rx_interrupt_SubPriorityLevel=val_;}
			unsigned char rx_interrupt_sub_priority_level(){return rx_interrupt_SubPriorityLevel;}
			//Transmit Interrupt Enable bit : IECxbits.UxTXIE
			void tx_interrupt_enable(bool val_){tx_interrupt_IsEnable=static_cast<unsigned char>(val_);}
			bool tx_interrupt_enable()const{return static_cast<bool>(tx_interrupt_IsEnable);}
			//Transmit Interrupt Flag : IFSxbits.UxTXIF
			void tx_interrupt_flag(bool val_){tx_interrupt_Flag=static_cast<unsigned char>(val_);}
			bool tx_interrupt_flag()const {return static_cast<bool>(tx_interrupt_Flag);}
			//Interrupt priority level : IPCxbits.UxIP
			void tx_interrupt_priority_level(unsigned char val_){tx_interrupt_PriorityLevel=val_;}
			unsigned char tx_interrupt_priority_level(){return tx_interrupt_PriorityLevel;}
			//Interrupt priority level : IPCxbits.UxIP
			void tx_interrupt_sub_priority_level(unsigned char val_){tx_interrupt_SubPriorityLevel=val_;}
			unsigned char tx_interrupt_sub_priority_level(){return tx_interrupt_SubPriorityLevel;}
			//Receive Buffer Data Available bit : UxSTATbits.URXDA
			bool rx_buf_full()const {return false;}
			//Receive Register : UxRXREG
			unsigned char rx_buf_get() { unsigned char c=rx_Buf.front(); rx_Buf.pop_front(); return c; }
			//Receive Buffer Overrun Error Status bit : UxSTAbits.OERR
			void rx_buf_overflow(bool val_){}
			bool rx_buf_overflow()const {return false;}
			//Transmit Buffer Full Status bit : UxSTAbits.UTXBF
			bool tx_buf_full()const {return false;}
			//Transmit Register : UxTXREG
			void tx_buf_set(unsigned char val_){tx_Buf.push_back(val_);}
			//UART enable bit : UxMODEbits.ON
			void enable(bool val_){IsEnable=static_cast<unsigned char>(val_);}
			bool enable()const{return static_cast<bool>(IsEnable);}
			//Transmit enable bit : UxSTAbits.UTXEN
			void tx_enable(bool val_){IsTxEnable=static_cast<unsigned char>(val_);}
			bool tx_enable()const{return static_cast<bool>(IsTxEnable);}
			//Receiver Enable bit : UxSTAbits.URXEN
			void rx_enable(bool val_){IsRxEnable=static_cast<unsigned char>(val_);}
			bool rx_enable()const{return static_cast<bool>(IsRxEnable);}
			//Baud Rate Register : UxBRG
			void baud_rate_register(unsigned int val_){BRG=val_;}
			//Transmit Interrupt Mode Selection bits : UxSTAbits.UTXISEL1,UxSTAbits.UTXISEL0
			void tx_interrupt_mode(sfr::uart::tx_interrupt_mode::mode mode_) {}
			//Receive Interrupt Mode Selection bit : UxSTAbits.URXISEL
			void rx_interrupt_mode(sfr::uart::rx_interrupt_mode::mode mode_) {}
			//Flow Control bits : UxMODEbits.UEN
			void flow_control(sfr::uart::flowcontrol::mode mode_){}
			//Reset all confige about UART
			void reset_all_config(){
				//Interrupt Reset
				rx_interrupt_enable(false);
				rx_interrupt_flag(false);
				tx_interrupt_enable(false);
				tx_interrupt_flag(false);
				rx_interrupt_function(0);
				tx_interrupt_function(0);
			}
		public:
			static sfr::interrupt::function* tx_interrupt_ptr;
			static sfr::interrupt::function* rx_interrupt_ptr;
		public:
			const sfr::interrupt::function* tx_interrupt_function()const{return tx_interrupt_ptr;}
			void tx_interrupt_function(sfr::interrupt::function* ptr_) { tx_interrupt_ptr=ptr_; }
			const sfr::interrupt::function* rx_interrupt_function()const{return rx_interrupt_ptr;}
			void rx_interrupt_function(sfr::interrupt::function* ptr_){rx_interrupt_ptr=ptr_;}
		};
		template<unsigned int no_>
		bool virtual_uart_register<no_>::rx_interrupt_IsEnable=false;
		template<unsigned int no_>
		bool virtual_uart_register<no_>::rx_interrupt_Flag=false;
		template<unsigned int no_>
		unsigned char virtual_uart_register<no_>::rx_interrupt_PriorityLevel=0;
		template<unsigned int no_>
		unsigned char virtual_uart_register<no_>::rx_interrupt_SubPriorityLevel=0;
		template<unsigned int no_>
		bool virtual_uart_register<no_>::tx_interrupt_IsEnable=false;
		template<unsigned int no_>
		bool virtual_uart_register<no_>::tx_interrupt_Flag=false;
		template<unsigned int no_>
		unsigned char virtual_uart_register<no_>::tx_interrupt_PriorityLevel=0;
		template<unsigned int no_>
		unsigned char virtual_uart_register<no_>::tx_interrupt_SubPriorityLevel=0;
		template<unsigned int no_>
		std::deque<unsigned char> virtual_uart_register<no_>::rx_Buf;
		template<unsigned int no_>
		std::deque<unsigned char> virtual_uart_register<no_>::tx_Buf;
		template<unsigned int no_>
		bool virtual_uart_register<no_>::IsEnable=false;
		template<unsigned int no_>
		bool virtual_uart_register<no_>::IsRxEnable=false;
		template<unsigned int no_>
		bool virtual_uart_register<no_>::IsTxEnable=false;
		template<unsigned int no_>
		unsigned char virtual_uart_register<no_>::BRG=0;
		template<unsigned int no_>
		sfr::interrupt::function* virtual_uart_register<no_>::tx_interrupt_ptr=0;
		template<unsigned int no_>
		sfr::interrupt::function* virtual_uart_register<no_>::rx_interrupt_ptr=0;
		template<unsigned int no_>
		const unsigned char virtual_uart_register<no_>::tx_ipl=7;
		template<unsigned int no_>
		const unsigned char virtual_uart_register<no_>::rx_ipl=7;
	}
}

#
#endif
