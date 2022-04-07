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
			Node		*right;
			Node		*left;
			Node		*parent;
			int			height;
		};
		typedef Node											Node_;
		typedef typename 	Alloc::template rebind<Node_ >::other	allocator_;
	public:
		typedef	Map_iterator<const key_type, mapped_type, Node_>			iterator;
		typedef typename 	Alloc::template rebind<iterator >::other	allocator_iter;


	private:
		size_type		_size;
		allocator_iter 	iter_alloc;
		Node_			*node;
		Node_			*root;
		Node_			*temp_parent;
		Node_			*tmp;
		Node_			*temp;
		allocator_type	alloc;
		allocator_ 		alloc_;
		key_compare 	k_compare;
		int 			check;

	public:
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()): check(0)
		{
			this->_size = 0;
		}

		// Map Modifiers
		pair<iterator, bool > insert(const value_type& val)
		{
			ft::pair< iterator , bool> my_pair;
			if (node == NULL)
			{
				root_node(val);
				my_pair.first = find_key(val);
				my_pair.second = true;
				return my_pair;
			}
			if (val.first < node->pair->first)
			{
				tmp = node;

				node->left = my_insert(node->left, val);
				my_pair.first = find_key(val);
				my_pair.second = true;
			}
			else if (val.first > node->pair->first)
			{
				tmp = node;
				node->right = my_insert(node->right, val);
				my_pair.first = find_key(val);
				my_pair.second = true;
			}
			else
				my_pair.second = false;
			return my_pair;
		}

		void 	erase(iterator position)
		{
			iterator iter;

			std::cout << "Start \n";
			node = erase_node(node, position);
			while (node->parent != NULL)
				node = node->parent;
			iter = begin();
			while (iter != end())
			{
				node = upadte_height(node, iter);
				iter++;
			}
			iter = begin();
			std::cout << "Middle\n";
			while (iter != end())
			{
				node = do_rotation(node, iter);
				iter++;
			}
			std::cout << "End \n";
		}

		int count_rang(iterator first, iterator last)
		{
			int count = 0;
			while (first != last)
			{
				first++;
				count += 1;
			}
			return count;
		}

		void 	filling_iter(iterator *temp, iterator first, iterator last)
		{
			int i = 0;
			while (first != last)
			{
				temp[i] = first;
				i++;
				first++;
			}
		}

		void 	erase(iterator first, iterator last) {
			iterator iter;

			while (first != last) {
				iter = first;
				if (first != end())
					first++;
				std::cout << "SeG Here\n";
				std::cout << "Will erase ==> " << iter->first << std::endl;
				erase(iter);
				/*if (check == 1)
				{
					std::cout << "PP ==> " << first->first << std::endl;
					first--;
					std::cout << "PPoo ==> " << first->first << std::endl;
					check = 0;
				}*/
				printTree(node, "", true);
			}
		}


		size_type	erase(const key_type& k)
		{
			iterator iter;

			printTree(node, "", true);
			iter = find_key(k);
			node = erase_node(node, iter);
			while (node->parent != NULL)
				node = node->parent;
			iter = begin();
			while (iter != end())
			{
				node = upadte_height(node, iter);
				//std::cout << "Itter ==> " << iter->first << std::endl;
				iter++;
			}
			iter = begin();
			while (iter != end())
			{
				node = do_rotation(node, iter);
				iter++;
			}
			root = node;
			printTree(node, "", true);
			iter = begin();
			while (iter != end())
			{
				node = do_father(node, iter, root);
				iter++;
				//std::cout << "Iterr ==> " << iter->first << std::endl;
			}
			printTree(node, "", true);
			return (1);
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
			iterator  iter;

			iter = iterator(node).left_most();
			return iter;
		}

		iterator end()
		{
			return iterator (node).after_right_most();
		}
		~map()
		{
			//iterator (node).check_value();
			//iterator (node).left_most();
			//printTree(node, "", false);
			alloc_.deallocate(node, sizeof (Node_));
		}

	private:


		Node_*		do_father(Node_* root, iterator iter, Node_* node)
		{
			if (root == NULL)
				return NULL;
			if (iter->first < root->pair->first)
			{
				if (root->pair->first != node->pair->first)
					temp = root;
				root->left = do_father(root->left, iter,node);
			}
			else if (iter->first > root->pair->first)
			{
				if (root->pair->first != node->pair->first)
					temp = root;
				root->right = do_father(root->right, iter, node);
			}
			else
			{
				if (root->pair->first != node->pair->first)
				{
					if (root->pair->first == temp->pair->first)
						root->parent = node;
					else
						root->parent = temp;
				} else
					root->parent = NULL;
			}
			return root;
		}
		iterator  nodeWithMinimumValue(Node_ *node) {
			return (iterator(node).left_most());
		}

		Node_*		the_right_node(Node_ *node, iterator pos)
		{
			if (node == NULL)
				return NULL;
			if (pos->first < node->pair->first)
				node->left = the_right_node(node->left, pos);
			else if (pos->first > node->pair->first)
				node->right = the_right_node(node->right, pos);
			return node;
		}

		Node_*		erase_node(Node_ *root, iterator pos) {
			if (root == NULL)
				return root;
			if (pos->first < root->pair->first)
				root->left = erase_node(root->left, pos);
			else if (pos->first > root->pair->first)
				root->right = erase_node(root->right, pos);
			else {
				if ((root->left == NULL) || (root->right == NULL)) {
					std::cout << "Enter 1\n";
					std::cout << root->pair->first << std::endl;
					Node_ *temp = root->left ? root->left : root->right;
					if (temp == NULL) {
						std::cout << "Enter heree in Null\n";
						//Node *_temp = root->parent;
						temp = root;
						root = NULL;
					}
					else {

						iterator iter = find_key(temp->pair);
						root = iter.return_node();
					/*	alloc.construct(root->pair, iter.return_pair());
						root->height = temp->height;
						root->right = temp->right;
						root->left = temp->left;*/
					}
					free(temp);
				} else {
					iterator temp = iterator(root->right).left_most();//= nodeWithMinimumValue(root->right);
					check = 1;
					alloc.construct(root->pair, temp.return_pair());
				//	root = temp.return_node();
					root->right = erase_node(root->right,
											 temp);
				}
				if (root == NULL)
					return root;
				root->height = 1 + max(height(root->left),
									   height(root->right));
			}

		//	std::cout << "Finally Root => " << root->pair->first << std::endl;
			printTree(node, "", true);
			return root;
		}

		Node_*		do_rotation(Node_ *root, iterator iter)
		{
			if (root == NULL)
				return NULL;
			root->height = 1 + max(height(root->left),height(root->right));
			if (iter->first < root->pair->first)
				root->left = do_rotation(root->left, iter);
			else if (iter->first > root->pair->first)
				root->right = do_rotation(root->right, iter);
			else
			{
				int balanceFactor = balanc_factor(root);
				if (balanceFactor > 1) {
					if (balanc_factor(root->left) >= 0) {
						root = right_rotate(root);
						return root;
					}
					else {
						root->left = left_rotate(root->left);
						root = right_rotate(root);
						return root;
					}
				}
				if (balanceFactor < -1) {
					if (balanc_factor(root->right) <= 0) {
						root = left_rotate(root);
						return root;
					} else {
						root->right = right_rotate(root->right);
						root = left_rotate(root);
						return root;
					}
				}
			}
			return root;
		}

		Node_*		upadte_height(Node_* root, iterator iter)
		{
			if (root == NULL)
				return NULL;
			if (iter->first < root->pair->first)
				root->left = do_rotation(root->left, iter);
			else if (iter->first > root->pair->first)
				root->right = do_rotation(root->right, iter);
			else
				root->height = 1 + max(height(root->left),height(root->right));
			return root;
		}

		iterator 		find_key(const value_type *value)
		{
			iterator iter;

			iter = begin();
			while (iter != end())
			{
				if (iter->first == value->first)
					return iter;
				iter++;
			}
			return iter;
		}

		iterator 		find_key(const value_type &value)
		{
			iterator iter;

			iter = begin();
			while (iter != end())
			{
				if (iter->first == value.first)
					return iter;
				iter++;
			}
			return iter;
		}

		iterator 		find_key(const key_type& k )
		{
			iterator iter;

			iter = begin();
			while (iter != end())
			{
				if (iter->first == k)
					return iter;
				iter++;
			}
			return iter;
		}

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
			node->height = 0;
			node->left = NULL;
			node->right	=	NULL;
			node->parent = NULL;
		}

		Node_*	new_node(const value_type &val)
		{
			Node_ *_node =  alloc_.allocate(1);
			_node->pair =	alloc.allocate(1);
			alloc.construct(_node->pair, val);
			_node->height = 1;
			_node->left = NULL;
			_node->right = NULL;
			_node->parent = tmp;
			return _node;
		}

		Node_*	my_insert(Node_* node, const value_type& val)
		{
			int balance;

			if (node == NULL)
			{
				return (new_node(val));
			}
			if (val.first < node->pair->first)
			{
				tmp = node;
				node->left = my_insert(node->left, val);
			}
			else if (val.first > node->pair->first)
			{
				tmp = node;
				node->right = my_insert(node->right, val);
			}
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

		Node_*		right_rotate(Node_* y)
		{
//			std::cout << "Right Rotation\n";
//			std::cout << "node to rotate ==> " << y->pair->first << std::endl;
//			if (y->parent == NULL)
//				std::cout << "Parent is NULL" << std::endl;
//			else
//				std::cout << "Parent is --> "<< y->parent->pair->first << std::endl;
//			if (y->left == NULL)
//				std::cout << "Left is NULL \n";
//			else
//				std::cout << "Left is --> " << y->left->pair->first << std::endl;
//			if (y->right == NULL)
//				std::cout << "Right is NULL \n";
//			else
//				std::cout << "Right is --> " << y->right->pair->first << std::endl;
			Node_ *x = y->left;
			Node_ *T2 = x->right;
			/*if (y->parent == NULL)
			{
			//	y->parent = x;
				x->parent = NULL;
			}*/
			x->right = y;
			y->left = T2;
			x->parent = y->parent;
			y->height = max(height(y->left),
							height(y->right)) +
						1;
			x->height = max(height(x->left),
							height(x->right)) +
						1;
			if (x->right->right != NULL)
				x->right->right->parent = x->right;
			if (x->right->left != NULL)
				x->right->left->parent = x->right;
//			if (x->parent == NULL)
//				std::cout << "Parent is NULL" << std::endl;
//			else
//				std::cout << "Parent is --> "<< x->parent->pair->first << std::endl;
//			if (x->left == NULL)
//				std::cout << "Left is NULL \n";
//			else
//				std::cout << "Left is --> " << x->left->pair->first << std::endl;
//			if (x->right == NULL)
//				std::cout << "Right is NULL \n";
//			else
//				std::cout << "Right is --> " << x->right->pair->first << std::endl;
			return x;
		}

		Node_*	left_rotate(Node_* x)
		{
			Node_ *y = x->right;
			Node_ *T2 = y->left;
			y->left = x;
			if (x->parent == NULL)
			{
				x->parent = y;
				y->parent = NULL;
			}
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