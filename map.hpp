//
// Created by Mouaad Labhairi on 3/14/22.
//

#ifndef CONTAINERS_MAP_HPP
#define CONTAINERS_MAP_HPP


template< class Key, class T, class Compare = less<key>,
        class Alloc = allocator<pair<const key, T> >
class map
{
	typedef Key			key_type;
	typedef T			mapped_type;
	typedef Compare		key_compare;

};


#endif //CONTAINERS_MAP_HPP
