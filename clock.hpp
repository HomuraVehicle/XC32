#ifndef XC32LIB_CLOCK_INC
#define XC32LIB_CLOCK_INC
#include <XC32Lib_config.hpp>
#include <device_include.h>
//#define HMLIB_NOLIB
#ifndef XC32LIB_DEBUGMODE
//#	include <peripheral/timer.h>
#endif
#include<XCBase/type.hpp>
#include<XCBase/lock.hpp>


//******* 必ず必要な初期化関数 ******
//一番初めに必ずオシレータのクロック指定が必要
//クロック自体は、コンフィギュレーションビットで指定
//あくまでも、クロックを設定するのではなく、ただ関数にクロックを教えているだけであることに注意！！
namespace xc32{
	using namespace xc;
	namespace oscillator{
		struct mutex{
		private:
			bool IsLock;
		public:
			mutex() :IsLock(false){}
		public:
			bool lock(){
				if(is_lock())return false;

				__asm("nop");
				//lock code1 0xAA996655,lock code2 0x556699AA 以外の数字を入れることでロックする
				SYSKEY = 0x00;
				__asm("nop");
				//lock code1 0xAA996655 を入れる
				SYSKEY = 0xAA996655;
				__asm("nop");
				//lock code2 0x556699AAを入れる
				SYSKEY = 0x556699AA;
				__asm("nop");
				//unlock

				IsLock = true;
				return false;
			}
			bool is_lock()const{ return IsLock; }
			void unlock(){
				if(!is_lock())return;

				__asm("nop");
				//lock code1 0xAA996655,lock code2 0x556699AA 以外の数字を入れることでロックする
				SYSKEY = 0x00;

				IsLock = false;
			}
		};//}Mutex;
		extern mutex Mutex;
		typedef xc::lock_guard<mutex> lock_guard;
		typedef xc::unique_lock<mutex> unique_lock;
	}
	namespace clock_div {
#if defined(XC32LIB_PIC32MX)
		enum type {
			div1=0,
			div2=1,
			div4=2,
			div8=3
		};
#elif defined(XC32LIB_PIC32MZ)
		enum type {
			div1=0,
			div2=1,
			div4=3,
			div8=7,
			div16=15,
			div32=31,
			div64=63,
			div128=127
		};
#else
#	error unknow device!
#endif
	}
	struct clock_block{
	private:
		static uint64 SystemClock;
		static clock_div::type BusDiv;
	public:
		bool IsLock;
		uint64 RequestSystemClock;
		clock_div::type RequestBusDiv;
	public:
		clock_block()
			: IsLock(false)
			, RequestSystemClock(10000000)	//1MHz
			, RequestBusDiv(clock_div::div8){
		}
	public:
		void config(uint64 Hz_, clock_div::type Div_ = clock_div::div8){
			RequestSystemClock = Hz_;
			RequestBusDiv = Div_;
		}
		bool lock(uint64 Hz_, clock_div::type Div_ = clock_div::div8){
			config(Hz_, Div_);
			return lock();
		}
		bool lock(){
			if(is_lock())return false;
			initialize(RequestSystemClock, RequestBusDiv);
			IsLock = true;
			return false;
		}
		bool is_lock()const{return IsLock;}
		void unlock(){
			IsLock = false;
		}
	public:
		static void set_system_clock(uint64 Hz_) { SystemClock = Hz_; }
		static uint64 get_system_clock() { return SystemClock; }
		static void set_bus_div(clock_div::type Div_) {
			//oscillatorへの書き込みmutexをロック
			oscillator::lock_guard Lock(oscillator::Mutex);

#if defined(XC32LIB_PIC32MX)
			//本当はPBDIVRDYを待たなければいけないはずだが、ヘッダにレジスタ設定されていない・・・
			//while(!OSCCONbits.PBDIVRDY);
			OSCCONbits.PBDIV = static_cast<unsigned char>(Div_);
#elif defined(XC32LIB_PIC32MZ)
			//本当はPBDIVRDYを待たなければいけないはずだが、ヘッダにレジスタ設定されていない・・・
			while(!PB1DIVbits.PBDIVRDY);
			PB1DIVbits.PBDIV = static_cast<unsigned char>(Div_);
			while(!PB2DIVbits.PBDIVRDY);
			PB2DIVbits.PBDIV = static_cast<unsigned char>(Div_);
			while(!PB3DIVbits.PBDIVRDY);
			PB3DIVbits.PBDIV = static_cast<unsigned char>(Div_);
			while(!PB4DIVbits.PBDIVRDY);
			PB4DIVbits.PBDIV = static_cast<unsigned char>(Div_);
			while(!PB5DIVbits.PBDIVRDY);
			PB5DIVbits.PBDIV = static_cast<unsigned char>(Div_);
			while(!PB7DIVbits.PBDIVRDY);
			PB7DIVbits.PBDIV = static_cast<unsigned char>(Div_);
			while(!PB8DIVbits.PBDIVRDY);
			PB8DIVbits.PBDIV = static_cast<unsigned char>(Div_);
#else
#	error unknow device!
#endif
			BusDiv = Div_;
		}
		static uint64 get_bus_clock() {
#if defined(XC32LIB_PIC32MX)
			return (SystemClock >> static_cast<unsigned int>(BusDiv));
#elif defined(XC32LIB_PIC32MZ)
			return (SystemClock / (static_cast<unsigned int>(BusDiv) + 1));
#endif
		}
		static void change_cpu_clock(clock_div::type Div_) {
			//oscillatorへの書き込みmutexをロック
			oscillator::lock_guard Lock(oscillator::Mutex);

#if defined(XC32LIB_PIC32MX)
			//本当はPBDIVRDYを待たなければいけないはずだが、ヘッダにレジスタ設定されていない・・・
			//while(!OSCCONbits.PBDIVRDY);
			OSCCONbits.PBDIV = static_cast<unsigned char>(Div_);
#elif defined(XC32LIB_PIC32MZ)
			//PBCLK7がCPUに対応する
			while(!PB7DIVbits.PBDIVRDY);
			PB7DIVbits.PBDIV = static_cast<unsigned char>(Div_);
#else
#	error unknow device!
#endif
		}
	private:
		static void initialize(uint64 Hz_, clock_div::type Div_ = clock_div::div8) {
			set_system_clock(Hz_);
			set_bus_div(Div_);
#if defined(XC32LIB_PIC32MZ)

			//oscillatorへの書き込みmutexをロック
			oscillator::lock_guard Lock(oscillator::Mutex);

			__asm("nop");
			PB2DIVbits.ON = 1;
			__asm("nop");
			PB3DIVbits.ON = 1;
			__asm("nop");
			PB4DIVbits.ON = 1;
			__asm("nop");
			PB5DIVbits.ON = 1;
			__asm("nop");
			PB7DIVbits.ON = 1;
			__asm("nop");
			PB8DIVbits.ON = 1;
#endif
		}
	};
	namespace clock{
		inline void set_system_clock(uint64 Hz_) { clock_block::set_system_clock(Hz_); }
		inline uint64 get_system_clock() { return clock_block::get_system_clock(); }
		inline void set_bus_div(clock_div::type Div_) {clock_block::set_bus_div(Div_);}
		inline uint64 get_bus_clock() { return clock_block::get_bus_clock(); }
		inline void change_cpu_clock(clock_div::type Div_) {clock_block::change_cpu_clock(Div_);}
	}
}
#
#endif
