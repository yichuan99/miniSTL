/*
	File name: ministl_iterator.h
	Creator: Yichuan Wang
	Last Update: 2018/2/21
	Description: Iterator class

/*
NOTE: 	This is an internal header, included by other miniSTL headers. 
		You should not attempt to use it directly
*/

#ifndef MINISTL_INTERNAL_ITERATOR_H
#define MINISTL_INTERNAL_ITERATOR_H

/*
Iterator tags
*/
struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag{}:public input_iterator_tag{};
struct bidirectional_iterator_tag{}:public forward_iterator_tag{};
struct random_access_iterator_tag{}:public bidirectional_iterator_tag{};


/*
Iterator base class
*/
template<	class category, 
			class Tp, 
			class difference = ptrdiff_t,
			class pointer = Tp*,
			class reference = Tp& >
struct iterator_base{
	typedef category 	iterator_category;
	typedef Tp 			value_type;
	typedef difference	difference_type;
	typedef	pointer		pointer;
	typedef reference	reference;
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


/*
Advance the iterator by n
*/


#endif