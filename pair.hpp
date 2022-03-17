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

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef T1		first_type;
		typedef T2		second_type;

		first_type 		first;
		second_type 	second;

		// Constructors
		pair() : first(first_type()), second(second_type())
		{
		}
		template<class U, class V>
		pair(const pair<U, V>& pr) : first(pr.first)
		{
			this->second = pr.second;
		}
		pair(const first_type& a, const second_type& b)
		{
			this->first = a;
			this->second = b;
		}

		// Operator =
		pair&	operator=(const pair& pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		}

		// Relational operators
	};
	template<class T1, class T2>
	bool operator== (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	template<class T1, class T2>
	bool operator!= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(lhs == rhs);
	}
	template<class T1, class T2>
	bool operator < (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return ((lhs.first <  rhs.first) || (!(rhs.first < lhs.first) && (lhs.second < rhs.second)));
	}
	template<class T1, class T2>
	bool operator <= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(rhs < lhs);
	}
	template<class T1, class T2>
	bool operator > (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (rhs < lhs);
	}
	template<class T1, class T2>
	bool operator >= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(lhs < rhs);
	}
}


#endif //CONTAINERS_PAIR_HPP
