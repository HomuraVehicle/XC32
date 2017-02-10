#ifndef XC32_INTERRUPTSAFEALLOCATOR_INC
#define XC32_INTERRUPTSAFEALLOCATOR_INC 100
#
#include<memory>
#include<cstdint>
#include<cstdlib>
#include"interrupt.hpp"
namespace xc32{

#ifndef _MSC_VER
	// TEMPLATE CLASS interrupt_safe_allocator
	//xc32コンパイラーの独自仕様に対応したクラス
	template<class _Ty>
	class interrupt_safe_allocator: public std::_Allocator_base<_Ty>{
	public:
		typedef std::_Allocator_base<_Ty> _Mybase;
		typedef typename _Mybase::value_type value_type;

		typedef value_type _FARQ *pointer;
		typedef value_type _FARQ& reference;
		typedef const value_type _FARQ *const_pointer;
		typedef const value_type _FARQ& const_reference;

		typedef std::_SIZT size_type;
		typedef std::_PDFT difference_type;

		template<class _Other>
		struct rebind
		{	// convert this type to interrupt_safe_allocator<_Other>
			typedef interrupt_safe_allocator<_Other> other;
		};

		pointer address(reference _Val) const
		{	// return address of mutable _Val
			return ((pointer)&(char&)_Val);
		}

		const_pointer address(const_reference _Val) const
		{	// return address of nonmutable _Val
			return ((const_pointer)&(char&)_Val);
		}

		interrupt_safe_allocator() _THROW0()
		{	// construct default allocator (do nothing)
		}

		interrupt_safe_allocator(const interrupt_safe_allocator<_Ty>&) _THROW0()
		{	// construct by copying (do nothing)
		}

		template<class _Other>
		interrupt_safe_allocator(const interrupt_safe_allocator<_Other>&) _THROW0()
		{	// construct from a related allocator (do nothing)
		}

		template<class _Other>
		interrupt_safe_allocator<_Ty>& operator=(const interrupt_safe_allocator<_Other>&)
		{	// assign from a related allocator (do nothing)
			return (*this);
		}

		void deallocate(pointer _Ptr, size_type)
		{	// deallocate object at _Ptr, ignore size
			xc32::interrupt::lock_guard Lock(xc32::interrupt::Mutex);
			::operator delete(_Ptr);
		}

		pointer allocate(size_type _Count)
		{	// allocate array of _Count elements
			xc32::interrupt::lock_guard Lock(xc32::interrupt::Mutex);
			return (std::_Allocate(_Count, (pointer)0));
		}

		pointer allocate(size_type _Count, const void _FARQ *)
		{	// allocate array of _Count elements, ignore hint
			return (allocate(_Count));
		}

		void construct(pointer _Ptr, const _Ty& _Val)
		{	// construct object at _Ptr with value _Val
			std::_Construct(_Ptr, _Val);
		}

		void destroy(pointer _Ptr)
		{	// destroy object at _Ptr
			std::_Destroy(_Ptr);
		}

		std::_SIZT max_size() const _THROW0()
		{	// estimate maximum array size
		std::_SIZT _Count = (std::_SIZT)(-1) / sizeof (_Ty);
		return (0 < _Count ? _Count : 1);
		}
	};

		// CLASS interrupt_safe_allocator<void>
	template<> class interrupt_safe_allocator<void>{
	public:
		typedef void _Ty;
		typedef _Ty _FARQ *pointer;
		typedef const _Ty _FARQ *const_pointer;
		typedef _Ty value_type;

		template<class _Other>
		struct rebind
		{	// convert this type to an interrupt_safe_allocator<_Other>
		typedef interrupt_safe_allocator<_Other> other;
		};

		interrupt_safe_allocator() _THROW0()
		{	// construct default allocator (do nothing)
		}

		interrupt_safe_allocator(const interrupt_safe_allocator<_Ty>&) _THROW0()
		{	// construct by copying (do nothing)
		}

		template<class _Other>
		interrupt_safe_allocator(const interrupt_safe_allocator<_Other>&) _THROW0()
		{	// construct from related allocator (do nothing)
		}

		template<class _Other>
		interrupt_safe_allocator<_Ty>& operator=(const interrupt_safe_allocator<_Other>&)
		{	// assign from a related allocator (do nothing)
			return (*this);
		}
	};

	template<class _Ty,class _Other>
	inline bool operator==(const interrupt_safe_allocator<_Ty>&, const interrupt_safe_allocator<_Other>&) _THROW0(){	// test for allocator equality
		return (true);
	}

	template<class _Ty,class _Other>
	inline bool operator!=(const interrupt_safe_allocator<_Ty>& _Left,const interrupt_safe_allocator<_Other>& _Right) _THROW0(){	// test for allocator inequality
		return (!(_Left == _Right));
	}
#else
	template<class _Ty>
	using interrupt_safe_allocator = std::allocator<_Ty>;
#endif
}
#
#endif
