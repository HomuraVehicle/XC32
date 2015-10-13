#ifndef XC32_INTERRUPT_INC
#define XC32_INTERRUPT_INC 100
#
#include<XCBase/lock.hpp>
#include"sfr/interrupt.hpp"
namespace xc32 {
	namespace interrupt {
		extern unsigned int DefaultLockPriorityLv;
		struct mutex {
		public:
			mutex(){}
		public:
			unsigned int lock(unsigned int LockPriority_ = DefaultLockPriorityLv) {
				unsigned int u = sfr::interrupt::cpu_priority();
				sfr::interrupt::cpu_priority(LockPriority_);
				return u;
			}
			void unlock(unsigned int Priority_) {
				sfr::interrupt::cpu_priority(Priority_);
			}
		};
		extern mutex Mutex;
	}
}
namespace xc{
	template<>
	class lock_guard < xc32::interrupt::mutex > {
	private:
		unsigned int OriginalPriority;
		xc32::interrupt::mutex& Mx;
	private:
		lock_guard(const lock_guard&);
		const lock_guard& operator=(const lock_guard&);
	public:
		lock_guard(xc32::interrupt::mutex& Mx_)
			:Mx(Mx_){
			OriginalPriority = Mx_.lock();
		}
		~lock_guard() {
			Mx.unlock(OriginalPriority);
		}
	};
	template<>
	struct unique_lock < xc32::interrupt::mutex > {
	private:
		xc32::interrupt::mutex* ptr;
		unsigned int OriginalPriority;
	private:
		unique_lock(const unique_lock&);
		const unique_lock& operator=(const unique_lock&);
	public:
		unique_lock() :ptr(0), OriginalPriority(0) {}
		unique_lock(xc32::interrupt::mutex& Mx_, bool defer_lock_ = false)
			: ptr(&Mx_)
			, OriginalPriority(0) {
			if(!defer_lock_)OriginalPriority = ptr->lock();
		}
		~unique_lock(){ reset(); }
		operator bool() { return OriginalPriority > 0; }
		void reset() {
			if(ptr && OriginalPriority > 0)ptr->unlock(OriginalPriority);
			ptr = 0;
			OriginalPriority = 0;
		}
		void reset(xc32::interrupt::mutex& ref_) {
			reset();
			ptr = &ref_;
			OriginalPriority = ptr->lock();
		}
		bool lock() {
			if(ptr == 0 || OriginalPriority > 0)return true;
			OriginalPriority = ptr->lock();
			return true;
		}
		void unlock() {
			if(ptr == 0 || OriginalPriority == 0)return;
			return ptr->unlock(OriginalPriority);
		}
	};
}
namespace xc32{
	namespace interrupt{
		typedef xc::lock_guard<mutex> lock_guard;
		typedef xc::unique_lock<mutex> unique_lock;
		using sfr::interrupt::function;
	}
	struct interrupt_block{
	private:
		//interruptèâä˙âªä÷êî
		static void initialize() {
#ifndef XC32_DEBUGMODE
			__asm("nop");
			sfr::interrupt::enable_all();
			//			INTEnableInterrupts();
			__asm("nop");
			//multi-vector modeÇ…Ç∑ÇÈÅDÇ±ÇÍÇÇµÇ»Ç¢Ç∆äÑÇËçûÇ›Ç™ê∂ê¨Ç≥ÇÍÇ»Ç¢Ç¡Ç€Ç¢
			sfr::interrupt::multivectormode(true);
#endif
		}
	private:
		bool IsLock;
	public:
		interrupt_block() :IsLock(false){}
	public:
		bool lock(){
			if(is_lock())return true;

			initialize();
			IsLock = true;
			return false;
		}
		bool is_lock()const{ return IsLock; }
		void unlock(){ IsLock = false; }
	};
}
#
#endif
