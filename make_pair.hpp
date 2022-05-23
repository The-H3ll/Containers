//
// Created by Mouaad Labhairi on 4/5/22.
//

#ifndef CONTAINERS_MAKE_PAIR_HPP
#define CONTAINERS_MAKE_PAIR_HPP

#include "pair.hpp"

namespace ft
{
	template	<class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1,T2>(x, y));
	}
}


#endif //CONTAINERS_MAKE_PAIR_HPP
