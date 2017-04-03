#ifndef XC32_UART_INC
#define XC32_UART_INC 101
#
/*
=== xc32::uart ===
v1_01/140727 hmIto
	registerとhardwareを統合
*/
//#include"interrupt.hpp"
#include"exceptions.hpp"
#include"sfr/uart_base.hpp"
#include"sfr/interrupt.hpp"
#ifndef __asm__
#define __asm__(val)
#endif
namespace xc32{
	namespace uart {
		struct exception :public xc32::exception{};		
		struct not_initialize_exception :public exception{};
		struct not_lock_exception :public exception{};
		using namespace xc32::sfr::uart;
	}
	template<typename uart_register_>
	class synchronous_uart{
	private:
		uart_register_ Register;
		unsigned long BPS;
		sfr::uart::flowcontrol::mode FlowControl;		
	public:
		synchronous_uart():BPS(9600),FlowControl(sfr::uart::flowcontrol::no_control) {}
//		synchronous_uart(const uart_register_& Register_):Register(Register_),Hardware(Hardware_),BPS(9600),FlowControl(sfr::uart::flowcontrol::no_control){}
		synchronous_uart(const uart_register_& Register_):Register(Register_), BPS(9600), FlowControl(sfr::uart::flowcontrol::no_control) {}
		~synchronous_uart() { if(is_initialize()) release(); }
		void initialize(const uart_register_& Register_) {
			if(is_initialize())release();

			Register=Register_;
		}
		void release() {
			if(!is_initialize())return;

			if(is_lock())unlock();
			Register.release();
		}
		bool is_initialize() const{ return static_cast<bool>(Register); }
	public:
		void config(unsigned long BPS_, sfr::uart::flowcontrol::mode FlowControl_){
			BPS=BPS_;
			FlowControl=FlowControl_;
		}
		bool lock(unsigned long BPS_, sfr::uart::flowcontrol::mode FlowControl_) {
			config(BPS_,FlowControl_);
			return lock();
		}
		bool lock(){
			xc32_assert(is_initialize(), uart::not_initialize_exception());
			if(is_lock())return false;

			if(Register.lock())return true;

			Register.enable(true);
			Register.tx_enable(true);
			Register.rx_enable(true);

			Register.baud_rate_register(uart::baud_rate(BPS));
			Register.tx_interrupt_mode(sfr::uart::tx_interrupt_mode::move_each);
			Register.rx_interrupt_mode(sfr::uart::rx_interrupt_mode::move_each);
			Register.flow_control(FlowControl);
			Register.rx_buf_overflow(false);
			Register.rx_interrupt_enable(false);
			Register.rx_interrupt_flag(false);
			Register.tx_interrupt_enable(false);
			Register.tx_interrupt_flag(false);

			return false;
		}
		bool is_lock()const{
			xc32_assert(is_initialize(), uart::not_initialize_exception());

			return Register.is_lock();
		}
		void unlock(){
			xc32_assert(is_initialize(), uart::not_initialize_exception());

			if(!is_lock())return;

			Register.enable(false);
			Register.reset_all_config();

			Register.unlock();
		}
	public:
		bool can_getc()const {//volatile{
			xc32_assert(is_lock(), uart::not_lock_exception());
			return Register.rx_buf_full();
		}
		unsigned char getc(){
			xc32_assert(is_lock(), uart::not_lock_exception());
			while(!Register.rx_buf_full());
			if(Register.rx_buf_overflow())Register.rx_buf_overflow(false);
			unsigned char tmp=Register.rx_buf_get();

			return tmp;
		}
		bool can_putc()const {//volatile{
			xc32_assert(is_lock(), uart::not_lock_exception());
			return !Register.tx_buf_full();
		}
		void putc(unsigned char data_){
			xc32_assert(is_lock(), uart::not_lock_exception());
			while(Register.tx_buf_full());
			Register.tx_buf_set(data_);
		}
	};
	template<typename uart_register_>
	class interrupt_uart{
	private:
		uart_register_ Register;
		sfr::interrupt::function* pSendInterrupt;
		sfr::interrupt::function* pRecvInterrupt;
		unsigned char RxInterruptPriorityLv;
		unsigned char TxInterruptPriorityLv;
		unsigned long BPS;
		sfr::uart::flowcontrol::mode FlowControl;	
	public:
		interrupt_uart()
			: pSendInterrupt(0)
			, pRecvInterrupt(0)
			, RxInterruptPriorityLv(uart_register_::rx_ipl)
			, TxInterruptPriorityLv(uart_register_::tx_ipl)
			, BPS(9600)
			, FlowControl(sfr::uart::flowcontrol::no_control) {
		}
		interrupt_uart(const uart_register_& Register_)
			:Register(Register_)
			, pSendInterrupt(0)
			, pRecvInterrupt(0)
			, RxInterruptPriorityLv(uart_register_::rx_ipl)
			, TxInterruptPriorityLv(uart_register_::tx_ipl)
			, BPS(9600)
			, FlowControl(sfr::uart::flowcontrol::no_control) {
		}
		~interrupt_uart() {if(is_initialize()) release(); }
		void initialize(const uart_register_& Register_) {
			if(is_initialize())release();

			Register=Register_;
		}
		void release() {
			if(!is_initialize())return;

			pSendInterrupt=0;
			pRecvInterrupt=0;

			if(is_lock())unlock();
			Register.release();
		}
		bool is_initialize() const{ return static_cast<bool>(Register); }
	public:
		void config(unsigned long BPS_, sfr::uart::flowcontrol::mode FlowControl_, sfr::interrupt::function& SendInterrupt_, sfr::interrupt::function& RecvInterrupt_, unsigned char TxInterruptPriorityLv_ = uart_register_::tx_ipl, unsigned char RxInterruptPriorityLv_ = uart_register_::rx_ipl) {
			pSendInterrupt=&SendInterrupt_;
			pRecvInterrupt=&RecvInterrupt_;
			RxInterruptPriorityLv=RxInterruptPriorityLv_;
			TxInterruptPriorityLv=TxInterruptPriorityLv_;
			BPS=BPS_;
			FlowControl=FlowControl_;
		}
		bool lock(unsigned long BPS_, sfr::uart::flowcontrol::mode FlowControl_, sfr::interrupt::function& SendInterrupt_, sfr::interrupt::function& RecvInterrupt_, unsigned char TxInterruptPriorityLv_ = uart_register_::tx_ipl, unsigned char RxInterruptPriorityLv_ = uart_register_::rx_ipl) {
			config(BPS_, FlowControl_, SendInterrupt_, RecvInterrupt_, TxInterruptPriorityLv_, RxInterruptPriorityLv_);
			return lock();
		}
		bool lock(){
			xc32_assert(is_initialize(), uart::not_initialize_exception());

			if(is_lock())return false;

			if(pSendInterrupt==0 || pRecvInterrupt==0)return true;
			if(Register.lock())return true;

			Register.enable(false);
			Register.reset_all_config();

			Register.tx_interrupt_function(pSendInterrupt);
			Register.rx_interrupt_function(pRecvInterrupt);

			Register.baud_rate_register(xc32::sfr::uart::baud_rate(BPS));

			Register.tx_interrupt_priority_level(TxInterruptPriorityLv);
			Register.rx_interrupt_priority_level(RxInterruptPriorityLv);
			__asm__("NOP");
			Register.flow_control(FlowControl);
			__asm__("NOP");
			Register.rx_buf_overflow(false);
			__asm__("NOP");
			Register.rx_interrupt_enable(false);
			__asm__("NOP");
			Register.rx_interrupt_flag(false);
			__asm__("NOP");
			Register.tx_interrupt_enable(false);
			__asm__("NOP");
			Register.tx_interrupt_flag(false);
			__asm__("NOP");

			Register.tx_enable(true);
			__asm__("NOP");
			Register.rx_enable(true);
			__asm__("NOP");
			Register.tx_interrupt_mode(sfr::uart::tx_interrupt_mode::move_each);
			__asm__("NOP");
			Register.rx_interrupt_mode(sfr::uart::rx_interrupt_mode::move_each);
			__asm__("NOP");
			Register.enable(true);

			return false;
		}
		bool is_lock()const{
			xc32_assert(is_initialize(), uart::not_initialize_exception());
			return Register.is_lock();
		}
		void unlock(){
			xc32_assert(is_initialize(), uart::not_initialize_exception());

			if(!is_lock())return;

			Register.enable(false);
			Register.reset_all_config();

			Register.unlock();
		}
	public://recv functions
		bool recv_in_data()const {//volatile{
			xc32_assert(is_lock(), uart::not_lock_exception());
			return Register.rx_buf_full();
		}
		unsigned char recv_data() {
			xc32_assert(is_lock(), uart::not_lock_exception());
			return Register.rx_buf_get();
		}
		bool recv_is_overflow()const volatile{
			xc32_assert(is_lock(), uart::not_lock_exception());
			return Register.rx_buf_overflow();
		}
		void recv_clear_overflow() {
			xc32_assert(is_lock(), uart::not_lock_exception());
			Register.rx_buf_overflow(false); 
		}
		bool recv_is_flag()const volatile{
			xc32_assert(is_lock(), uart::not_lock_exception());
			return Register.rx_interrupt_flag(); 
		}
		void recv_clear_flag() { 
			xc32_assert(is_lock(), uart::not_lock_exception());
			return Register.rx_interrupt_flag(false); 
		}
		void recv_set_flag() { 
			xc32_assert(is_lock(), uart::not_lock_exception());
			return Register.rx_interrupt_flag(true);
		}
		bool recv_is_enable()const {
			xc32_assert(is_lock(), uart::not_lock_exception());
			return Register.rx_interrupt_enable();
		}
		void recv_enable() { 
			xc32_assert(is_lock(), uart::not_lock_exception());
			return Register.rx_interrupt_enable(true); 
		}
		void recv_disable() { 
			xc32_assert(is_lock(), uart::not_lock_exception());
			return Register.rx_interrupt_enable(false); 
		}
	public://send functions
		bool send_in_data()const {//volatile{
			xc32_assert(is_lock(), uart::not_lock_exception());
			return Register.tx_buf_full();
		}
		void send_data(unsigned char c) {
			xc32_assert(is_lock(), uart::not_lock_exception());
			return Register.tx_buf_set(c);
		}
		bool send_is_flag()const volatile{ 
			xc32_assert(is_lock(), uart::not_lock_exception());
			return Register.tx_interrupt_flag(); 
		}
		void send_clear_flag() { 
			xc32_assert(is_lock(), uart::not_lock_exception());
			return Register.tx_interrupt_flag(false); 
		}
		void send_set_flag() { 
			xc32_assert(is_lock(), uart::not_lock_exception());
			return Register.tx_interrupt_flag(true); 
		}
		bool send_is_enable()const {
			xc32_assert(is_lock(), uart::not_lock_exception());
			return Register.tx_interrupt_enable();
		}
		void send_enable() { 
			xc32_assert(is_lock(), uart::not_lock_exception());
			return Register.tx_interrupt_enable(true);
		}
		void send_disable() { 
			xc32_assert(is_lock(), uart::not_lock_exception());
			return Register.tx_interrupt_enable(false); 
		}
	};
}
#
#endif
