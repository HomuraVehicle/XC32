#ifndef XC32LIB_SFR_SFRREGISTERMIXIN_INC
#define XC32LIB_SFR_SFRREGISTERMIXIN_INC 100
#
namespace xc32 {
	namespace sfr {
		template<typename T>
		class sfr_register_mixin {
		private:
			typedef sfr_register_mixin<T> my_type;
		public:
			void release() {}
			operator bool()const { return true; }
		};
	}
}
#
#endif
