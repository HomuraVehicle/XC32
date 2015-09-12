#ifndef XC32_LONGTIMER_INC
#define XC32_LONGTIMER_INC 100
#
#include<XCBase/type_traits.hpp>
#include<XCBase/type.hpp>
#include<XCBase/lock.hpp>
#include"exceptions.hpp"
#include"sfr/interrupt.hpp"
#include"sfr/timer_base.hpp"
#include"clock.hpp"

/*
Only Type B timer modules support 32-bit modes of operation. A 32-bit Timer module is formed
by combining an even numbered Type B timer (referred to as TimerX) with a consecutive odd
numbered Type B timer (referred to as TimerY). For example, 32-bit timer combinations are
Timer2 and Timer3, Timer4 and Timer5, and so on. The number of timer pairs depends on the
particular PIC32 device.
The 32-bit timer pairs can operate in the following modes:
• 32-bit Synchronous Clock Counter
• 32-bit Synchronous External Clock Counter
• 32-bit Gated Timer
The 32-bit Timer modes are determined by the following bits:
• T32 (TxCON<3>): 32-bit Timer Mode Select bit (TimerX only)
• TCS (TxCON<1>): Timer Clock Source Select bit
• TGATE (TxCON<7>): Timer Gated Time Accumulation Enable bit
Specific behavior in 32-bit Timer mode:
• TimerX is the master timer; TimerY is the slave timer
• TMRx count register is least significant half word of the 32-bit timer value
• TMRy count register is most significant half word of the 32-bit timer value
• PRx period register is least significant half word of the 32-bit period value
• PRy period register is most significant half word of the 32-bit period value
• TimerX control bits (TxCON) configure the operation for the 32-bit timer pair
• TimerY control bits (TyCON) have no effect
• TimerX interrupt and status bits are ignored
• TimerY provides the interrupt enable, interrupt flag and interrupt priority control bits
*/

namespace xc32{
	using namespace xc;
	namespace longtimer{
		struct exception :public xc32::exception{};
		struct not_initialize_exception :public exception{};
		struct not_open_exception :public exception{};
		struct over_div_exception : public exception {};
		using namespace sfr::timer;
	}

