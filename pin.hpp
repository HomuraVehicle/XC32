#ifndef XC32LIB_PIN_INC
#define XC32LIB_PIN_INC 100
#
namespace xc32 {
	template<typename pin_register_,bool IsNegativeLogic=false,bool OpenDrain=false>
	class output_pin {
	private:
		bool IsLock;
		pin_register_ Pin;
	public:
		output_pin() :IsLock(false) {}
		~output_pin() { unlock(); }
		bool lock() {
			if(is_lock())return true;
			Pin.tris(false);
			Pin.analog(false);
			Pin.opendrain(OpenDrain);
			IsLock=true;
			return false;
		}
		bool is_lock()const { return IsLock; }
		void unlock() {
			if(!is_lock())return;
			Pin.tris(true);
			IsLock=false;
		}
		void operator()(bool val_) {
			Pin.lat(val_);
		}
	};
	template<typename pin_register_>
	class output_pin<pin_register_,true,false> {
	private:
		bool IsLock;
		pin_register_ Pin;
	public:
		output_pin() :IsLock(false) {}
		~output_pin() { unlock(); }
		bool lock() {
			if(is_lock())return true;
			Pin.tris(false);
			Pin.analog(false);
			Pin.opendrain(false);
			IsLock=true;
			return false;
		}
		bool is_lock()const { return IsLock; }
		void unlock() {
			if(!is_lock())return;
			Pin.tris(true);
			IsLock=false;
		}
		void operator()(bool val_) {
			Pin.lat(!val_);
		}
	};
	template<typename pin_register_>
	class output_pin<pin_register_,true,true> {
	private:
		bool IsLock;
		pin_register_ Pin;
	public:
		output_pin() :IsLock(false) {}
		~output_pin() { unlock(); }
		bool lock() {
			if(is_lock())return true;
			Pin.tris(false);
			Pin.analog(false);
			Pin.opendrain(true);
			IsLock=true;
			return false;
		}
		bool is_lock()const { return IsLock; }
		void unlock() {
			if(!is_lock())return;
			Pin.tris(true);
			IsLock=false;
		}
		void operator()(bool val_) {
			Pin.lat(!val_);
		}
	};
	template<typename pin_register_,bool IsNegativeLogic=false>
	class input_pin {
	private:
		bool IsLock;
		pin_register_ Pin;
	public:
		input_pin() :IsLock(false) {}
		~input_pin() { unlock(); }
		bool lock() {
			if(is_lock())return true;
			Pin.tris(true);
			Pin.analog(false);
			Pin.opendrain(false);
			IsLock=true;
			return false;
		}
		bool is_lock()const { return IsLock; }
		void unlock() {
			if(!is_lock())return;
			Pin.tris(true);
			IsLock=false;
		}
		bool operator()(void)const volatile {
			return Pin.port();
		}
	};
	template<typename pin_register_>
	class input_pin <pin_register_,true>{
	private:
		bool IsLock;
		pin_register_ Pin;
	public:
		input_pin() :IsLock(false) {}
		~input_pin() { unlock(); }
		bool lock() {
			if(is_lock())return true;
			Pin.tris(true);
			Pin.analog(false);
			Pin.opendrain(false);
			IsLock=true;
			return false;
		}
		bool is_lock()const { return IsLock; }
		void unlock() {
			if(!is_lock())return;
			Pin.tris(true);
			IsLock=false;
		}
		bool operator()(void)const volatile {
			return !Pin.port();
		}
	};
}
#
#endif
