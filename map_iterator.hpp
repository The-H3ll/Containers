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

template <class T, class V, class Z>
class Map_iterator
{
public:
	typedef std::bidirectional_iterator_tag	iteratory_category;
	typedef ft::pair<T, V>							value_type;
	typedef std::ptrdiff_t 					difference_type;
	typedef Z						Node_;

private:
	//value_type 	*_it;
	Node_ 		*node;

public:
	Map_iterator()
	{
		// Default;
	}

	Map_iterator(const Map_iterator& mapIterator)
	{
		this->node = mapIterator.node;
	}

	Map_iterator(Node_ *node_)
	{
		node = node_;
	}

	Map_iterator operator=(const Map_iterator& mapIterator)
	{
		this->node = mapIterator.node;
		return (*this);
	}

	bool operator==(const Map_iterator& mapIterator)
	{
		if (this->node == mapIterator.node)
			return true;
		return false;
	}

	bool operator!= (const Map_iterator& mapIterator)
	{
		return !(this->_it == mapIterator._it);
	}

	value_type&	operator*()
	{
		return (*node->pair);
	}

	value_type *operator->()
	{
	//	std::cout << "Node ==> " << node->height << std::endl;
		return node->pair;
	}


	value_type 	*operator++()
	{

		return ;
	}

	Map_iterator	left_most() {
		while (node->left != NULL)
			node = node->left;
		return (*this);
	}

	void	check_value()
	{
		std::cout << "Check IN\n";
		std::cout << "Key ==> " << node->pair->first << std::endl;
		std::cout << "value ==> " << node->pair->second << std::endl;
	}

	/*Map_iterator 	operator--()
	{
		--_it;
		return _it;
	}*/
};

#endif //CONTAINERS_MAP_ITERATOR_HPP
