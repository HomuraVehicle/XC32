#ifndef XC32_TIMER_INC
#define XC32_TIMER_INC 100
#
#include<XCBase/type.hpp>
#include"exceptions.hpp"
#include"clock.hpp"
#include"sfr/interrupt.hpp"
#include"sfr/timer_base.hpp"
#ifndef __asm__
#define __asm__(val)
#endif
namespace xc32{
	using namespace xc;
	namespace timer{
		using namespace xc32::sfr::timer;
		struct not_initialize_exception :public exception{};
		struct not_lock_exception :public exception{};
	}

	template<typename timer_register_>
	class interrupt_timer{
	private:
		typedef typename timer_register_::type_prescaler prescaler;
		timer_register_ Register;
		sfr::interrupt::function* pInterrupt;
		unsigned char InterruptPriorityLv;
		xc32::uint32 Period;
		typename prescaler::div Prescaler;
	public:
		interrupt_timer()
			: pInterrupt(0)
			, InterruptPriorityLv(timer_register_::ipl)
			, Period(1)
			, Prescaler(prescaler::div1){
		}
		interrupt_timer(const timer_register_& Register_)
			: Register(Register_)
			, pInterrupt(0)
			, InterruptPriorityLv(timer_register_::ipl)
			, Period(1)
			, Prescaler(prescaler::div1){
		}
		~interrupt_timer(){if(is_initialize())release(); }
		void initialize(const timer_register_& Register_) {
			if(is_initialize())release();

			Register=Register_;
		}
		void release() {
			if(!is_initialize())return;

			pInterrupt=0;

			if(is_lock())unlock();
			Register.release();
		}
		bool is_initialize() const{ return static_cast<bool>(Register); }
	public:
		void config(xc32::uint32 Period_, typename prescaler::div Prescaler_, sfr::interrupt::function& Interrupt_, unsigned char InterruptPriorityLv_=timer_register_::ipl) {
			pInterrupt=&Interrupt_;
			InterruptPriorityLv=InterruptPriorityLv_;
			Period=Period_;
			Prescaler=Prescaler_;
		}
		void config(xc32::uint32 MSec_, sfr::interrupt::function& Interrupt_, unsigned char InterruptPriorityLv_=timer_register_::ipl) {
			typename prescaler::div Div=prescaler::auto_div(clock::get_bus_clock(),MSec_);
			return config(prescaler::period(clock::get_bus_clock(), MSec_, Div), Div, Interrupt_, InterruptPriorityLv_);
		}
		bool lock(xc32::uint32 Period_, typename prescaler::div Prescaler_, sfr::interrupt::function& Interrupt_, unsigned char InterruptPriorityLv_=timer_register_::ipl) {
			config(Period_, Prescaler_, Interrupt_, InterruptPriorityLv_);
			return lock();
		}
		bool lock(xc32::uint32 MSec_, sfr::interrupt::function& Interrupt_, unsigned char InterruptPriorityLv_=timer_register_::ipl) {
			config(MSec_, Interrupt_, InterruptPriorityLv_);
			return lock();
		}
		bool lock(){
			xc32_assert(is_initialize(), timer::not_initialize_exception());

//			xc32_assert(Register.timer_no()!=1, timer::invalid_timer_type_exception());
			if(is_lock())return false;

			if(pInterrupt==0)return true;

			if(Register.lock())return true;

			Register.reset_all_config();
			Register.interrupt_function(pInterrupt);

			Register.clock_select(false);			
			Register.interrupt_priority_level(InterruptPriorityLv);
			__asm__("NOP");
			Register.gate_enable(false);
			__asm__("NOP");
			Register.prescaler(Prescaler);
			__asm__("NOP");

			Register.period(Period);
			Register.count(0);

			return false;
		}
		bool is_lock()const{
			xc32_assert(is_initialize(), timer::not_initialize_exception());

			return Register.is_lock();
		}
		void unlock() {
			xc32_assert(is_initialize(), timer::not_initialize_exception());

			if(!is_lock())return;

			Register.enable(false);
			Register.reset_all_config();
			Register.unlock();
		}
	public:
		void start(){
			xc32_assert(is_lock(), timer::not_lock_exception());
			Register.enable(true);
			Register.interrupt_enable(true);
		}
		bool is_start()const{
			xc32_assert(is_lock(), timer::not_lock_exception());
			return Register.enable();
		}
		void stop(){
			xc32_assert(is_lock(), timer::not_lock_exception());
			Register.enable(false);
			Register.interrupt_enable(false);
		}
		unsigned int count()const{
			xc32_assert(is_lock(), timer::not_lock_exception());
			return Register.count();
		}
		void clear_count(){
			xc32_assert(is_lock(), timer::not_lock_exception());
			Register.count(0);
		}
		void set_count(unsigned int val_){
			xc32_assert(is_lock(), timer::not_lock_exception());
			Register.count(val_);
		}
		unsigned int period()const{
			xc32_assert(is_lock(), timer::not_lock_exception());
			return Register.period();
		}
		void set_period(unsigned int val_){
			xc32_assert(is_lock(), timer::not_lock_exception());
			Register.period(val_);
		}
		/*
		bool is_enable() const {
			xc32_assert(is_lock(), timer::not_lock_exception());
			return Register.interrupt_enable();
		}
		void enable(){
			xc32_assert(is_lock(), timer::not_lock_exception());
			Register.interrupt_enable(true);
		}
		void disable(){
			xc32_assert(is_lock(), timer::not_lock_exception());
			Register.interrupt_enable(false);
		}
		void get_flag()const volatile{
			xc32_assert(is_lock(), timer::not_lock_exception());
			return Register.interrupt_flag();
		}*/
		void set_flag(){
			xc32_assert(is_lock(), timer::not_lock_exception());
			Register.interrupt_flag(true);
		}
		void clear_flag(){
			xc32_assert(is_lock(), timer::not_lock_exception());
			Register.interrupt_flag(false);
		}
	};

