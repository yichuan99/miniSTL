/*
	File name: ministl_construct.h
	Creator: Yichuan Wang
	Last Update: 2018/2/13
	Description: Construction and descrution of objects. (memory allocation)
*/

/*
NOTE: 	This is an internal header, included by other miniSTL headers. 
		You should not attempt to use it directly
*/

#ifndef MINISTL_INTERNAL_CONSTRUCT_H
#define MINISTL_INTERNAL_CONSTRUCT_H

#include <new>

namespace ministl{

	//CONSTRUCTION

	//Assign value of T2 value to the address of T1* p
	template<class T1, class T2>
	inline void construct(T1* p, const T2& value){
		new ((void*) p) T1(value);
	}

	//Default construction 
	template<class T1>
	inline void construct(T1* p){
		new ((void*) p) T1();
	}

	//DESTRUCTION

	//Call destructor of this type 
	template<class T>
	void destroy(T* p){
		p->~T();
	}

	/*TO-DO(after the iterator class is complete):
		Add distruction for a range of objects
			Trivial destructor detection using type traits. 
			Reference: Annotated STL Sources (STL源码剖析) p51
	*/


	//some trivial destructor cases
	void destroy(char*, char*){}
	void destroy(int*, int*){}
	void destroy(long*, long*){}
	void destroy(float*, float*){}
	void destroy(double*, double*){}
}

#endif