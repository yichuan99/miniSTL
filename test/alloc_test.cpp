/*
File name: alloc_test.cpp
Creator: Yichuan Wang
Last Update: 2018/2/13
Description: testing the ministl_alloc.h (the allocator)
*/

#include <vector>
#include <iostream>
#include "../src/ministl_alloc.h"

int main(){
	std::vector<int, ministl::allocator<int> > my_vec(4,0);
	std::cout<<my_vec.size();
	return 0;
}