	template<typename timer_register_>
	class delay_ms_timer{
	private:
		typedef typename timer_register_::type_prescaler prescaler;
		timer_register_ Register;
		unsigned int MSec;
		unsigned int RepeatNum;
	public:
		delay_ms_timer() {}
		delay_ms_timer(const timer_register_& Register_):Register(Register_){}
		~delay_ms_timer(){if(is_initialize())release(); }
		void initialize(const timer_register_& Register_) {
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
		bool lock() {
			xc32_assert(is_initialize(), timer::not_initialize_exception());

//			xc32_assert(Register.timer_no()!=1, timer::invalid_timer_type_exception());

			if(is_lock())return false;

			if(Register.lock())return true;

			Register.reset_all_config();

			Register.clock_select(false);
			__asm__("NOP");
			Register.gate_enable(false);
			__asm__("NOP");
			Register.prescaler(prescaler::div1);
			__asm__("NOP");

			MSec=0;
			RepeatNum=1;

			return false;
		}
		void unlock() { 
			xc32_assert(is_initialize(), timer::not_initialize_exception());

			if(!is_lock())return;

			Register.enable(false);
			Register.reset_all_config();

			Register.unlock();
		}
		bool is_lock() const{
			xc32_assert(is_initialize(), timer::not_initialize_exception());

			return Register.is_lock(); 
		}
	private:
		void wait() {
			Register.count(0);
			Register.interrupt_flag(false);
			Register.enable(true);

			//割り込み時間内だった場合
			for(unsigned int RepeatCnt = 0; RepeatCnt<RepeatNum; ++RepeatCnt) {
				while(!Register.interrupt_flag());
				Register.count(0);
				Register.interrupt_flag(false);
			}

			Register.enable(false);
			Register.interrupt_flag(false);
		}
	public:
		void operator()(unsigned int MSec_) {
			xc32_assert(is_lock(), timer::not_lock_exception());

			//同じ時間でのdelayを高速化できるように、設定を覚えておく
			if(MSec!=MSec_) {
				uint16 DivCnt=0;
				typename prescaler::div Div;

				MSec=MSec_;
				RepeatNum=1;

				while(1) {
					//最初は1で試して、次は2、その次は5、以降10、20、50・・・という順で割ってみる
					if(DivCnt%3==0) {
						Div=prescaler::auto_div(clock::get_bus_clock(),MSec_);
						if(Div!=prescaler::diverr) {
							break;
						}
						++DivCnt;
					} else if(DivCnt%3==1) {
						Div=prescaler::auto_div(clock::get_bus_clock(),MSec_/2);
						if(Div!=prescaler::diverr) {
							MSec_/=2;
							RepeatNum*=2;
							break;
						}
						++DivCnt;
					} else {
						Div=prescaler::auto_div(clock::get_bus_clock(),MSec_/5);
						if(Div!=prescaler::diverr) {
							MSec_/=5;
							RepeatNum*=5;
							break;
						}
						MSec_/=10;
						RepeatNum*=10;
						++DivCnt;
					}
				}
				Register.prescaler(Div);
				__asm__("NOP");
				Register.period(prescaler::period(clock::get_bus_clock(),MSec_,Div));
			}

			wait();
		}
		void operator()(unsigned int period_, typename prescaler::div Div_) {
			xc32_assert(is_lock(), timer::not_lock_exception());

			MSec = 0;
			RepeatNum = 1;

			Register.prescaler(Div_);
			__asm__("NOP");
			Register.period(period_);

			wait();
		}
	};
}

#
#endif
