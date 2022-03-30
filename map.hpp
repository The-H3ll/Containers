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
		//typedef Map_iterator<const value_type>			const_iterator;
	private:
		class Node
		{
		public:
			value_type 	*pair;
			Node	*right;
			Node	*left;
			Node	*parent;
			int 	height;
		};
		typedef Node											Node_;
		typedef typename 	Alloc::template rebind<Node_ >::other	allocator_;
	public:
		typedef	Map_iterator<const key_type, mapped_type, Node_>			iterator;


	private:
		size_type		_size;
		Node_			*node;
		allocator_type	alloc;
		allocator_ 		alloc_;
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
				root_node(val);
				my_pair.first = iterator (node);
				my_pair.second = true;
				return my_pair;
			}
			if (val.first < node->pair->first)
			{
				node->left = my_insert(node->left, val);
				my_pair.first = iterator (node->right);
				my_pair.second = true;
			}
			else if (val.first > node->pair->first)
			{
				node->right = my_insert(node->right, val);
				my_pair.first = iterator (node->right);
				my_pair.second = true;
			}
			else
				my_pair.second = false;
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
				std::cout << root->pair->first << std::endl;
				printTree(root->left, indent, false);
				printTree(root->right, indent, true);
			}
		}

		iterator	begin()
		{
			return iterator(node).left_most();
		}

		~map()
		{
			//iterator (node).check_value();
			//printTree(node, "", false);
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
			node->pair = alloc.allocate(1);
			alloc.construct(node->pair, val);
			std::cout << "key ==> " << node->pair->first << std::endl;
			std::cout << "Value ==> " << node->pair->second << std::endl;
			node->height = 0;
			node->left = NULL;
			node->right	=	NULL;
			node->parent = NULL;
			//node->pair->second = val.second;
		}

		Node_*	new_node(const value_type &val)
		{
			Node_ *_node =  alloc_.allocate(1);
			_node->pair =	alloc.allocate(1);
			alloc.construct(_node->pair, val);
			_node->height = 1;
			_node->left = NULL;
			_node->right	=	NULL;
			//_node->parent = node
			//_node->pair->second = val.second;
			return _node;
		}

		Node_*	my_insert(Node_* node, const value_type& val)
		{
			int balance;
			if (node == NULL)
				return (new_node(val));
			std::cout << "Node ==> " << node->pair->first << std::endl;
			if (val.first < node->pair->first)
				node->left = my_insert(node->left, val);
			else if (val.first > node->pair->first)
				node->right = my_insert(node->right, val);
			else
				return node;
			node->height = 1 + max(height(node->left), height(node->right));
			balance = balanc_factor(node);
			if (balance > 1)
			{
				if (val.first < node->left->pair->first)
				{
					return right_rotate(node);
				}
				else if (val.first > node->left->pair->first)
				{
					node->left = left_rotate(node->left);
					return right_rotate(node);
				}
			}
			if (balance < -1)
			{
				if (val.first > node->right->pair->first) {
					return left_rotate(node);
				} else if (val.first < node->right->pair->first) {
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