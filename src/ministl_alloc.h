/*
	File name: ministl_alloc.h
	Creator: Yichuan Wang
	Last Update: 2018/2/13
	Description: Memory allocation and deallocation

	Current version uses "new" for allocation and "delete" for deallocation.
	The memory management technique will be upgraded for better performance. 
	The ideas for upgrade are: memory pool, free list (list or RB-tree based)
*/

/*
NOTE: 	This is an internal header, included by other miniSTL headers. 
		You should not attempt to use it directly
*/
#ifndef MINISTL_INTERNAL_ALLOC_H
#define MINISTL_INTERNAL_ALLOC_H

#include <bits/c++config.h>
#include <new>
#include <bits/functexcept.h>
#include <bits/move.h>

namespace ministl{

using std::size_t;
using std::ptrdiff_t;

template<typename T>
	class allocator{
	public:

		//data type required by C++ standard
		typedef size_t 		size_type;
		typedef ptrdiff_t	difference_type;
		typedef T*			pointer;
		typedef const T*	const_pointer;
		typedef T&			reference;
		typedef const T& 	const_reference;
		typedef T 			value_type;

		//to create different allocator types
		template<typename U>
		struct rebind
		{typedef allocator<U> other;};

		//constructor
		allocator() throw(){}

		allocator(const allocator&) throw(){}

		template<typename U>
		allocator(const allocator<U>&) throw(){}
	
		//destructor
		~allocator() throw() {}

		//reference
		pointer
		address(reference x) const {return std::__addressof(x);}

		const_pointer
		address(const_reference x) const {return std::__addressof(x);}

		//memory allocation (ignore the hint for now)
		//n==0 doesn't violate the C++ Standard; the standard doesn't say 
		//anything about it 
		pointer
		allocate(size_type n, const void* hint=0){
			if(n > this->max_size())//too much to allocate
				std::__throw_bad_alloc();
			return static_cast<T*>(::operator new(n * sizeof(T)));
		}

		//memory deallocation
		//p cannot be a null pointer
		void 
		deallocate(pointer p, size_type){
			::operator delete(p);
		}

		size_type
		max_size() const throw(){
			//uses overflow to get upper limit
			return size_t(-1)/sizeof(T);
		}

		//construction
		//no idea why this is here given ministl_construct.h
		//should I include ministl_construct.h?
		//wierd
		void 
		construct(pointer p, const T& value){
			::new((void*) p) T(value);
		}

		//destruction
		void destroy(pointer p){
			p->~T();
		}

	};

	//allocator comparision

	template<typename T>
	inline bool
	operator==(const allocator<T>&, const allocator<T>&){
		return true;
	}

	template<typename T>
	inline bool
	operator!=(const allocator<T>&, const allocator<T>&){
		return false;
	}
}

#endif