	template<typename master_timer_register_,typename slave_timer_register_,typename is_valid_timer_combination_=typename sfr::timer::is_valid_combination<master_timer_register_,slave_timer_register_>::type >
	class interrupt_longtimer {};
	template<typename master_timer_register_,typename slave_timer_register_>
	class interrupt_longtimer<master_timer_register_, slave_timer_register_, true_type>{
	private:
		typedef typename master_timer_register_::type_prescaler prescaler;
		master_timer_register_ Master_Register;
		slave_timer_register_ Slave_Register;
		sfr::interrupt::function* pInterrupt;
		unsigned char InterruptPriorityLv;
		uint64 Period;
		typename prescaler::div Prescaler;
//		longtimer::prescaler::div Prescaler;
	public:
		interrupt_longtimer()
			: pInterrupt(0)
			, InterruptPriorityLv(slave_timer_register_::ipl)
			, Period(1)
			, Prescaler(prescaler::div1){
		}
		interrupt_longtimer(const master_timer_register_& Master_Register_,const slave_timer_register_& Slave_Register_)
			: Master_Register(Master_Register_)
			, Slave_Register(Slave_Register_)
			, pInterrupt(0)
			, InterruptPriorityLv(slave_timer_register_::ipl)
			, Period(1)
			, Prescaler(prescaler::div1){
		}
		~interrupt_longtimer(){if(is_initialize())release();}
	public:
		void initialize(const master_timer_register_& Master_register_,const slave_timer_register_& Slave_register_){
			if(is_initialize())release();

			Master_Register=Master_register_;
			Slave_Register=Slave_register_;
		}
		void release(){
			if(!is_initialize())return;

			pInterrupt=0;

			if(is_lock())unlock();
			Master_Register.release();
			Slave_Register.release();
		}
		bool is_initialize()const{
			return (static_cast<bool>(Master_Register) && static_cast<bool>(Slave_Register));
		}
	public:
		void config(uint64 Period_, typename prescaler::div Prescaler_, sfr::interrupt::function& Interrupt_, unsigned char InterruptPriorityLv_=slave_timer_register_::ipl) {
			pInterrupt=&Interrupt_;
			InterruptPriorityLv=InterruptPriorityLv_;
			Period=Period_;
			Prescaler=Prescaler_;
		}
		void config(uint64 MSec_, sfr::interrupt::function& Interrupt_, unsigned char InterruptPriorityLv_=slave_timer_register_::ipl) {
			typename prescaler::div Div = prescaler::long_auto_div(clock::get_bus_clock(), MSec_);
			return config(prescaler::long_period(clock::get_bus_clock(), MSec_, Div), Div, Interrupt_, InterruptPriorityLv_);
		}
		bool lock(uint64 Period_, typename prescaler::div Prescaler_, sfr::interrupt::function& Interrupt_, unsigned char InterruptPriorityLv_=slave_timer_register_::ipl) {
			config(Period_, Prescaler_, Interrupt_, InterruptPriorityLv_);
			return lock();
		}
		bool lock(uint64 MSec_, sfr::interrupt::function& Interrupt_, unsigned char InterruptPriorityLv_=slave_timer_register_::ipl) {
			config(MSec_, Interrupt_, InterruptPriorityLv_);
			return lock();
		}
		bool lock() {
			xc32_assert(is_initialize(), longtimer::not_initialize_exception());

			if(is_lock())return false;

			if(!sfr::timer::is_valid_combination_dynamic(Master_Register, Slave_Register))return true;

			if(pInterrupt==0)return true;

			if(xc32::lock(Master_Register,Slave_Register))return true;

			//一応リセット
			Master_Register.reset_all_config();
			__asm__("NOP");
			Slave_Register.reset_all_config();

			//割り込み系はslaveで設定
			Slave_Register.interrupt_function(pInterrupt);
			Slave_Register.interrupt_priority_level(InterruptPriorityLv);

			//config系はMasterでいじる
//			Master_Register.clock_select(false);
			__asm__("NOP");
			Master_Register.gate_enable(false);
			__asm__("NOP");
			Master_Register.prescaler(Prescaler);
			__asm__("NOP");
			Master_Register.enable_32bit(true);

			Master_Register.period(static_cast<unsigned int>(Period));
			Slave_Register.period(static_cast<unsigned int>(Period>>16));
			Master_Register.count(0);
			Slave_Register.count(0);

			return false;
		}
		bool is_lock()const{
			xc32_assert(is_initialize(),longtimer::not_initialize_exception());
			
			return (Master_Register.is_lock() && Slave_Register.is_lock());
		}
		void unlock(){
			xc32_assert(is_initialize(),longtimer::not_initialize_exception());

			if(!is_lock())return;

			Master_Register.reset_all_config();
			Slave_Register.reset_all_config();

			Master_Register.enable(false);
			Slave_Register.enable(false);

			Master_Register.unlock();
			Slave_Register.unlock();
		}
	public:
		void start(){
			xc32_assert(is_open(),longtimer::not_open_exception());
			Master_Register.enable(true);
			Slave_Register.interrupt_enable(true);
		}
		bool is_start()const{
			xc32_assert(is_open(),longtimer::not_open_exception());
			return Master_Register.enable();
		}
		void stop(){
			xc32_assert(is_open(),longtimer::not_open_exception());
			Slave_Register.interrupt_enable(false);
			Master_Register.enable(false);
		}
		void clear_count(){
			xc32_assert(is_open(),longtimer::not_open_exception());
			Master_Register.count(0);
			Slave_Register.count(0);
		}
		uint32 count()const volatile{
			xc32_assert(is_open(),longtimer::not_open_exception());
			uint32 tmp=static_cast<uint32>(Master_Register.count());
			tmp|=static_cast<uint32>(Slave_Register.count()<<16);
			return tmp;
		}
		void set_count(uint32 val_){
			xc32_assert(is_open(),longtimer::not_open_exception());
			Master_Register.count(static_cast<uint16>(val_ && 0x0000FFFF));
			Slave_Register.count(static_cast<uint16>(val_ >> 16));
		}
		uint32 period()const{
			xc32_assert(is_open(),longtimer::not_open_exception());
			uint32 tmp=static_cast<uint32>(Master_Register.period());
			tmp|=static_cast<uint32>(Slave_Register.period()<<16);
			return tmp;
		}
		void set_period(uint32 val_){
			xc32_assert(is_open(),longtimer::not_open_exception());
			Master_Register.period(static_cast<uint16>(val_ & 0x0000FFFF));
			Slave_Register.period(static_cast<uint16>(val_ >>16));
		}
		bool is_enable()const volatile{
			xc32_assert(is_open(),longtimer::not_open_exception());
			return Slave_Register.interrupt_enable();
		}
		void enable(){
			xc32_assert(is_open(),longtimer::not_open_exception());
			Slave_Register.interrupt_enable(true);
		}
		void disable(){
			xc32_assert(is_open(),longtimer::not_open_exception());
			Slave_Register.interrupt_enable(false);
		}
		void get_flag()const volatile{
			xc32_assert(is_open(),longtimer::not_open_exception());
			return Slave_Register.interrupt_flag();
		}
		void set_flag(){
			xc32_assert(is_open(),longtimer::not_open_exception());
			Slave_Register.interrupt_flag(true);
		}
		void clear_flag(){
			xc32_assert(is_open(),longtimer::not_open_exception());
			Slave_Register.interrupt_flag(false);
		}
	};

