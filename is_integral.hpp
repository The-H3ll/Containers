//
// Created by Mouaad Labhairi on 3/13/22.
//

#ifndef CONTAINERS_IS_INTEGRAL_HPP
#define CONTAINERS_IS_INTEGRAL_HPP

#include "iterators.hpp"


template<class T>
struct check_int {
	bool ret_value() const{
		const bool t = true;
		const bool f = false;
		const char *s = typeid(T).name();
		if (strcmp(s, "i") == 0)
			return t;
		else if (strcmp(s, "l") == 0)
			return t;
		else if (strcmp(s, "d") == 0)
			return t;
		else if (strcmp(s, "x") == 0)
			return t;
		else if (strcmp(s, "b") == 0)
			return t;
		else if (strcmp(s, "Ds") == 0)
			return t;
		else if (strcmp(s, "Di") == 0)
			return t;
		else if (strcmp(s, "w") == 0)
			return t;
		else if (strcmp(s, "s") == 0)
			return t;
		return f;
	}
};

template <class T>
struct is_integral
{
	static check_int<T> o;
	static constexpr bool  x =  o.ret_value();
	static const bool value = x;
	//typedef std::integral_constant<bool, value> type;
	operator bool () const
	{
		return value ;
	}
};

#endif //CONTAINERS_IS_INTEGRAL_HPP