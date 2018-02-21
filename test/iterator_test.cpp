/*
File name: iterator_test.cpp
Creator: Yichuan Wang
Last Update: 2018/2/21
Description: testing the ministl_iterator.h (the allocator)
*/

#include <vector>
#include <list>
#include <iostream>
#include "../src/ministl_iterator.h"

int main(){
	std::vector<int> my_vec(4,0);
	std::cout<<ministl::distance(my_vec.begin(), my_vec.end());

	return 0;
}