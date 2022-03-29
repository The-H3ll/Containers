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
#include "pair.hpp"
#include "node.hpp"

template <class T, class V>
class Map_iterator
{
public:
	typedef std::bidirectional_iterator_tag	iteratory_category;
	typedef ft::pair<T, V>							value_type;
	typedef std::ptrdiff_t 					difference_type;
	typedef ft::Node						Node_;

private:
	value_type 	*_it;
	Node_ 		*node;

public:
	Map_iterator()
	{
		// Default;
	}
	Map_iterator(value_type value)
	{
		_it = new value_type(value);
		//_it= &value;
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

	value_type 	*operator++()
	{

		return _it;
	}

	Map_iterator 	operator--()
	{
		--_it;
		return _it;
	}
};

#endif //CONTAINERS_MAP_ITERATOR_HPP
