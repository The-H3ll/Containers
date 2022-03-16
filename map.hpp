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
#include "pair.hpp"
//#include "value_comp.hpp"

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>,
	        class Alloc = std::allocator<pair<const Key, T> > >
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

	private:
		size_type	_size;

	public:
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type())
		{
			this->_size = 0;
		}
		pair<iterator, bool > insert(const value_type& val)
		{

		}
	};
}





#endif //CONTAINERS_MAP_HPP
