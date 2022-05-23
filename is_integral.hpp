//
// Created by Mouaad Labhairi on 3/13/22.
//

#ifndef CONTAINERS_IS_INTEGRAL_HPP
#define CONTAINERS_IS_INTEGRAL_HPP


#include <memory>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <math.h>
#include <type_traits>

namespace ft
{
	template <class T>
	class is_integral
	{
	public:
		static const int value = false;
		operator bool () const
		{
			return value ;
		}
	};
	template<>
	class is_integral<char>
	{
	public:
		static const int value = true;
		operator bool () const
		{
			return value ;
		}
	};
	template<>
	class is_integral<signed char >
	{
	public:
		static const int value = true;
		operator bool () const
		{
			return value ;
		}
	};
	template<>
	class is_integral<unsigned char>
	{
	public:
		static const int value = true;
		operator bool () const
		{
			return value ;
		}
	};
	template<>
	class is_integral<wchar_t>
	{
	public:
		static const int value = true;
		operator bool () const
		{
			return value ;
		}
	};
	template<>
	class is_integral<char16_t>
	{
	public:
		static const int value = true;
		operator bool () const
		{
			return value ;
		}
	};

	template<>
	class is_integral<char32_t>
	{
	public:
		static const int value = true;
		operator bool () const
		{
			return value ;
		}
	};

	template<>
	class is_integral<short>
	{
	public:
		static const int value = true;
		operator bool () const
		{
			return value ;
		}
	};

	template<>
	class is_integral<unsigned short >
	{
	public:
		static const int value = true;
		operator bool () const
		{
			return value ;
		}
	};

	template<>
	class is_integral<int>
	{
	public:
		static const int value = true;
		operator bool () const
		{
			return value ;
		}
	};

	template<>
	class is_integral<unsigned int>
	{
	public:
		static const int value = true;
		operator bool () const
		{
			return value ;
		}
	};

	template<>
	class is_integral<long>
	{
	public:
		static const int value = true;
		operator bool () const
		{
			return value ;
		}
	};

	template<>
	class is_integral<unsigned long >
	{
	public:
		static const int value = true;
		operator bool () const
		{
			return value ;
		}
	};

	template<>
	class is_integral<long long >
	{
	public:
		static const int value = true;
		operator bool () const
		{
			return value ;
		}
	};

	template<>
	class is_integral< unsigned long long >
	{
	public:
		static const int value = true;
		operator bool () const
		{
			return value ;
		}
	};
}

#endif //CONTAINERS_IS_INTEGRAL_HPP