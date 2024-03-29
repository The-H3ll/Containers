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
#include <functional>
#include "map_iterator.hpp"
#include "pair.hpp"
#include "node.hpp"
#include "make_pair.hpp"
#include "reverse_iterator.hpp"
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
		typedef Alloc												allocator_type;
		typedef typename Alloc::reference&							reference;
		typedef const typename Alloc::reference&					const_reference;
		typedef typename Alloc::pointer*							pointer;
		typedef const typename Alloc::pointer*						const_pointer;
		typedef std::size_t 										size_type;
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

		class value_compare : std::binary_function<value_type, value_type, bool>
		{
			friend class map;
		protected:
			key_compare comp;
			value_compare (key_compare c) : comp(c) {}  // constructed with map's comparison object
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};
		typedef Node														Node_;
		typedef typename 	Alloc::template rebind<Node_ >::other			allocator_;
		typedef value_compare 												value_compare;
	public:
		typedef	Map_iterator<value_type , Node_, key_compare>							iterator;
		typedef Map_iterator<const value_type, Node_, key_compare>						const_iterator;
		typedef reverse_iterator<const_iterator>							const_reverse_iterator;
		typedef reverse_iterator<iterator>									reverse_iterator;
		typedef typename 	Alloc::template rebind<iterator >::other		allocator_iter;
		typedef typename iterator_traits<iterator>::difference_type 					difference_type;
		Node_			*node ;
		Node_			*ending;
		Node_			*r_ending;


	protected:
		size_type		_size;
		int				flag ;
		int 			in;
		int				rotate_true;
		Node_			*root;
		Node_			*tmp;
		Node_			*temp;
		allocator_type	alloc;
		allocator_ 		alloc_;
		key_compare 	k_compare;
		Node_*		tempi;
		Node_*			_node;

	public:

		//	Constructors
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type())
		{
			this->node = NULL;
			this->_size = 0;
			flag = 0;
			in = 0;
			k_compare = comp;
			this->alloc = alloc;
			ending = alloc_.allocate(1);
			r_ending = alloc_.allocate(1);
		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type())
		{
			this->_size = 0;
			flag = 0;
			in = 0;
			size_type count = 0;
			k_compare = comp;
			InputIterator back(r_ending);
			this->node = NULL;
			ending = alloc_.allocate(1);
			r_ending = alloc_.allocate(1);
			while (first != last)
			{
				insert(*(first++));
				//first++;
				count++;
				//if (begin() == r_ending)
					//std::cout << "Yes it is\n";	
			}
			//if (this->_size != count)
				//his->_size +=1;
			//k_compare = comp;
			this->alloc = alloc;
		}

		map (const map& x)
		{
			k_compare = x.k_compare;
			flag = 0;
			in = 0;
			this->node = NULL;
			this->_size =0;
			ending = alloc_.allocate(1);
			r_ending = alloc_.allocate(1);
			insert(x.begin(), x.end());
		}

		map& operator= (const map& x)
		{
			k_compare = x.k_compare;
			if (node != NULL)
			{
				//node = NULL;
				erase(begin(), end());
				this->_size = 0;
				this->node = NULL;
				if (!x.empty())
				{
					insert(x.begin(), x.end());
				}
				else
				{
					
					r_ending = ending;
					this->_size = 0;
				}
				return(*this);
			}
			else if (!x.empty())
			{
				erase(begin(), end());
				this->_size = 0;
				this->node = NULL;
				if (!x.empty())
					insert(x.begin(), x.end());

			}
			else if ( x.empty())
			{
				node = ending;
				this->_size = 0;
			}
			return (*this);
		}

		// Map Modifiers

		pair<iterator, bool > insert(const value_type& val)
		{
			ft::pair< iterator , bool> my_pair;
			iterator iter;
			Node_* tempo;
			
			if (node)
				tempo = node;
			
			if (node == NULL)
			{
				root_node(val);
				 my_pair.first = find_key(val);
				//my_pair.first = node->pair->first;
				my_pair.second = true;
				this->_size += 1;
				return my_pair;
			}
			else if (/*val.first < node->pair->first*/  k_compare(val.first, node->pair->first))
			{
				tmp = node;
				node->left = my_insert(node->left, val);
				tempo = node->left;
			}
			else if (/*val.first > node->pair->first*/k_compare(node->pair->first, val.first) )
			{
				tmp = node;
				node->right = my_insert(node->right, val);
				tempo = node->right;
			}
			else if (val.first == node->pair->first)
			{
				my_pair.first = iterator(tempo);
				my_pair.second = false;
				return my_pair;
			}
			if(flag == 1)
			{
				flag = 0;
				my_pair.first = iterator(tempo);
				my_pair.second = false;
				return my_pair;
			}
			my_pair.first =iterator(_node);
			my_pair.second = true;
			iter = iterator(_node);
			// printTree(node, "", true);
			if (/*value->first < node->pair->first*/k_compare(node->pair->first, val.first))
			{

				 while (iter != iterator(node) /*_node != NULL && ver != NULL*/)
				 {
				 	_node = do_rotation(_node, iter);
					_node = _node->parent;
					iter = iterator(_node);
				 }
				node = do_rotation(node, iter);
				

			}
			else if(/*value->first < node->pair->first*/k_compare(val.first, node->pair->first))
			{
				// std::cout << "ENter\n";
				iterator itera(node);
				while (itera != begin())
				{
					node = upadte_height(node, itera);
					node = do_rotation(node, iter);
					itera--;
				}
			}
			else
			{
				iterator itera (node);
				node = upadte_height(node, itera);
				node = do_rotation(node, iter);
			}
			this->_size += 1;
			// printTree(node, "", true);
			return my_pair;
		}

		iterator insert(iterator position,  const value_type& val)
		{
			position = begin();
			if (node == NULL)
			{
				root_node(val);
				this->_size += 1;
				return find_key(val);
			}
			if (/*val.first < node->pair->first*/k_compare(val.first, node->pair->first))
			{
				tmp = node;
				node->left = my_insert(node->left, val);
				//this->_size += 1;
			}
			else if (/*val.first > node->pair->first*/k_compare(node->pair->first, val.first))
			{
				tmp = node;
				node->right = my_insert(node->right, val);
				root = node;
				iterator  iter = begin();
				if (/*value->first < node->pair->first*/k_compare(val.first, node->pair->first))
				{
					while (iter != iterator(node))
					{
						node = do_father(node, iter, root);
						iter++;
				 		iter++;
					}
				}
				else if (/*value->first > node->pair->first*/k_compare(node->pair->first, val.first))
				{
					iterator itera = node;
					while (itera != end())
					{
						node = do_father(node, iter, root);
				 		itera++;
					}
				}
				else if (/*value->first == node->pair->first*/k_compare(node->pair->first, val.first) == false && k_compare(val.first, node->pair->first) == false )
				{
					iter = iterator(node);
					node = do_father(node, iter, root);
				}
				// while (iter != end())
				// {
				// 	node = do_father(node, iter, root);
				// 	iter++;
				// }
			}
			if (flag == 0)
				this->_size += 1;
			return find_key(val);
		}
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}
		void 	erase(iterator position)
		{
			iterator iter;
			iterator itera;
			Node_* tt = position.return_node();
			if (tt->parent == NULL)
			{
				if (tt->right->left)
				{
					
					itera = iterator(tt->right).left_left();
				}
				else if (tt->left)
				{
					if (tt->left == r_ending)
					{
						itera = iterator(tt->right);
					}
					else
						itera = iterator(tt->left);
				}
				tt = itera.return_node();
			}
			else
				tt = tt->parent;

			// printTree(node, "", true);
			node = erase_node(node, position);
			// printTree(node, "", true);
			this->_size -= 1;
			if (node && this->_size > 0)
			{
				root = node;
				iter = iterator(tt);
				while (iter != iterator(node) && tt->parent != NULL)
				{
					node = do_rotation(node, iter);
					tt = tt->parent;
					iter = iterator(tt);
				}
			}
		}

		void 	erase(iterator first, iterator last) {
			iterator iter;

			if (this->_size == 0)
				return ;
			while (first != last)
			{
				iter = first;
				first++;
				if (first != last)
				{
					if (iter->first == first->first)
					{
						break;
					}
				}
				erase(iter);
			}
		}
		size_type	erase(const key_type& k)
		{
			iterator iter;
			iter = find_key(k);
			if (in == 1)
				{
					in = 0;
					return 0;
				}
			// printTree(node, "", true);
			node = erase_node(node, iter);
			this->_size -= 1;
			if (node && this->_size > 0)
			{
				root = node;
				iter = begin();
				while (iter != end())
				{
					node = do_rotation(node, iter);
					iter++;
				}
			}
			return (1);
		}

		void 		clear()
		{
			iterator iter = begin();
			erase(iter, end());
			node = NULL;
			this->_size = 0;
		}
		void	swap(map& x)
		{
			map holo;
			size_type save_size = this->_size;
			Node_* save_last_element = this->ending;
			Node_* save_last_rev = this->r_ending;
			Node_*	save_node = this->node;
			this->_size = x.size();
			this->ending = x.ending;
			this->r_ending = x.r_ending;
			this->node = x.node;

			x._size = save_size;
			x.node = save_node;
			x.ending = save_last_element;
			x.r_ending = save_last_rev;
			
			
		}
		//		Iterators

		iterator	begin()
		{
			if (node == NULL)
				return end();
			iterator  iter(r_ending, r_ending);

			return iter.left_most();
		}
		const_iterator	begin() const
		{
			if (node == NULL)
				return end();
			const_iterator  iter(r_ending, r_ending);

			return iter.left_most();
		}
		iterator end()
		{
			iterator iter(ending, r_ending);

			return iter.after_right_most();
		}

		const_iterator end() const
		{
			const_iterator ite(ending, r_ending);

			return ite.after_right_most();
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(end()));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(end()));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(begin()));
		}
		const_reverse_iterator rend() const {
			return (const_reverse_iterator(begin()));
		}

			//	Element Access
		mapped_type&	operator[] (const key_type& k)
		{
			return ((*((this->insert(ft::make_pair(k,mapped_type()))).first)).second);
		}

		pair<iterator, iterator>		equal_range(const key_type& k)
		{
			iterator  iter = begin();

			while (iter != end())
			{
				if (k_compare(iter->first, k) == false && k_compare(k, iter->first) == false)
					return (ft::make_pair(lower_bound(iter->first), upper_bound(iter->first)));
				iter++;
			}
			return (ft::make_pair(upper_bound(k), upper_bound(k)));
		}

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			const_iterator  iter = begin();

			while (iter !=  end())
			{
				if (k_compare(iter->first, k) == false && k_compare(k, iter->first) == false)
					return (ft::make_pair(lower_bound(iter->first), upper_bound(iter->first)));
				iter++;
			}
			return (ft::make_pair(upper_bound(k), upper_bound(k)));
		}

		//	Capacity

		bool empty() const
		{
			if(this->_size == 0)
				return true;
			return false;
		}
		size_type size() const
		{
			return this->_size;
		}
		size_type max_size() const
		{
			return alloc_.max_size();
		}

		// Observers
		value_compare value_comp() const
		{
			value_compare	val((key_compare()));
			return (val);
		}

		key_compare key_comp() const
		{
			return (key_compare());
		}

		// Operations
		iterator find(const key_type& k)
		{
			 iterator iter;
			 Node_* root = node;

			// if (k_compare)
			while (root && root != ending)
			{
				iter = iterator(root);
				if (k_compare(k, iter->first) == false && k_compare(iter->first, k) == false)
					return iter;
				
				if (/*k < node->pair->first*/k_compare(k, root->pair->first))
					root = root->left;
				else
					root = root->right;

			}
			return end();
		}
		const_iterator find(const key_type& k)const
		{
			 const_iterator iter;
			 Node_* root = node;

			// if (k_compare)
			while (root && root != ending)
			{
				iter = iterator(root);
				if (k_compare(k, iter->first) == false && k_compare(iter->first, k) == false)
					return iter;
				
				if (/*k < node->pair->first*/k_compare(k, root->pair->first))
					root = root->left;
				else
					root = root->right;

			}
			return end();
		}
		size_type count(const key_type& k) const
		{
			const_iterator iter = find(k);
			if (iter != end())
				return 1;
			return 0;
		}
		iterator lower_bound(const key_type& k)
		{
			iterator iter ;
			iterator fin = end();
			if (k_compare(node->pair->first, k))
				 iter = iterator(node);
			else
				iter = begin();
			while (iter != fin && key_comp()(iter->first, k))
			{
				iter++;
			}

			return  iter;
		}
		const_iterator lower_bound(const key_type& k) const
		{
			const_iterator  iter;

			if (k_compare(node->pair->first, k))
				 iter = iterator(node);
			else
				iter = begin();
			while (iter != end() && key_comp()(iter->first, k))
			{
				iter++;
			}
			return  iter;
		}

		iterator upper_bound(const key_type& k)
		{
			iterator  iter;

			if (k_compare(node->pair->first, k))
				 iter = iterator(node);
			else
				iter = begin();
			while (iter != end())
			{
				if (key_comp()(k, iter->first))
					break;
				iter++;
			}
			return  iter;
		}

		const_iterator upper_bound(const key_type& k) const
		{
			const_iterator  iter;
			if (k_compare(node->pair->first, k))
				 iter = iterator(node);
			else
				iter = begin();
			while (iter != end())
			{
				if (key_comp()(k, iter->first))
					break;
				iter++;
			}
			return  iter;
		}
		
		//Allocator
		allocator_type get_allocator() const
		{
			return alloc;
		}


		~map()
		{
			if (this->_size > 0 && node)
			{
			
				 clear();
				 this->_size = 0;
				 alloc_.deallocate(r_ending, 1);
				alloc_.deallocate(ending, 1);
				node = NULL;
			}

		}

	private:

		iterator 	return_begin()
		{
			iterator iter(r_ending);
			return iter.after_right_most();
		}
		const_iterator 	return_begin() const
		{
			const_iterator iter(r_ending);
			return iter.after_right_most();
		}

		void	free_node()
		{
			 node = NULL;
			// // iterator  start = begin();
			// // iterator  ends= end();
			// erase(begin(), end());
		}
		void 	printTree(Node* root, std::string indent, bool last) const
		{
			if (root != nullptr && root != ending && root != r_ending) {
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

		Node_* 		do_father(Node_* root, iterator iter, Node_* node)
		{
			if (root == NULL)
				return NULL;
			if (root == ending)
				return ending;
			if (/*iter->first < root->pair->first*/k_compare(iter->first, root->pair->first))
			{
				if (root->pair->first != node->pair->first)
					temp = root;
				root->left = do_father(root->left, iter,node);
			}
			else if (/*iter->first > root->pair->first*/k_compare(root->pair->first, iter->first))
			{
				if (root->pair->first != node->pair->first)
					temp = root;
				root->right = do_father(root->right, iter, node);
			}
			else
			{
				if (root->pair->first != node->pair->first)
				{

					if (temp && root->pair->first == temp->pair->first)
						root->parent = node;
					else if (temp != NULL)
						root->parent = temp;
				}
				else
					root->parent = NULL;
				temp = NULL;
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
			if (/*pos->first < node->pair->first*/k_compare(pos->first, node->pair->first))
				node->left = the_right_node(node->left, pos);
			else if (/*pos->first > node->pair->first*/k_compare(node->pair->first, pos->first))
				node->right = the_right_node(node->right, pos);
			return node;
		}

		Node_*		erase_node(Node_ *root, iterator pos) {
			if (root == NULL)
				return root;
			if (root == ending)
				return root;
			if (/*pos->first < root->pair->first*/k_compare(pos->first, root->pair->first))
				root->left = erase_node(root->left, pos);
			else if (/*pos->first > root->pair->first*/k_compare(root->pair->first, pos->first))
				root->right = erase_node(root->right, pos);
			else {
				if ((root->left == NULL) || (root->right == NULL) || (root->left == r_ending) || (root->right == ending)) {
					Node_ *temp = root->left ? root->left : root->right;
					if (root->left != NULL && root->left != r_ending)
						temp = root->left;
					else if (root->right != NULL && root->right != ending)
						temp = root->right;
					if (temp == NULL) {
						temp = root;
						root = NULL;
						alloc_.deallocate(temp, 1);
					}
					else if (temp == ending)
					{
						temp = root;
						root = ending;
						ending->parent = temp->parent;
						alloc_.deallocate(temp, 1);
					}
					else if (temp == r_ending)
					{
						temp = root;
						r_ending->parent = temp->parent;
						root = r_ending;
						alloc_.deallocate(temp, 1);
					}
					else {
						Node_* timp = root;
						root = temp;
						root->parent = timp->parent;
						if (timp->right == ending)
						{
							
							 Node_ *tmp  = root;
							while (tmp->right != NULL && tmp->right != ending)
							{
								tmp = tmp->right;
							}
							tmp->right = ending;
							ending->parent = tmp;
						}
						if (timp->left == r_ending)
						{
							 Node_ *tmp  = root;
							while (tmp->left != NULL && tmp->left != r_ending)
							{
								tmp = tmp->left;
							}
							tmp->left = r_ending;
							r_ending->parent = tmp;
						}
						alloc_.deallocate(timp, 1);
					}
				} else {
					iterator temp = iterator(root->right).left_left();//= nodeWithMinimumValue(root->right);
					if (temp != NULL && temp != r_ending)
					{
						alloc.construct(root->pair, temp.return_pair());
						root->right = erase_node(root->right,
												 temp);
					}
					else
					{
						Node_* tmp = root;
						root = NULL;
						alloc_.deallocate(tmp, 1);
					}
				}
				if (root == NULL)
					return root;
				root->height = 1 + max(height(root->left),
									   height(root->right));
			}
			return root;
		}

		// Node_*		do_rotation(Node_ *root, iterator iter)
		// {
		// 	key_compare comp;
		// 	if (root == NULL)
		// 		return NULL;
		// 	if (root == ending)
		// 		return  ending;
		// 	root->height = 1 + max(height(root->left),height(root->right));
		// 	if (/*iter->first < root->pair->first*/k_compare(iter->first, root->pair->first))
		// 		root->left = do_rotation(root->left, iter);
		// 	else if (/*iter->first > root->pair->first*/k_compare(root->pair->first, iter->first))
		// 		root->right = do_rotation(root->right, iter);
		// 	else
		// 	{
		// 		int balanceFactor = balanc_factor(root);
		// 		if (balanceFactor > 1) {
		// 			if (balanc_factor(root->left) >= 0) {
		// 				return right_rotate(root);
		// 			}
		// 			else {
		// 				root->left = left_rotate(root->left);
		// 				return right_rotate(root);
		// 			}
		// 		}
		// 		if (balanceFactor < -1) {
		// 			if (balanc_factor(root->right) <= 0) {
		// 				return left_rotate(root);
		// 			} else {
		// 				root->right = right_rotate(root->right);
		// 				return left_rotate(root);
		// 			}
		// 		}
		// 	}
		// 	return root;
		// }

		Node_*		do_rotation(Node_ *root, iterator iter)
		{
			if (root == NULL)
				return NULL;
			if (root == ending)
				return  ending;

	//			std::cout << "he ==> " << root->height << std::endl;
			root->height = 1 + max(height(root->left),height(root->right));
		//		std::cout << "0he ==> " << root->height << std::endl;
		//	root->height = 1 + max(height(root->left),height(root->right));
			if (/*iter->first < root->pair->first*/k_compare(iter->first, root->pair->first))
				root->left = do_rotation(root->left, iter);
			else if (/*iter->first > root->pair->first*/k_compare(root->pair->first, iter->first))
				root->right = do_rotation(root->right, iter);
			else
			{
				int balanceFactor = balanc_factor(root);
			//	std::cout << "BA ++> " << balanceFactor << std::endl;
				if (balanceFactor > 1) {
					if (balanc_factor(root->left) >= 0) {
						return right_rotate(root);
					}
					else {
						root->left = left_rotate(root->left);
						return right_rotate(root);
					}
				}
				if (balanceFactor < -1) {
					if (balanc_factor(root->right) <= 0) {
						 return left_rotate(root);
					} else {
						root->right = right_rotate(root->right);
						return left_rotate(root);
					}
				}
			}
			return root;
		}


//		Node_*		do_rotation_tes(Node_ *root, iterator iter, Node *pos)
//		{
//			key_compare comp;
//			if (root == NULL)
//				return NULL;
//			if (root == ending)
//				return  ending;
//
//	//			std::cout << "he ==> " << root->height << std::endl;
//			root->height = 1 + max(height(root->left),height(root->right));
//		//		std::cout << "0he ==> " << root->height << std::endl;
//		//	root->height = 1 + max(height(root->left),height(root->right));
//			if (/*iter->first < root->pair->first*/k_compare(iter->first, root->pair->first))
//				root->left = do_rotation(root->left, iter);
//			else if (/*iter->first > root->pair->first*/k_compare(root->pair->first, iter->first))
//				root->right = do_rotation(root->right, iter);
//			else
//			{
//				int balanceFactor = balanc_factor(root);
//			//	std::cout << "BA ++> " << balanceFactor << std::endl;
//				if (balanceFactor > 1) {
//					if (balanc_factor(root->left) >= 0) {
//						return right_rotate(root);
//					}
//					else {
//						root->left = left_rotate(root->left);
//						return right_rotate(root);
//					}
//				}
//				if (balanceFactor < -1) {
//					if (balanc_factor(root->right) <= 0) {
//						 return left_rotate(root);
//					} else {
//						root->right = right_rotate(root->right);
//						return left_rotate(root);
//					}
//				}
//			}
//			return root;
//		root}



		Node_*		upadte_height(Node_* root, iterator iter)
		{
			if (root == NULL)
				return NULL;
			if (root == ending)
				return ending;
			if (root == r_ending)
				return r_ending;
			if (/*iter->first < root->pair->first*/ k_compare(iter->first, root->pair->first))
				root->left = upadte_height(root->left, iter);
			else if (/*iter->first > root->pair->first*/k_compare(root->pair->first, iter->first))
				root->right = upadte_height(root->right, iter);
			else
			{
				root->height = 1 + max(height(root->left),height(root->right));

			//	std::cout << "Key --> " << root->pair->first << " || height --> " << root->height << std::endl;
			}
			return root;
		}

		iterator 		find_key(const value_type *value)
		{
			iterator iter;
			iterator fin = end();

			iter = begin();
			if (/*value->first < node->pair->first*/k_compare(value->first, node->pair->first))
			{
				while (iter != iterator(node))
				{
			 		if (iter->first == value->first)
			 			return iter;
			 		iter++;
				}
			}
			else if (/*value->first > node->pair->first*/k_compare(node->pair->first, value->first))
			{
				iterator itera = node;
				while (itera != fin)
				{
			 		if (itera->first == value->first)
			 			return itera;
			 		itera++;
				}
			}
			else if (/*value->first == node->pair->first*/k_compare(node->pair->first, value->first) == false && k_compare(value->first, node->pair->first) == false )
			{
				iter = iterator(node);
				return iter;
			}
			in = 1;
			return iter;
		}

		iterator 		find_key(const value_type &value)
		{
			iterator iter;
			iterator fin = end();

			iter = begin();

			if (/*value.first < node->pair->first*/k_compare(value.first, node->pair->first))
			{
				while (iter != iterator(node))
				{
			 		if (iter->first == value.first)
			 			return iter;
			 		iter++;
				}
			}
			else if (/*value.first > node->pair->first*/k_compare(node->pair->first, value.first))
			{
				iterator itera = node;
				while (itera != fin)
				{
			 		if (itera->first == value.first)
			 			return itera;
			 		itera++;
				}
			}
			else if (/*value.first == node->pair->first*/k_compare(value.first, node->pair->first) ==  false && k_compare(node->pair->first, value.first) == false)
			{
				iter = iterator(node);
				return iter;
			}

			return iter;
		}

		iterator 		find_key(const key_type& k )
		{
			iterator iter;
			iterator fin = end();

			iter = begin();

			if (/*k < node->pair->first*/k_compare(k, node->pair->first))
			{
				while (iter != iterator(node))
				{
			 		if (iter->first == k)
			 			return iter;
			 		iter++;
				}
			}
			else if (/*k > node->pair->first*/k_compare(node->pair->first, k))
			{
				iterator itera = node;
				while (itera != fin)
				{
			 		if (itera->first == k)
			 			return itera;
			 		itera++;
				}
			}
			else if (/*k == node->pair->first*/ k_compare(node->pair->first, k) ==  false && k_compare(k, node->pair->first) == false)
			{
				iter = iterator(node);
				return iter;
			}
			in = 1;
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
			node->left = r_ending;
			node->right	=	ending;
			node->parent = NULL;
			ending->right = NULL;
			ending->left = NULL;
			ending->pair = NULL;
			ending->height = 0;
			ending->parent = node;
			r_ending->right = NULL;
			r_ending->left = NULL;
			r_ending->pair = NULL;
			r_ending->height = 0;
			r_ending->parent = node;
		}

		Node_*	new_node(const value_type &val, int i)
		{
			_node =  alloc_.allocate(1);
			_node->pair =	alloc.allocate(1);
			alloc.construct(_node->pair, val);
		//	tempi->first = iterator(_node);
			_node->height = 1;
			_node->parent = tmp;
			if (i == 0)
			{
				_node->left = NULL;
				_node->right = NULL;
			}
			else if (i == 1)
			{
				_node->left = NULL;
				_node->right = ending;
				ending->right = NULL;
				ending->left = NULL;
				ending->pair = NULL;
				ending->parent = _node;
				ending->height = 0;
			}
			else
			{
				_node->left = r_ending;
				_node->right = NULL;
				r_ending->right = NULL;
				r_ending->left = NULL;
				r_ending->pair = NULL;
				r_ending->parent = _node;
				r_ending->height = 0;
			}
			return _node;
		}

		Node_*	my_insert(Node_* node, const value_type& val)
		{
		//	int balance;
			if (node == NULL)
			{
				return (new_node(val, 0));
			}
			else if (node == ending)
			{
				return (new_node(val, 1));
			}
			else if (node == r_ending)
			{
				return new_node(val, 2);
			}
			// std::cout << "mid1\n";
			if (/*val.first < node->pair->first*/k_compare(val.first, node->pair->first))
			{
				tmp = node;
				node->left = my_insert(node->left, val);
			}
			else if (/*val.first > node->pair->first*/k_compare(node->pair->first, val.first))
			{
				tmp = node;
				node->right = my_insert(node->right, val);
			}
			else if (/*val.first == node->pair->first*/k_compare(val.first, node->pair->first) == false && k_compare(node->pair->first, val.first) == false )
			{
				flag = 1;
			}
			return node;
		}

		Node_*		right_rotate(Node_* y)
		{
			// printTree(node, "", true);
			// std::cout << "RR \n";
			Node_ *x = y->left;
			Node_ *T2 = x->right;
			x->right = y;

			y->left = T2;
			// if (x->right && x->right != ending)
			// 	x->right->parent = x;
			 Node_* temp = y->parent;
			 y->parent = x;
			 x->parent = temp;
			if (y->left)
				y->left->parent = y;
			if (x->parent)
			{
				if (x->parent->left == y)
			 		x->parent->left = x;
				else
					x->parent->right = x;

			}
			y->height = max(height(y->left),
							height(y->right)) +
						1;
			x->height = max(height(x->left),
							height(x->right)) +
						1;
			// std::cout << "x ==>  " << x->pair->first << std::endl;
			// if (x->right)
			// 	std::cout << "xR ==>  " << x->right->pair->first << std::endl;
			// if (x->left)
			// 	std::cout << "xL ==>  " << x->left->pair->first << std::endl;
			// if (x->parent)
			// 	std::cout << "xP ==>  " << x->parent->pair->first << std::endl;
			// rotate_true = 1;
			return x;
		}

		Node_*	left_rotate(Node_* x)
		{
			// printTree(node, "", true);
			// std::cout << "LR \n";
			// std::cout << "x ==>  " << x->pair->first << std::endl;
			// if (x->right)
			// 	std::cout << "xR ==>  " << x->right->pair->first << std::endl;
			// if (x->left)
			// 	std::cout << "xL ==>  " << x->left->pair->first << std::endl;
			// if (x->parent)
			// 	std::cout << "xP ==>  " << x->parent->pair->first << std::endl;
			Node_ *y = x->right;
			Node_ *T2 = y->left;

			y->parent = x->parent;
			y->left = x;
			x->right = T2;
			if (y->left && y->left != r_ending)
				y->left->parent = y;
			if (x->right)
				x->right->parent = x;
			 x->parent = y;
			//y->parent = temp;
			 if (y->parent)
			 {
				if(y->parent->right == x)
			 		y->parent->right = y;
				else
					y->parent->left = y;	
			 }
			x->height = max(height(x->left),
							height(x->right)) +
						1;
			y->height = max(height(y->left),height(y->right)) +
						1;
			// rotate_true = 1;
			// printTree(node, "", true);
			return y;
		}

		friend  bool operator== ( const ft::map<Key,T,Compare,Alloc>& lhs,
						  const ft::map<Key,T,Compare,Alloc>& rhs )
		{
			if (lhs.size() == rhs.size())
			{
				if (std::equal(lhs.begin(), lhs.end(), rhs.begin()))
					return (true);
				else
					return (false);
			}
			else
				return (false);
		}

		friend bool operator!= ( const ft::map<Key,T,Compare,Alloc>& lhs,
						  const ft::map<Key,T,Compare,Alloc>& rhs )
		{
			return !(lhs == rhs);
		}

		friend bool operator<  ( const ft::map<Key,T,Compare,Alloc>& lhs,
						  const ft::map<Key,T,Compare,Alloc>& rhs )
		{
			return (std::lexicographical_compare(lhs.begin(), lhs.end() - 1, rhs.begin(), rhs.end() - 1));
		}

		friend bool operator<= ( const ft::map<Key,T,Compare,Alloc>& lhs,
						  const ft::map<Key,T,Compare,Alloc>& rhs )
		{
			return  !(rhs < lhs);
		}

		friend  bool operator>  ( const ft::map<Key,T,Compare,Alloc>& lhs,
						  const ft::map<Key,T,Compare,Alloc>& rhs )
		{
			return (rhs < lhs);
		}

		friend bool operator>= ( const ft::map<Key,T,Compare,Alloc>& lhs,
						  const ft::map<Key,T,Compare,Alloc>& rhs )
		{
			return !(lhs < rhs);
		}

		friend void swap (ft::map<Key,T,Compare,Alloc>& x, ft::map<Key,T,Compare,Alloc>& y)
		{
			x.swap(y);
		}
	};
}




#endif //CONTAINERS_MAP_HPP