//
// Created by Mouaad Labhairi on 4/10/22.
//

#ifndef CONTAINERS_ITERATORS_TRAITS_HPP
#define CONTAINERS_ITERATORS_TRAITS_HPP

#include <memory>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stdexcept>



template <class Iterator>
class iterator_traits
{
public:
	typedef Iterator		value_type;
	typedef std::ptrdiff_t	difference_type;
	typedef typename Iterator::pointer		pointer;
	typedef typename Iterator::reference		reference;
	typedef std::random_access_iterator_tag iterator_category;




};

#endif //CONTAINERS_ITERATORS_TRAITS_HPP
