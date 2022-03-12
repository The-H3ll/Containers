

#include <memory>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stdexcept>

template <class T, class Pointer = T*, class Reference = T&>
class Iterator
{
public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef difference_type  distance_type;
    typedef Pointer pointer;
    typedef Reference reference;
private:
	value_type *it;
public:
	Iterator()
	{
		std::cout << "Iterator default constructor\n";
	}
	Iterator(value_type *value)
	{
		it = value;
	}
	Iterator(const Iterator &_iter)
	{
		*this = _iter;
	}
	Iterator operator = (const Iterator &iter)
	{
		it = iter.it;
		return (it);
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
	value_type 	&operator*()
	{
		return (*it);
	}
	void operator*(value_type value)
	{
		*it = value;
	}

	value_type *operator->()
	{
		return it;
	}

	Iterator 	operator++(value_type)
	{
		it++;
		return it;
	}

	Iterator 	operator++()
	{
		++it;
		return it;
	}

	Iterator 	operator--(value_type)
	{
		it--;
		return it;
	}

	Iterator 	operator--()
	{
		--it;
		return it;
	}
	Iterator operator + (value_type value)
	{
		Iterator temp = *this;

		temp.it = temp.it + value;
		return 	temp ;
	}
	friend Iterator operator +(value_type value, Iterator iter)
	{
		iter.it = iter.it +value;
		return iter;
	}
	Iterator operator - (value_type value)
	{
		Iterator temp = *this;

		temp.it = temp.it - value;
		return 	temp ;
	}
	friend Iterator operator -(value_type value, Iterator iter)
	{
		iter.it = iter.it - value;
		return iter;
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
		if (this->it >= iter.it)
			return true;
		return false;
	}

	Iterator operator -=(value_type value)
	{
		Iterator temp = *this;

		temp.it -= value;
		return 	temp ;
	}

	Iterator operator +=(value_type value)
	{
		Iterator temp = *this;

		temp.it += value;
		return 	temp ;
	}

	value_type operator[](value_type value)
	{
		return (it[value]);
	}
};
