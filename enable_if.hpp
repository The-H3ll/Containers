//
// Created by Mouaad Labhairi on 3/13/22.
//

#ifndef CONTAINERS_ENABLE_IF_HPP
#define CONTAINERS_ENABLE_IF_HPP


#include <memory>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stdexcept>

namespace ft {

	template<bool Cond, class T = void >
	struct enable_if {};

	template< class T>
	class enable_if <true, T> {
	public:
		typedef T type;
	};

}
#endif //CONTAINERS_ENABLE_IF_HPP
