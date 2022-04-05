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

//private:
	value_type 	*_it;
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

	Map_iterator( value_type *value)
	{
//		this->node->pair = value;
		_it = value;
	}

	Map_iterator(Node_ *node_)
	{
		node = node_;
	}

	Map_iterator	operator=(const value_type *value)
	{
		return (*this);
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
		return !(this->node == mapIterator.node);
	}

	value_type 	return_pair()
	{
		return (*node->pair);
	}

	value_type&	operator*()
	{
		return (*node->pair);
	}

	value_type *operator->()
	{
		return node->pair;
	}


	Map_iterator	*operator++(int)
	{
		Node_ *tmp = right_most();

		if (tmp->pair->first == node->pair->first)
			node = node->right;
		else if (node->right != NULL)
			node = node->right;
		else if (node->parent != NULL && node->pair->first < node->parent->pair->first)
			node = node->parent;
		else if (node->parent != NULL && node->pair->first > node->parent->pair->first && node->parent->parent != NULL)
			node = node->parent->parent;
		return (this);
	}

	Map_iterator	*operator++()
	{
		Node_ *tmp = right_most();

		if (tmp->pair->first == node->pair->first)
			node = node->right;
		else if (node->right != NULL)
			node = node->right;
		else if (node->parent != NULL && node->pair->first < node->parent->pair->first)
			node = node->parent;
		else if (node->parent != NULL && node->pair->first > node->parent->pair->first && node->parent->parent != NULL)
			node = node->parent->parent;
		else
			node = node->right;
		return (this);
	}

	Map_iterator	left_most() {
		while (node->left != NULL) {
			//std::cout << "Node ==> " << node->pair->first << std::endl;
			node = node->left;
		}
		return (*this);
	}

	Node_ *right_most()
	{
		Node_ *tmp = go_root();
		while (tmp->right != NULL)
			tmp = tmp->right;
		return (tmp);
	}

	Map_iterator	after_right_most()
	{
		while (node->right != NULL)
		{
			node = node->right;
		}
		node = node->right;
		return (*this);
	}

	Node_*	go_root()
	{
		Node_ *tmp;

		tmp = node;
		while (tmp->parent != NULL)
			tmp = tmp->parent;
		return tmp;
	}

	void	check_value()
	{
		std::cout << "Check IN\n";
		std::cout << "Key ==> " << node->pair->first << std::endl;
		std::cout << "value ==> " << node->pair->second << std::endl;
	}

	Map_iterator 	*operator--()
	{

		if (node->left != NULL)
		{
			node = node->left;
			if (node->right != NULL)
				node = node->right;
			return (this);
		}
		if (node->parent != NULL && node->pair->first > node->parent->pair->first)
		{
			node = node->parent;
			return (this);
		}
		return (this);
	}

	Map_iterator 	*operator--(int)
	{

		if (node->left != NULL)
		{
			node = node->left;
			if (node->right != NULL)
				node = node->right;
			return (this);
		}
		if (node->parent != NULL && node->pair->first > node->parent->pair->first)
		{
			node = node->parent;
			return (this);
		}
		return (this);
	}
};

#endif //CONTAINERS_MAP_ITERATOR_HPP
