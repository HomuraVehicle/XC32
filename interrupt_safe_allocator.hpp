#ifndef XC32_INTERRUPTSAFEALLOCATOR_INC
#define XC32_INTERRUPTSAFEALLOCATOR_INC 100
#
#include<memory>
#include<cstdint>
#include<cstdlib>
#include"interrupt.hpp"
namespace xc32{
	template <class T>
	class interrupt_safe_allocator{
		typedef std::allocator<T> my_allocator;
	public:
		// 型定義	
		typedef typename my_allocator::size_type size_type;
		typedef typename my_allocator::difference_type difference_type;
		typedef typename my_allocator::pointer pointer;
		typedef typename my_allocator::const_pointer const_pointer;
		typedef typename my_allocator::reference reference;
		typedef typename my_allocator::const_reference const_reference;
		typedef typename my_allocator::value_type value_type;
		// アロケータをU型にバインドする
		template <class U>
		struct rebind{
			typedef interrupt_safe_allocator<U> other;
		};
	private:
		my_allocator Allocator;
	public:
		// コンストラクタ
		interrupt_safe_allocator() throw(){}
		interrupt_safe_allocator(const interrupt_safe_allocator<T>&) throw(){}
		template <class U> interrupt_safe_allocator(const interrupt_safe_allocator<U>&) throw(){}
		// デストラクタ
		~interrupt_safe_allocator() throw(){}

		// メモリを割り当てる
		pointer allocate(size_type num){
			xc32::interrupt::lock_guard Lock(xc32::interrupt::Mutex);
			return Allocator.allocate(num);
		}
		// メモリを割り当てる
		pointer allocate(size_type num, const_pointer hint){
			xc32::interrupt::lock_guard Lock(xc32::interrupt::Mutex);
			return Allocator.allocate(num, hint);
		}
		// メモリを解放する
		void deallocate(pointer p, size_type num){
			xc32::interrupt::lock_guard Lock(xc32::interrupt::Mutex);
			Allocator.deallocate(p, num);
		}

		// 割当て済みの領域を初期化する
		void construct(pointer p, const T& value){ Allocator.construct(p, value); }
		// 初期化済みの領域を削除する
		void destroy(pointer p){ Allocator.destroy(p); }

		// アドレスを返す
		pointer address(reference value) const{ return Allocator.address(value); }
		const_pointer address(const_reference value) const{ return Allocator.address(value); }

		// 割当てることができる最大の要素数を返す
		size_type max_size() const throw(){
			return Allocator.max_size();
		}
		friend bool operator==(const interrupt_safe_allocator<T>& My1_, const interrupt_safe_allocator<T>& My2_){
			return My1_.Allocator == My2_.Allocator;
		}
		friend bool operator!=(const interrupt_safe_allocator<T>& My1_, const interrupt_safe_allocator<T>& My2_){
			return My1_.Allocator != My2_.Allocator;
		}
	};
	template <>
	class interrupt_safe_allocator<void>{
		typedef std::allocator<void> my_allocator;
	public:
		// 型定義	
		typedef my_allocator::pointer pointer;
		typedef my_allocator::const_pointer const_pointer;
		typedef my_allocator::value_type value_type;
		// アロケータをU型にバインドする
		template <class U>
		struct rebind{
			typedef interrupt_safe_allocator<U> other;
		};
	private:
		my_allocator Allocator;
	public:
		// コンストラクタ
		interrupt_safe_allocator() throw(){}
		interrupt_safe_allocator(const interrupt_safe_allocator<void>&) throw(){}
		template <class U> interrupt_safe_allocator(const interrupt_safe_allocator<U>&) throw(){}
		// デストラクタ
		~interrupt_safe_allocator() throw(){}
		friend bool operator==(const interrupt_safe_allocator<void>& My1_, const interrupt_safe_allocator<void>& My2_){
			return My1_.Allocator == My2_.Allocator;
		}
		friend bool operator!=(const interrupt_safe_allocator<void>& My1_, const interrupt_safe_allocator<void>& My2_){
			return My1_.Allocator != My2_.Allocator;
		}
	};
}
#
#endif
