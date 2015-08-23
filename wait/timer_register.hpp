#ifndef XC32_TIMERREGISTER_INC
#define XC32_TIMERREGISTER_INC
#
#include"sfr/interrupt.hpp"
namespace xc32 {
	struct timer_register {
	private:
		typedef sfr::interrupt interrupt;
	private:
		struct adaptor_interface {
			friend timer_register;
		public:
			virtual ~adaptor_interface() {}
		protected:
			virtual void create()=0;
			virtual void release()=0;
		protected:
			virtual bool is_lock()const=0;
			virtual bool lock()=0;
			virtual void unlock()=0;
		protected:
			virtual bool use_internal_clock() const=0;
			virtual void use_internal_clock(bool Val_)=0;
			virtual bool use_gate() const=0;
			virtual void use_gate(bool Val_)=0;
			virtual bool interrupt_flag()const=0;
			virtual void interrupt_flag(bool Val_)=0;
			virtual bool interrupt_enable()const=0;
			virtual void interrupt_enable(bool Val_)=0;
			virtual bool power()const=0;
			virtual void power(bool Val_)=0;
			virtual bool prescaller()const=0;
			virtual void prescaller(bool Val_)=0;
			virtual unsigned int period()const=0;
			virtual void period(unsigned int Val_)=0;
			virtual unsigned int count()const=0;
			virtual void count(unsigned int Val_)=0;
			virtual const interrupt* interrupt_function()const=0;
			virtual void interrupt_function(interrupt* Val_)=0;
		};
	public:
		struct builder_interface {
			virtual timer_register operator()(void)=0;
		};
	public:
		template<typename register_>
		struct builder :public builder_interface {
		private:
			typedef builder<register_> my_type;
		public:
			class adaptor :public adaptor_interface {
			protected:
				virtual void create() { ++UsedCount; }
				virtual void release() { --UsedCount; }
			protected:
				virtual bool is_lock()const { return LockCount>0; }
				virtual bool lock() {
					//確保済みならOK
					if(LockCount) {
						++LockCount;
						return false;
					}

					//確保に失敗したら、OUT
					if(my_type::Register.lock())return true;
					++LockCount;
				}
				virtual void unlock() {
					//未確保なら無視
					if(LockCount==0)return;

					//全て解放済みなら、親元開放
					--LockCount;
					if(LockCount==0)my_type::Register.unlock();
				}
			protected:
				virtual bool use_internal_clock() const { return my_type::Register.use_internal_clock(); }
				virtual void use_internal_clock(bool Val_) { my_type::Register.use_internal_clock(Val_); }
				virtual bool use_gate() const { return my_type::Register.use_gate(); }
				virtual void use_gate(bool Val_) { my_type::Register.use_gate(Val_); }
				virtual bool interrupt_flag()const { return my_type::Register.interrupt_flag(); }
				virtual void interrupt_flag(bool Val_) { my_type::Register.interrupt_flag(Val_); }
				virtual bool interrupt_enable()const { return my_type::Register.interrupt_enable(); }
				virtual void interrupt_enable(bool Val_) { my_type::Register.interrupt_enable(Val_); }
				virtual bool power()const { return my_type::Register.power(); }
				virtual void power(bool Val_) { my_type::Register.power(Val_); }
				virtual bool prescaller()const { return my_type::Register.prescaller(); }
				virtual void prescaller(bool Val_) { my_type::Register.prescaller(Val_); }
				virtual unsigned int period()const { return my_type::Register.period(); }
				virtual void period(unsigned int Val_) { my_type::Register.period(Val_); }
				virtual unsigned int count()const { return my_type::Register.count(); }
				virtual void count(unsigned int Val_) { my_type::Register.count(Val_); }
				virtual const interrupt* interrupt_function()const { return my_type::Register.interrupt_function(); }
				virtual void interrupt_function(interrupt* Val_) { my_type::Register.interrupt_function(Val_); }
			};
		private:
			static adaptor Adaptor;
			static register_ Register;
			static unsigned int UsedCount;
			static unsigned int LockCount;
		public:
			static timer_register create() {
				if(is_used())return timer_register(0);
				return timer_register(&Adaptor);
			}
			static bool is_used() { return UsedCount>0; }
			static unsigned int used_count() { return UsedCount; }
		public:
			timer_register operator()(void) { return create(); }
		};
	private:
		adaptor_interface* pRegister;
		bool IsLock;
	public:
		timer_register()
			: pRegister(0) {}
		timer_register(const timer_register& My_)
			: pRegister(My_.pRegister) {
			if(pRegister) {
				pRegister->create();
			}
		}
		const timer_register& operator=(const timer_register& My_) {
			if(this!=&My_) {
				//自分を一度空にする
				release();

				pRegister=My_.pRegister;
				//レジスタに作成を通知
				if(pRegister) {
					pRegister->create();
				}
			}
			return *this;
		}
		~timer_register() {
			release();
		}
	private:
		timer_register(adaptor_interface* pRegister_)
			: pRegister(pRegister_) {
			//レジスタに作成を通知
			if(pRegister) {
				pRegister->create();
			}
		}
	public:
		operator bool() { return pRegister!=0; }
		void release() {
			//ロック開放
			unlock();

			//レジスタに解放を通知
			if(pRegister) {
				pRegister->release();
			}

			//相手を忘れる
			pRegister=0;
		}
		bool is_lock()const { return IsLock; }
		bool lock() {
			//中身が空ならエラー
			if(pRegister)return true;

			//ロック済みならOK
			if(IsLock)return false;

			//ロック
			if(pRegister->lock())return true;
			IsLock=true;

			return false;
		}
		void unlock() {
			//中身が空なら無視
			if(pRegister)return;

			//ロック開放済みならOK
			if(!IsLock)return;

			//ロック開放
			pRegister->unlock();
			IsLock=false;
		}
		bool use_internal_clock() const { return pRegister->use_internal_clock(); }
		void use_internal_clock(bool Val_) { pRegister->use_internal_clock(Val_); }
		bool use_gate() const { return pRegister->use_gate(); }
		void use_gate(bool Val_) { pRegister->use_gate(Val_); }
		bool interrupt_flag()const { return pRegister->interrupt_flag(); }
		void interrupt_flag(bool Val_) { pRegister->interrupt_flag(Val_); }
		bool interrupt_enable()const { return pRegister->interrupt_enable(); }
		void interrupt_enable(bool Val_) { pRegister->interrupt_enable(Val_); }
		bool power()const { return pRegister->power(); }
		void power(bool Val_) { pRegister->power(Val_); }
		bool prescaller()const { return pRegister->prescaller(); }
		void prescaller(bool Val_) { pRegister->prescaller(Val_); }
		unsigned int period()const { return pRegister->period(); }
		void period(unsigned int Val_) { pRegister->period(Val_); }
		unsigned int count()const { return pRegister->count(); }
		void count(unsigned int Val_) { pRegister->count(Val_); }
		const interrupt* interrupt_function()const { return pRegister->interrupt_function(); }
		void interrupt_function(interrupt* Val_) { pRegister->interrupt_function(Val_); }
	};
	template<typename register_>
	typename timer_register::template builder<register_>::adaptor timer_register::template builder<register_>::Adaptor;
	template<typename register_>
	register_ timer_register::template builder<register_>::Register;
	template<typename register_>
	unsigned int timer_register::template builder<register_>::Count;
}
#
#endif
