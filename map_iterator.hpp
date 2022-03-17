//
// Created by Mouaad Labhairi on 3/17/22.
//

#ifndef CONTAINERS_MAP_ITERATOR_HPP
#define CONTAINERS_MAP_ITERATOR_HPP

#include <memory>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stdexcept>

template <class T, class Pointer = T*, class Reference = T&>
class Map_iterator
{
public:
	typedef std::bidirectional_iterator_tag	iteratory_category;
	typedef T								value_type;
	typedef std::ptrdiff_t 					difference_type;
	typedef Pointer							pointer;
	typedef Reference						reference;

private:
	value_type *_it;
public:
	Map_iterator()
	{
		// Default;
	}
	Map_iterator(value_type value)
	{
		_it= &value;
	}
	Map_iterator(const Map_iterator& mapIterator)
	{
		_it = mapIterator._it;
	}
	Map_iterator operator=(const Map_iterator& mapIterator)
	{
		this->_it = mapIterator._it;
		return (*this);
	}

	Map_iterator	operator= (const value_type& value)
	{
		*_it = value;
		return _it;
	}

	bool operator==(const Map_iterator& mapIterator)
	{
		if (this->_it == mapIterator._it)
			return true;
		return false;
	}
	bool operator!= (const Map_iterator& mapIterator)
	{
		return !(this->_it == mapIterator._it);
	}

	value_type&	operator*()
	{
		return (*_it);
	}

	value_type *operator->()
	{
		return _it;
	}

	/*Map_iterator 	operator++(value_type valueType )
	{
		valueType.
		return _it;
	}*/

	Map_iterator 	operator++()
	{
		++_it;
		return _it;
	}

	/*Map_iterator 	operator--(value_type)
	{
		_it--;
		return _it;
	}*/

	Map_iterator 	operator--()
	{
		--_it;
		return _it;
	}


};




#endif //CONTAINERS_MAP_ITERATOR_HPP
