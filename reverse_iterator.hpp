//
// Created by Mouaad Labhairi on 4/10/22.
//

#ifndef CONTAINERS_REVERSE_ITERATOR_HPP
#define CONTAINERS_REVERSE_ITERATOR_HPP

#include "iterators_traits.hpp"

template <class Iterator>
class reverse_iterator
{
public:
	typedef	Iterator										iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iterator>::value_type 			value_type;
	typedef typename iterator_traits<Iterator>::difference_type 		difference_type;
	typedef typename iterator_traits<Iterator>::pointer 				pointer;
	typedef typename iterator_traits<Iterator>::reference 			reference;

	//	Declaration
private:
	iterator_type current;

	//Constructors

	reverse_iterator()
	{
		current = iterator_type ();
	}
	explicit reverse_iterator(iterator_type it)
	{
		current = it;
	}

	template<class Iter>
	reverse_iterator(const reverse_iterator<Iter>& rev_it)
	{
		current = rev_it.base();
	}

	iterator_type base() const
	{
		return (current);
	}

	reference operator*() const
	{
		iterator_type temp;

		temp = current;

		return (*--temp);
	}

	reverse_iterator	operator+(difference_type n) const
	{
		return (reverse_iterator(current - n));
	}
	reverse_iterator& operator++()
	{
		--current;
		return (*this);
	}

	reverse_iterator	operator++(int )
	{
		--current;
		return (*this);
	}

	reverse_iterator& operator--()
	{
		++current;
		return (*this);
	}

	reverse_iterator	operator--(int )
	{
		++current;
		return (*this);
	}

	reverse_iterator	operator+=(difference_type n) const
	{
		return (reverse_iterator(current -= n));
	}

	reverse_iterator	operator-(difference_type n) const
	{
		return (reverse_iterator(current + n));
	}
	reverse_iterator	operator-=(difference_type n) const
	{
		return (reverse_iterator(current += n));
	}

	pointer operator->()const
	{
		return &(operator*());
	}

	reference operator[](difference_type n) const
	{
		return (*this + n);
	}

};

//	Relation Operators

template <class Iterator>
bool operator== (const reverse_iterator<Iterator>& lhs,
				 const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class Iterator>
bool operator!= (const reverse_iterator<Iterator>& lhs,
				 const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator>
bool operator<  (const reverse_iterator<Iterator>& lhs,
				 const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() > rhs.base());
}

template <class Iterator>
bool operator<= (const reverse_iterator<Iterator>& lhs,
				 const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class Iterator>
bool operator>  (const reverse_iterator<Iterator>& lhs,
				 const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() < rhs.base());
}

template <class Iterator>
bool operator>= (const reverse_iterator<Iterator>& lhs,
				 const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class Iterator>
		reverse_iterator<Iterator> operator+ (
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it)
{
	return (rev_it.base() - n);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator- (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)

{
	return (lhs.base() - rhs.base());
}











#endif //CONTAINERS_REVERSE_ITERATOR_HPP
