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


	template< class Key, class T, class Compare = std::less<Key>,
	        class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		//friend class value_compare<Key, T, Compare, Alloc>;
	public:
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef Compare												key_compare;
		typedef ft::pair<const key_type, mapped_type>				value_type;
		//typedef value_compare<Key, T, Compare, Alloc> 	value_compare;
		typedef Alloc												allocator_type;
		typedef typename Alloc::reference&							reference;
		typedef const typename Alloc::reference&					const_reference;
		typedef typename Alloc::pointer*							pointer;
		typedef const typename Alloc::pointer*						const_pointer;
		typedef std::size_t 										size_type;
		typedef	Map_iterator<const key_type, mapped_type>			iterator;
		//typedef Map_iterator<const value_type>			const_iterator;
		typedef ft::Node											Node_;
		typedef ft::pairs											Pairs;
		typedef typename 	Alloc::template rebind<Node_ >::other	allocator_;
		typedef typename 	Alloc::template rebind<pairs >::other	allocator;


	private:
		size_type		_size;
		Node_			*node;
		allocator_type	alloc;
		allocator_ 		alloc_;
		allocator 		p_alloc;
		key_compare 	k_compare;

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
				std::cout << "Enter NULL\n";
				root_node(val);
				my_pair.first = iterator (val);
				my_pair.second = true;
				return my_pair;
			}
			if (val.first < node->pair->key)
			{
				std::cout << "Enter Left\n";
				node->left = my_insert(node->left, val);
			}
			else if (val.first > node->pair->key)
			{
				std::cout << "Enter Right\n";
				node->right = my_insert(node->right, val);
			}
			my_pair.first = iterator (val);
			my_pair.second = true;
			return my_pair;
		}
		void 	printTree(Node* root, std::string indent, bool last)
		{
			if (root != nullptr) {
				std::cout << indent;
				if (last) {
					std::cout << "R----";
					indent += "   ";
				} else {
					std::cout << "L----";
					indent += "|  ";
				}
				std::cout << root->pair->key << std::endl;
				printTree(root->left, indent, false);
				printTree(root->right, indent, true);
			}
		}

		iterator	begin()
		{

		}

		~map()
		{
			printTree(node, "", false);
			alloc_.deallocate(node, sizeof (Node_));
		}

	private:

		int max(int a, int b)
		{
			return ((a > b) ? a : b);
		}
		int height(Node_ *node)
		{
			if (node == NULL)
				return 0;
			return node->height;
		}

		int balanc_factor(Node_ *node)
		{
			if (node == NULL)
				return 0;
			return height(node->left) - height(node->right);
		}
		void root_node(const value_type& val)
		{
			node =	alloc_.allocate(1);
			node->pair = p_alloc.allocate(1);
			node->pair->key = val.first;
			node->height = 0;
			node->left = NULL;
			node->right	=	NULL;
			node->pair->value = val.second;
		}

		Node_*	new_node(const value_type& val)
		{
			Node_ *_node =  alloc_.allocate(sizeof (Node_));
			_node->pair =	p_alloc.allocate(sizeof (Pairs));
			_node->pair->key = val.first;
			_node->height = 1;
			_node->left = NULL;
			_node->right	=	NULL;
			_node->pair->value = val.second;
			return _node;
		}

		Node_*	my_insert(Node_* node, const value_type& val)
		{
			int balance;
			if (node == NULL)
				return (new_node(val));
			if (val.first < node->pair->key)
				node->left = my_insert(node->left, val);
			else if (val.first > node->pair->key)
				node->right = my_insert(node->right, val);
			else
				return node;
			node->height = 1 + max(height(node->left), height(node->right));
			balance = balanc_factor(node);
			if (balance > 1)
			{
				if (val.first < node->left->pair->key) {
					return right_rotate(node);
				} else if (val.first > node->left->pair->key) {
					node->left = left_rotate(node->left);
					return right_rotate(node);
				}
			}
			if (balance < -1)
			{
				if (val.first > node->right->pair->key) {
					return left_rotate(node);
				} else if (val.first < node->right->pair->key) {
					node->right = right_rotate(node->right);
					return left_rotate(node);
				}
			}
			return node;
		}

		Node_*		right_rotate(Node_* x)
		{
			Node_ *y = x->left;
			Node_ *T2 = y->right;
			y->right = x;
			x->left = T2;
			x->height = max(height(x->left),
							height(x->right)) +
						1;
			y->height = max(height(y->left),
							height(y->right)) +
						1;
			return y;
		}

		Node_*	left_rotate(Node_* x)
		{
			Node_ *y = x->right;
			Node_ *T2 = y->left;
			y->left = x;
			x->right = T2;
			x->height = max(height(x->left),
							height(x->right)) +
						1;
			y->height = max(height(y->left),
							height(y->right)) +
						1;
			return y;
		}
	};
}

#endif //CONTAINERS_MAP_HPP