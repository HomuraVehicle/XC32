#ifndef XC32_INTERRUPTSAFEALLOCATOR_INC
#define XC32_INTERRUPTSAFEALLOCATOR_INC 100
#
#include<memory>
#include<cstdint>
#include<cstdlib>
#include"interrupt.hpp"
namespace xc32{
	template <class T>
	class interrupt_safe_allocator {
	public:
		// �^��`
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T value_type;
		typedef interrupt_safe_allocator<T> my_type;
		// �A���P�[�^��U�^�Ƀo�C���h����
		template <class U>
		struct rebind {
			typedef interrupt_safe_allocator<U> other;
		};

		// �R���X�g���N�^
		interrupt_safe_allocator() throw() {}
		interrupt_safe_allocator(const interrupt_safe_allocator<T>&) throw() {}
		template <class U> interrupt_safe_allocator(const interrupt_safe_allocator<U>&) throw() {}
		// �f�X�g���N�^
		~interrupt_safe_allocator() throw() {}

		// �����������蓖�Ă�
		pointer allocate(size_type num, const_pointer hint = 0) {
			xc32::interrupt::lock_guard Lock(xc32::interrupt::Mutex);
			return (pointer)std::malloc(num*sizeof(T));
		}
		// ���������������
		void deallocate(pointer p, size_type num) {
			xc32::interrupt::lock_guard Lock(xc32::interrupt::Mutex);
			std::free(p);
		}

		// �����čς݂̗̈������������
		void construct(pointer p, const T& value) { new((void*)p) T(value); }
		// �������ς݂̗̈���폜����
		void destroy(pointer p) { p->~T(); }

		// �A�h���X��Ԃ�
		pointer address(reference value) const { return &value; }
		const_pointer address(const_reference value) const { return &value; }

		// �����Ă邱�Ƃ��ł���ő�̗v�f����Ԃ�
		size_type max_size() const throw() {
			return std::numeric_limits<size_t>::max() / sizeof(T);
		}
		friend bool operator==(const my_type& My1_, const my_type& My2_) {
			return true;
		}
		friend bool operator!=(const my_type& My1_, const my_type& My2_) {
			return false;
		}
	};
	template <>
	class interrupt_safe_allocator<void> {
	public:
		// �^��`
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef void* pointer;
		typedef const void* const_pointer;
		typedef void value_type;
		typedef interrupt_safe_allocator<void> my_type;

		// �A���P�[�^��U�^�Ƀo�C���h����
		template <class U>
		struct rebind {
			typedef interrupt_safe_allocator<U> other;
		};

		// �R���X�g���N�^
		interrupt_safe_allocator() throw() {}
		interrupt_safe_allocator(const interrupt_safe_allocator<void>&) throw() {}
		template <class U> interrupt_safe_allocator(const interrupt_safe_allocator<U>&) throw() {}
		// �f�X�g���N�^
		~interrupt_safe_allocator() throw() {}

		// �����������蓖�Ă�
		pointer allocate(size_type num, interrupt_safe_allocator<void>::const_pointer hint = 0) {
			xc32::interrupt::lock_guard Lock(xc32::interrupt::Mutex);
			return (pointer)std::malloc(num);
		}
		// ���������������
		void deallocate(pointer p, size_type num) {
			xc32::interrupt::lock_guard Lock(xc32::interrupt::Mutex);
			std::free(p);
		}
		// �����Ă邱�Ƃ��ł���ő�̗v�f����Ԃ�
		size_type max_size() const throw() {
			return INT_MAX;
		}
		friend bool operator==(const my_type& My1_, const my_type& My2_) {
			return true;
		}
		friend bool operator!=(const my_type& My1_, const my_type& My2_) {
			return false;
		}
	};
}
#
#endif
