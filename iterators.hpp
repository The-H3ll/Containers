

#include <memory>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include "is_integral.hpp"


template <class T, class Pointer = T*, class Reference = T&>
class Iterator
{
public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef T								value_type;
   	typedef Iterator<const T> 				const_iterator;
    typedef std::ptrdiff_t					difference_type;
    typedef difference_type 				distance_type;
    typedef Pointer							pointer;
    typedef Reference						reference;
public:
	value_type *it;
public:
	Iterator()
	{
		it = NULL;
	}
	Iterator(value_type *value)
	{
		it = value;
	}
	Iterator(const Iterator &_iter)
	{
		it = _iter.it;
	}
	Iterator& operator = (const Iterator &iter)
	{
		it = iter.it;
		return (*this);
	}
	operator	const_iterator ()
	{
		return (this->it);
	}
	bool	operator== (const Iterator &iter)
	{
		if (it == iter.it)
			return true;
		else
			return false;
	}
	bool 	operator != (const Iterator &iter)
	{
		if (it != iter.it)
			return true;
		return false;
	}
	reference 	operator*()const
	{
		value_type *temp;

		temp = it;
		return (*temp);
	}
/* 	reference operator*(value_type value)
	{
		*it = value;
	}*/

	pointer operator->()
	{
		return &(operator*());
	}

	Iterator 	operator++(int)
	{
		Iterator temp(*this);
		++(*this);
		return (temp);
	}

	Iterator&	operator++()
	{
		++it;
		return (*this);
	}

	Iterator 	operator--(int)
	{
		Iterator temp(*this);
		--(*this);
		return (temp);
	}

	Iterator& 	operator--()
	{
		--it;
		return (*this);
	}
	Iterator operator + (difference_type value)const
	{
//		Iterator temp = *this;
//
//		temp.it = temp.it + value
		return 	Iterator(it + value) ;
	}
	friend Iterator operator +(difference_type value, Iterator iter)
	{
//		Iterator temp = iter;
//		temp.it = temp.it +value;
		return Iterator(iter.it + value);
	}
	Iterator operator - (difference_type value)const
	{
//		Iterator temp = *this;
//
//		temp.it = temp.it - value;
		return 	Iterator(it - value) ;
	}
	bool  operator <(Iterator iter)
	{
		if (this->it < iter.it)
			return true;
		return false;
	}
	bool  operator >(Iterator iter)
	{
		if (this->it > iter.it)
			return true;
		return false;
	}
	bool  operator >=(Iterator iter)
	{
		if (this->it >= iter.it)
			return true;
		return false;
	}
	bool  operator <=(Iterator iter)
	{
		if (this->it <= iter.it)
			return true;
		return false;
	}

	Iterator& operator -=(difference_type value)
	{
		it -= value;
		return 	*this ;
	}

	Iterator& operator +=(difference_type value)
	{

		it += value;
		return *this;
	}

	reference operator[](difference_type value) const
	{
		return (it[value]);
	}
};

template <class Iterators>
typename Iterator<Iterators>::difference_type operator- (
		const Iterator<Iterators>& lhs,
		const Iterator<Iterators>& rhs)

{
	return (lhs.it - rhs.it);
}