	template<typename master_timer_register_, typename slave_timer_register_, typename is_valid_timer_combination_ = typename sfr::timer::is_valid_combination<master_timer_register_, slave_timer_register_>::type>
	class delay_ms_longtimer{};
	template<typename master_timer_register_,typename slave_timer_register_>
	class delay_ms_longtimer<master_timer_register_,slave_timer_register_, true_type>{
	private:
		typedef typename master_timer_register_::type_prescaler prescaler;
		master_timer_register_ Master_Register;
		slave_timer_register_  Slave_Register;
		uint32 miliseconds;
		uint32 RepeatNum;
	public:
		delay_ms_longtimer(){}
		delay_ms_longtimer(const master_timer_register_& Master_Register_,const slave_timer_register_& Slave_Register_):Master_Register(Master_Register_),Slave_Register(Slave_Register_){}
		~delay_ms_longtimer() { if(is_initialize())release(); };
		void initialize(const master_timer_register_& Master_Register_,const slave_timer_register_& Slave_Register_){
			if(is_initialize())release();

			Master_Register=Master_Register_;
			Slave_Register=Slave_Register_;
		}
		void release(){
			if(!is_initialize())return;

			if(is_lock())unlock();
			Master_Register.release();
			Slave_Register.release();
		}
		bool is_initialize()const{return (static_cast<bool>(Master_Register) && static_cast<bool>(Slave_Register));}
	public:
		bool lock(){
			xc32_assert(is_initialize(), longtimer::not_initialize_exception());

			if(is_lock())return false;

			if(!sfr::timer::is_valid_combination_dynamic(Master_Register, Slave_Register))return true;
			
			if(Master_Register.lock())return true;
			if(Slave_Register.lock()){
				Master_Register.unlock();
				return true;
			}

			//一応リセット
			Master_Register.reset_all_config();
			__asm__("NOP");
			Slave_Register.reset_all_config();

			//config系はMasterでいじる
//			Master_Register.clock_select(false);
			__asm__("NOP");
			Master_Register.gate_enable(false);
			__asm__("NOP");
			Master_Register.prescaler(prescaler::div1);
			__asm__("NOP");
			Master_Register.enable_32bit(true);

			Master_Register.period(0);
			Slave_Register.period(0);
			Master_Register.count(0);
			Slave_Register.count(0);

			miliseconds=0;
			RepeatNum=1;
			return false;
		}
		void unlock(){
			xc32_assert(is_initialize(),longtimer::not_initialize_exception());

			if(!is_lock())return;

			Master_Register.reset_all_config();
			Slave_Register.reset_all_config();

			Master_Register.unlock();
			Slave_Register.unlock();
			miliseconds=0;
			RepeatNum=0;

		}
		bool is_lock()const{
			xc32_assert(is_initialize(),longtimer::not_initialize_exception());
			
			return (Master_Register.is_lock() && Slave_Register.is_lock());
		}
	public:
		void operator()(unsigned int MSec_) {
			xc32_assert(is_open(), longtimer::not_open_exception());

			//同じ時間でのdelayを高速化できるように、設定を覚えておく
			if(miliseconds!=MSec_) {
				uint16 DivCnt=0;
				typename prescaler::div Div;

				miliseconds=MSec_;
				RepeatNum=1;

				while(1) {
					//最初は1で試して、次は2、その次は5、以降10、20、50・・・という順で割ってみる
					if(DivCnt%3==0) {
						Div=prescaler::long_auto_div(clock::get_bus_clock(),MSec_);
						if(Div!=prescaler::diverr) {
							break;
						}
						++DivCnt;
					} else if(DivCnt%3==1) {
						Div=prescaler::long_auto_div(clock::get_bus_clock(),MSec_/2);
						if(Div!=prescaler::diverr) {
							MSec_/=2;
							RepeatNum*=2;
							break;
						}
						++DivCnt;
					} else {
						Div=prescaler::long_auto_div(clock::get_bus_clock(),MSec_/5);
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
				Master_Register.prescaler(Div);
				__asm__("NOP");
//				uint64 Period=timer::prescaler::long_period(clock::get_bus_clock(), MSec_, Div);
//				Master_Register.period(static_cast<uint32>(Period));
//				Slave_Register.period(static_cast<uint32>(Period>>32));
				uint32 Period = prescaler::long_period(clock::get_bus_clock(), MSec_, Div);
				Master_Register.period(static_cast<uint16>(Period));
				Slave_Register.period(static_cast<uint16>(Period>>16));
			}

			Master_Register.count(0);
			Slave_Register.count(0);
			Slave_Register.interrupt_flag(false);
			Master_Register.enable(true);

			//割り込み時間内だった場合
			for(unsigned int RepeatCnt=0; RepeatCnt<RepeatNum; ++RepeatCnt) {
				while(!Slave_Register.interrupt_flag());
				Master_Register.count(0);
				Slave_Register.count(0);
				Slave_Register.interrupt_flag(false);

			}

			Master_Register.enable(false);
			Slave_Register.interrupt_flag(false);
		}
	};
}

#
#endif
