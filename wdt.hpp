#ifndef XC32LIB_WDT_INC
#define XC32LIB_WDT_INC 100
#
#include"sfr/wdt.hpp"
#include"exceptions.hpp"
namespace xc32{
	struct wdt{
		struct not_open_exception :public exception {
			not_open_exception() :exception(){}
			not_open_exception(unsigned int Code_) :exception(Code_) {}
		};
	private:
		sfr::wdt Register;
	public:
		bool lock(){
			if(is_lock())return false;
			if(Register.lock())return true;
			return false;
		}
		bool is_lock()const{return Register.is_lock();}
		void unlock(){
			if(!is_lock())return;
			disable();
			clear();
			Register.unlock();
		}
	public:
		void enable(){
			xc32_assert(is_lock(), not_open_exception());
			Register.enable(true);
		}
		void disable(){
			xc32_assert(is_lock(), not_open_exception());
			Register.enable(false);
		}
		bool is_enable()const{
			xc32_assert(is_lock(), not_open_exception());
			return Register.enable();
		}
		void clear(){
			xc32_assert(is_lock(), not_open_exception());
			Register.clear();
		}
	};
}
#
#endif
