//
// Created by Mouaad Labhairi on 3/14/22.
//

#ifndef CONTAINERS_PAIR_HPP
#define CONTAINERS_PAIR_HPP


#include <memory>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stdexcept>

template <class T1, class T2>
struct pair
{
	typedef T1		first_type;
	typedef T2		second_type;

	first_type 		first;
	second_type 	second;

	pair()
	{
		first = first_type();
		second = second_type ();
	}

	template<class U, class V>
			pair(const pair<U, V>& pr)
	{

	}
};


#endif //CONTAINERS_PAIR_HPP
