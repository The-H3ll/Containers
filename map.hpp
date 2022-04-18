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
		typedef	Map_iterator<value_type , Node_>							iterator;
		typedef Map_iterator<const value_type, Node_>						const_iterator;
		typedef reverse_iterator<const_iterator>							const_reverse_iterator;
		typedef reverse_iterator<iterator>									reverse_iterator;
		typedef typename 	Alloc::template rebind<iterator >::other		allocator_iter;
		typedef typename iterator_traits<iterator>::difference_type 					difference_type;


	private:
		size_type		_size;
		allocator_iter 	iter_alloc;
		Node_			*node ;
		Node_			*root;
		Node_			*temp_parent;
		Node_			*tmp;
		Node_			*temp;
		allocator_type	alloc;
		allocator_ 		alloc_;
		key_compare 	k_compare;
		int 			check;

	public:

		//	Constructors
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()): check(0)
		{
			this->node = NULL;
			this->_size = 0;
			k_compare = comp;
			this->alloc = alloc;
		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type())
		{
			while (first != last)
			{
				insert(*first);
				first++;
			}
			k_compare = comp;
			this->alloc = alloc;
		}

		map (const map& x)
		{
			insert(x.begin(), x.end());
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
				this->_size += 1;
				return my_pair;
			}
			if (val.first < node->pair->first)
			{
				tmp = node;
				node->left = my_insert(node->left, val);
				my_pair.first = find_key(val);
				my_pair.second = true;
				this->_size += 1;
			}
			else if (val.first > node->pair->first)
			{
				tmp = node;
				node->right = my_insert(node->right, val);
				root = node;
				iterator  iter = begin();
				while (iter != end())
				{
					node = do_father(node, iter, root);
					iter++;
				}
				my_pair.first = find_key(val);
				my_pair.second = true;
				this->_size += 1;
			}
			else
				my_pair.second = false;
			printTree(node, "", true);
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
			if (val.first < node->pair->first)
			{
				tmp = node;
				node->left = my_insert(node->left, val);
				this->_size += 1;
			}
			else if (val.first > node->pair->first)
			{
				tmp = node;
				node->right = my_insert(node->right, val);
				root = node;
				iterator  iter = begin();
				while (iter != end())
				{
					node = do_father(node, iter, root);
					iter++;
				}
				this->_size += 1;
			}
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

			node = erase_node(node, position);
			while (node && node->parent != NULL )
				node = node->parent;
			if (node)
			{
				root = node;
				iter = begin();
				while (iter != end())
				{
					node = do_father(node, iter, root);
					iter++;
				}
				iter = begin();
				while (iter != end())
				{
					node = upadte_height(node, iter);
					iter++;
				}
				iter = begin();
				while (iter != end())
				{
					node = do_rotation(node, iter);
					iter++;
				}
				root = node;
				iter = begin();
				while (iter != end())
				{
					node = do_father(node, iter, root);
					iter++;
				}
			}
			this->_size -= 1;
		}
		void 	erase(iterator first, iterator last) {
			iterator iter;

			while (first != last) {
				iter = first;
				first++;
				if (first != last)
				{
					if (iter->first == first->first)
						break;
				}
				erase(iter->first);
			}
		}
		size_type	erase(const key_type& k)
		{
			iterator iter;

			iter = find_key(k);
			node = erase_node(node, iter);
			while (node && node->parent != NULL)
				node = node->parent;
			if (node)
			{
				root = node;
				iter = begin();
				while (iter != end())
				{
					node = do_father(node, iter, root);
					iter++;
				}
				iter = begin();
				while (iter != end())
				{
					node = upadte_height(node, iter);
					iter++;
				}
				iter = begin();
				while (iter != end())
				{
					node = do_rotation(node, iter);
					iter++;
				}
				root = node;
				iter = begin();
				while (iter != end())
				{
					node = do_father(node, iter, root);
					iter++;
				}

			}
			this->_size -= 1;
			return (1);
		}
		void 		clear()
		{
			iterator iter = begin();
			erase(iter, end());
			alloc_.deallocate(node, this->_size);
			node = NULL;
			this->_size = 0;
		}
		void	swap(map& x)
		{
			map holo;

			holo = *this;
			*this = x;
			x = holo;
			check = 1;
		}
		//		Iterators

		iterator	begin()
		{
			iterator  iter(node);

			return iter.left_most();
		}
		const_iterator	begin() const
		{
			const_iterator  iter(node);

			return iter.left_most();
		}
		iterator end()
		{
			iterator iter(node);

			return iter.after_right_most();
		}

		const_iterator end() const
		{
			const_iterator ite(node);

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

			while (iter !=  end())
			{
				if (k_compare(iter->first, k) == false && k_compare(k, iter->first) == false)
					return (ft::make_pair(lower_bound(iter->first), upper_bound(iter->first)));
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
			}
			return (ft::make_pair(upper_bound(k), upper_bound(k)));
		}

		//	Capacity

		bool empty() const
		{
			std::cout << "This Size ==> " << this->_size << std::endl;
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
			iterator iter = begin();

			while (iter != end())
			{
				//std::cout << "Ie ==> " << iter->first << " K ==> " << k  <<'\n';
				if (k_compare(k, iter->first) == false && k_compare(iter->first, k) == false)
					return iter;
				iter++;
			}
			return end();
		}
		size_type count(const key_type& k) const
		{
			const_iterator iter = begin();

			while (iter != end())
			{
				//std::cout << "Ie ==> " << iter->first << " K ==> " << k  <<'\n';
				if (k_compare(k, iter->first) == false && k_compare(iter->first, k) == false)
					return 1;
				iter++;
			}
			return 0;
		}
		iterator lower_bound(const key_type& k)
		{
			iterator  iter;

			iter = begin();
			while (iter != end() && key_comp()(iter->first, k))
			{
				iter++;
			}
			return  iter;
		}
		const_iterator lower_bound(const key_type& k) const
		{
			const_iterator  iter;

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

			iter = begin();
			while (iter != end() && key_comp()(k, iter->first) == false)
				iter++;
			return  iter;
		}

		const_iterator upper_bound(const key_type& k) const
		{

			const_iterator  iter;

			iter = begin();
			while (iter != end() && key_comp()(k, iter->first) == false)
				iter++;

			return  iter;
		}

		//Allocator

		allocator_type get_allocator() const
		{
			return alloc;
		}


		~map()
		{
			if (node && check == 0)
				free_node();
			check = 0;
		}

	private:


		void	free_node()
		{
			iterator  iter = begin();

			erase(iter, end());

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
					if (temp && root->pair->first == temp->pair->first)
						root->parent = node;
					else if (temp != NULL)
						root->parent = temp;
					std::cout << "Node ==> " << root->pair->first << std::endl;
					std::cout << "PARENT ==> " << root->pair->first << std::endl;
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
					Node_ *temp = root->left ? root->left : root->right;
					if (temp == NULL) {
						temp = root;
						root = NULL;
						free(temp);
					}
					else {
						iterator iter = find_key(temp->pair);
						root = iter.return_node();
					}
				} else {
					iterator temp = iterator(root->right).left_most();//= nodeWithMinimumValue(root->right);
					check = 1;
					alloc.construct(root->pair, temp.return_pair());
					root->right = erase_node(root->right,
											 temp);
				}
				if (root == NULL)
					return root;
				root->height = 1 + max(height(root->left),
									   height(root->right));
			}
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
			if (y->parent == NULL)
			{
				y->parent = x;
				x->parent = NULL;
			}
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
			y->parent = x->parent;
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

template <class Key, class T, class Compare, class Alloc>
bool operator== ( const ft::map<Key,T,Compare,Alloc>& lhs,
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

template <class Key, class T, class Compare, class Alloc>
bool operator!= ( const ft::map<Key,T,Compare,Alloc>& lhs,
				  const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<  ( const ft::map<Key,T,Compare,Alloc>& lhs,
				  const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return (std::lexicographical_compare(lhs.begin(), lhs.end() - 1, rhs.begin(), rhs.end() - 1));
}

template <class Key, class T, class Compare, class Alloc>
bool operator<= ( const ft::map<Key,T,Compare,Alloc>& lhs,
				  const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return  !(rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>  ( const ft::map<Key,T,Compare,Alloc>& lhs,
				  const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return (rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>= ( const ft::map<Key,T,Compare,Alloc>& lhs,
				  const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return !(lhs < rhs);
}


template <class Key, class T, class Compare, class Alloc>
void swap (ft::map<Key,T,Compare,Alloc>& x, ft::map<Key,T,Compare,Alloc>& y)
{
	x.swap(y);
}



#endif //CONTAINERS_MAP_HPP