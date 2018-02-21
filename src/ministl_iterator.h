/*
	File name: ministl_iterator.h
	Creator: Yichuan Wang
	Last Update: 2018/2/21
	Description: Iterator class
*/

/*
NOTE: 	This is an internal header, included by other miniSTL headers. 
		You should not attempt to use it directly
*/

#ifndef MINISTL_INTERNAL_ITERATOR_H
#define MINISTL_INTERNAL_ITERATOR_H

#include <iostream>

namespace ministl{
	/*
	Iterator tags
	*/
	struct input_iterator_tag{};
	struct output_iterator_tag{};
	struct forward_iterator_tag: 		public input_iterator_tag{};
	struct bidirectional_iterator_tag: 	public forward_iterator_tag{};
	struct random_access_iterator_tag: 	public bidirectional_iterator_tag{};


	/*
	Iterator base class
	*/
	template<	class Category, 
				class Tp, 
				class Difference = ptrdiff_t,
				class Pointer = Tp*,
				class Reference = Tp& >
	struct iterator_base{
		typedef Category 	iterator_category;
		typedef Tp 			value_type;
		typedef Difference	difference_type;
		typedef	Pointer		pointer;
		typedef Reference	reference;
	};

	/*
	Iterator traits exractor
	*/
	template<class Iterator>
	struct iterator_traits{
		typedef typename Iterator::iterator_category 	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef	typename Iterator::difference_type 		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	/*
	Predefined traits for native pointers
	*/
	template<class Tp>
	struct iterator_traits<Tp*>{
		typedef random_access_iterator_tag	iterator_category;
		typedef Tp 							value_type;
		typedef ptrdiff_t					difference_type;
		typedef	Tp* 						pointer;
		typedef Tp& 						reference; 
	};

	/*
	Predefined traits for constant native pointers
	*/
	template<class Tp>
	struct iterator_traits<const Tp*>{
		typedef random_access_iterator_tag	iterator_category;
		typedef Tp 							value_type;
		typedef ptrdiff_t					difference_type;
		typedef	const Tp* 					pointer;
		typedef const Tp& 					reference; 
	};

	/*
	Calculate the distance between two pointers
	*/

	template<typename InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	_internal_distance(	InputIterator first, 
						InputIterator last,
						input_iterator_tag){
		typedef typename iterator_traits<InputIterator>::difference_type difference_type;
		difference_type n=0;
		while(first!=last){
			++n;
			++first;
		}
		return n;
	}

	template<typename InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	_internal_distance(	InputIterator first, 
						InputIterator last,
						random_access_iterator_tag){
		return last-first;
	}

	template<typename InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last){
		typedef typename iterator_traits<InputIterator>::iterator_category category;
		return _internal_distance(first, last, category());
	}

	/*
	Advance the iterator by n
	*/
	template<typename InputIterator, typename Distance>
	void
	__advance(	InputIterator& itr, Distance d,
				input_iterator_tag){
		while(--d<=0)++itr;
	}

	template<typename InputIterator, typename Distance>
	void
	_internal_advance(	InputIterator& itr, Distance d,
				bidirectional_iterator_tag){
		if(d>0){
			while(--d>=0)++itr;
		}else if(d<0){
			while(++d<=0)--itr;
		}else return;
	}

	template<typename InputIterator, typename Distance>
	void
	_internal_advance(	InputIterator& itr, Distance d,
				random_access_iterator_tag){
		itr += d;
	}

	template<typename InputIterator, typename Distance>
	void
	advance(InputIterator& itr, Distance d){
		_internal_advance(itr, d, iterator_traits<InputIterator>::iterator_category);
	}
}
#endif