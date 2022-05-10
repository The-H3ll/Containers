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

template <class T, class Z, class Pointer=T*, class Reference=T&>
class Map_iterator
{
public:
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef T							value_type;
	typedef Map_iterator<const T, Z>    const_iterator;
	typedef std::ptrdiff_t 					difference_type;
	typedef Z						Node_;
	typedef Pointer							pointer;
	typedef Reference						reference;

//private:
	Node_ 		*node;
	Node_ 		*end;

public:
	Map_iterator()
	{
		// Default;
	}

	operator const_iterator()
	{
		return (this->node);
	}



	Map_iterator(Node_ *node)
	{
		this->node = node;
	}

	Map_iterator(Node_ *node, Node_* end)
	{
		this->node = node;
		this->end = end;
	}

	Map_iterator(const Map_iterator& mapIterator)
	{
		this->node = mapIterator.node;
		this->end = mapIterator.end;
	}


	Node_*	return_node()
	{
		return node;
	}

	Map_iterator& operator=(const Map_iterator& mapIterator)
	{
		this->node = mapIterator.node;
		this->end = mapIterator.end;
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

	reference	operator*() const
	{
		return (*node->pair);
	}

	pointer operator->()const
	{
		return &(operator*());
	}


	Map_iterator	operator++(int)
	{
		Map_iterator temp = *this;
		++(*this);
		return (temp);
	}


	Map_iterator&	operator++()
	{
			//  std::cout << "HEEELLLO\n";
			//   std::cout << go_root()->pair->first << std::endl;
			//  if (go_root()->parent == NULL)
			//  	std::cout << "Yes\n";
		if (node->right != NULL  && node->pair->first != go_root()->pair->first )
		{
			// std::cout << "Here\n";
			node = node->right;
			if (node->left)
			 	node = left_most(node);
		}
		else if (node->parent != NULL && node->pair && node->pair->first < node->parent->pair->first && node->pair->first != go_root()->pair->first)
			node = node->parent;
		else if (node->parent != NULL && node->pair && node->pair->first > node->parent->pair->first && node->parent->parent != NULL&& node->pair->first != go_root()->pair->first)
		{
			Node_ *temp = node;
			while (node->pair->first != go_root()->pair->first)
			{
				//std::cout << "Temp " << temp->pair->first << " || " << node->pair->first << std::endl;
				if (temp->pair->first < node->pair->first)
					return *this;
				else
					node = node->parent;
			}
				if (temp->pair->first < node->pair->first)
					return *this;
			//node = node->parent->parent;
		}
		else if (node->pair && node->pair->first == go_root()->pair->first)
		{
			node = left_most(node->right);
		}
		return (*this);
	}

	Map_iterator	left_most() {
		if (node)
		{
			while (node->left != NULL && node->left != end )
			{
				node = node->left;
			}
		}
		return (*this);
	}

	const Map_iterator	left_most() const{
		if (node)
		{
			while (node->left != NULL && node->left != end) {
				node = node->left;
			}
		}
		return (*this);
	}

	Node_ *	left_most(Node_* node) {
		if (node)
		{
			while (node->left != NULL) {
				node = node->left;
			}
		}
		return (node);

	}

	Node_ *right_most(Node_* node)
	{
		if (node)
		{
			while (node->right != NULL)
				node = node->right;
		}
		return node;
	}



	Map_iterator	after_right_most()
	{
//		while (node->right != NULL)
//		{
//			node = node->right;
//		}
//		node = node->right;
		return (*this);
	}

	const Map_iterator	after_right_most() const
	{
//		while (node->right != NULL)
//		{
//			node = node->right;
//		}
//		node = node->right;
		return (*this);
	}

	Node_*	go_root()
	{
		Node_ *tmp;

		if (node)
		{
			tmp = node;
			while (tmp->parent != NULL)
			{
				//std::cout << "Tmp ==> " << tmp->pair->first << std::endl;
				tmp = tmp->parent;
			}
			return tmp;
		}
		return NULL;
	}

	Map_iterator&	operator--()
	{
	
		if (node->left != NULL /*&& node->left != end*/)
		{
			node = node->left;
			if (node != end && node->right != NULL)
				node = right_most(node->right);

		}
		else if (node->parent != NULL && node->pair != NULL && node->pair->first > node->parent->pair->first)
		{
			node = node->parent;
		}
		else if (node->parent != NULL &&node->pair != NULL && node->pair->first < node->parent->pair->first && node->parent->parent != NULL)
		{
			Node_ *temp = node;
			while (node->pair->first != go_root()->pair->first)
			{
				//std::cout << "Temp " << temp->pair->first << " || " << node->pair->first << std::endl;
				if (temp->pair->first > node->pair->first)
					return *this;
				else
					node = node->parent;
			}
			 if (temp->pair->first > node->pair->first)
			 	return *this;
			// std::cout << "PAAAIR " << node->pair->first << std::endl;
			if (node->left != NULL && node->left != end)
			{
				// std::cout << "ENNN" << node;
				node = node->left;
				if (node->right != NULL)
					node = node->right;
			}
		}
		else if (node->parent != NULL && node->pair == NULL && node->right == NULL && node->left == NULL)
			node =node->parent;
		return (*this);
	}

	Map_iterator 	operator--(int)
	{
		Map_iterator temp = *this;
		--(*this);
	return (temp);
	}

	Map_iterator	operator-(difference_type n) const
	{
		return Map_iterator(node - n);
	}

};

#endif //CONTAINERS_MAP_ITERATOR_HPP
