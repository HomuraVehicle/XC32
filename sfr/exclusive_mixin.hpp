#ifndef XC32_SFR_EXCLUSIVEMIXIN_INC
#define XC32_SFR_EXCLUSIVEMIXIN_INC 100
#
namespace xc32 {
	namespace sfr {
		template<typename T>
		class exclusive_mixin {
		private:
			typedef exclusive_mixin<T> my_type;
		private:
			static unsigned int UsedCnt;
		public:
			static bool is_used(){ return UsedCnt>0; }
			static unsigned int used_count(){ return UsedCnt; }
			static bool unique() { return UsedCnt==1; }
		private:
			bool IsLock;
		protected:
			exclusive_mixin():IsLock(false) {}
			exclusive_mixin(const my_type& cref_): IsLock(cref_.IsLock) {if(IsLock)++UsedCnt;}
			const my_type& operator=(const my_type& cref_) {
				if(this!=&cref_) {
					IsLock=cref_.IsLock;
					if(IsLock)++UsedCnt;
				}
				return *this;
			}
			virtual ~exclusive_mixin() {if(IsLock)--UsedCnt;}
		public:
			bool is_lock()const { return IsLock; }
			bool lock() {
				if(IsLock)return false;
				if(UsedCnt)return true;

				++UsedCnt;
				IsLock=true;

				return false;
			}
			void unlock() {
				if(!IsLock)return;

				--UsedCnt;
				IsLock=false;
			}
		};
		template<typename T>
		unsigned int exclusive_mixin<T>::UsedCnt=0;
	}
}
#
#endif
