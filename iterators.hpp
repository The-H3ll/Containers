

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
	Iterator(const Iterator &_iter)
	{
		*this = _iter;
	}
	Iterator &operator = (const Iterator &iter)
	{
		*this = iter;
	}
	bool	operator== (const Iterator &iter)
	{
		if (this->it[0] == iter.it[0])
			return true;
		else
			return false;
	}
	bool 	operator != (const Iterator &iter)
	{
		if (this->it[0] != iter.it[0])
			return true;
		return false;
	}
	value_type 	operator*(const Iterator &iter)
	{
		return (iter.it[0]);
	}

	void	operator++(const Iterator &iter)
	{
		iter.it++;
	}

};