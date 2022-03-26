//
// Created by Mouaad Labhairi on 3/14/22.
//

#ifndef CONTAINERS_MAP_HPP
#define CONTAINERS_MAP_HPP



#include <memory>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include "map_iterator.hpp"
#include "pair.hpp"
#include "node.hpp"
//#include "value_comp.hpp"

namespace ft
{

	class Node
	{
	public:
		int 	key;
		int 	height;
		Node	*right;
		Node	*left;
		int		value;
	};

	template< class Key, class T, class Compare = std::less<Key>,
	        class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		//friend class value_compare<Key, T, Compare, Alloc>;
	public:
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef Compare									key_compare;
		typedef ft::pair<const key_type, mapped_type>	value_type;
		//typedef value_compare<Key, T, Compare, Alloc> 	value_compare;
		typedef Alloc									allocator_type;
		typedef typename Alloc::reference&				reference;
		typedef const typename Alloc::reference&		const_reference;
		typedef typename Alloc::pointer*				pointer;
		typedef const typename Alloc::pointer*			const_pointer;
		typedef std::size_t 							size_type;
		typedef	Map_iterator<const key_type, mapped_type>				iterator;
		//typedef Map_iterator<const value_type>			const_iterator;
		typedef ft::Node									Node_;

	private:
		size_type	_size;
		Node_		*node;

	public:
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type())
		{
			this->_size = 0;
		}

		pair<iterator, bool > insert(const value_type& val)
		{
			ft::pair< iterator , bool> my_pair;
			if (node == NULL)
			{
				root_node(val);
				std::cout << " kEy --> " << node->key << std::endl;
				std::cout << "value --> " << node->value << std::endl;
				//Map_iterator<value_type>(my_pair.first, val);
				std::cout << "Before\n";
				my_pair.first = iterator (val);
				std::cout << "dd ==> " << my_pair.first->first <<std::endl;
				std::cout << "After\n";
				my_pair.second = true;
				return my_pair;
				std::cout << "Enter \n";
			}
			std::cout << "dkdkkd 2\n";
			if (val.first < node->key)
				node->left = my_insert(node->left, val);
			else if (val.first > node->key)
				node->right = my_insert(node->right, val);
			//Map_iterator<value_type>(my_pair.first, val);
			my_pair.first = iterator (val);
			my_pair.second = true;
			return my_pair;
		}

	private:
		void root_node(const value_type& val)
		{
			node = new Node_;
			node->key = val.first;
			node->height = 0;
			node->left = NULL;
			node->right	=	NULL;
			node->value = val.second;
		}

		Node_*	new_node(const value_type& val)
		{
			Node_ *_node =  new Node_;
			_node->key = val.first;
			_node->height = 1;
			_node->left = NULL;
			_node->right	=	NULL;
			_node->value = val.second;
			return _node;
		}

		Node_*	my_insert(Node_* node, const value_type& val)
		{
			if (node == NULL)
			{
				return (new_node(val));
			}
			if (val.first < node->key)
			{
				node->left = my_insert(node->left, val);
			}
			else if (val.first > node->key)
			{
				node->right = my_insert(node->right, val);
			}
			return node;
		}
	};
}

#endif //CONTAINERS_MAP_HPP