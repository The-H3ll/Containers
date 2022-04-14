
#include <memory>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <math.h>
#include "iterators.hpp"
#include "enable_if.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
    template < class T, class Alloc = std::allocator<T> > 
    class vector
    {
            // Members Types
        public:
            typedef  std::size_t                         				size_type;
            typedef  T                                      			value_type;
            typedef  Alloc                                  			allocator_type;
            typedef typename Alloc::reference&               			reference;
            typedef const typename Alloc::const_reference&    			const_reference;
            typedef typename Alloc::pointer*           					pointer;
			typedef const typename Alloc::pointer*           			const_pointer;
			typedef Iterator<value_type>								iterator;
			typedef Iterator<const value_type>							const_iterator;
			typedef reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef reverse_iterator<iterator>							reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type differenc_type;


		//typedef typename std::allocator<T>::value_type  value_type;
	private:
            allocator_type _alloc;
            size_type       _size;
            size_type       _capacity;
            value_type      *arr;
        public:
            //  Constructors

            explicit vector(const allocator_type& alloc = allocator_type())
            {
                _alloc = alloc;
                _size = 0;
                arr = NULL;
            }
            explicit vector(size_type n, const value_type& va = value_type(), const allocator_type& alloc= allocator_type())
            {
                _alloc = alloc;
                _size = n;
                arr = _alloc.allocate(n);
                _capacity = n;
                for (size_type i = 0; i < n; i++)
                {
                    arr[i] = va;
                }
            }
		template <class InputIterator>
		vector (InputIterator first,InputIterator last,
				typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0,
				const allocator_type& alloc = allocator_type())
            {
				_capacity = 0;
                _alloc = alloc;
                int count = count_range(first, last);
                int i = 0;
//                while (temp != last)
//                {
//                    count += 1;
//                    temp++;
//                }
                this->arr = _alloc.allocate(count);
                while (first != last)
                {
                    arr[i] = *first;
                    first++;
                    i += 1;
                }
				_size = count;
                _capacity = count;

			}
            vector (const vector& x)
            {
            	arr = _alloc.allocate(x._size);
				for (size_type i = 0 ; i < x._size; i++)
				{
					arr[i] = x.arr[i];
				}
				_size = x._size;
				_capacity = x._capacity;
            }
			vector& operator= (const vector& x)
			{
				arr = x.arr;
				_size = x._size;
				_capacity = x._capacity;
				return *this;
			}
		// Iterators
           iterator	begin()
           {
            	iterator sec(&arr[0]);
			   return(sec);
           }
           const_iterator begin() const
		   {
			   const_iterator sec(&arr[0]);
			   return(sec);
		   }

		   iterator end()
		   {
            	iterator first(arr + this->_size);
            	return (first);
		   }
		   const_iterator end() const
		   {
			   const_iterator first(arr + this->_size);
			   return (first);
		   }

		   reverse_iterator	rbegin()
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
		   const_reverse_iterator rend() const
		   {
			   return (const_reverse_iterator(begin()));
		   }
            //  Element Access

            reference   operator[] (size_type n)
            {
                return (arr[n]);
            }
            const_reference   operator[] (size_type n) const
            {
                return (arr[n]);
            }
            reference   at(size_type n)
            {
                if (n >= this->_size)
                    throw std::out_of_range("Is out of range");
                else
                    return(arr[n]);
            } 
            const_reference   at(size_type n) const
            {
                if (n >= this->_size)
                    throw std::out_of_range("Is out of range");
                else
                    return(arr[n]);
            } 
            reference   front()
            {
                return (arr[0]);
            }
            const_reference   front() const
            {
                return (arr[0]);
            }
            reference   back()
            {
                return (arr[this->_size - 1]);
            }
            const_reference back() const
            {
                return (arr[this->_size - 1]);
            }
            //  Capacity

            size_type size() const
            {
                return (this->_size);
            }
            size_type max_size() const
            {
                unsigned long  hold = 1;
               // const char *s = typeid(T).name();
/*
                if (strcmp(s, "i") == 0)
                {
                    return ();
                }
                else if (strcmp(s, "c") == 0)
                {
                    for (int i = 0; i < (64 - sizeof(char)); i++ )
                        hold *= 2;
                    return (hold - 1);
                }
                else if (strcmp(s, "d") == 0 || strcmp(s, "l") == 0)
                {
                     for (int i = 0; i < 61 ; i++ )
                         hold *= 2;
                     return (hold - 1);
                }   */
				if (sizeof(T) != 1)
				{
					hold = pow(2, 64) / sizeof(T) - 1;
					return  (hold);
				}

				return (pow(2, 63) - 1);
            }
            size_type   capacity() const
            {
                return (this->_capacity);
            }
            void    resize(size_type n, value_type val = value_type())
            {
                value_type *array = NULL;
                size_type i = 0;
                if (n < this->_size)
                {
                    array = _alloc.allocate(n);
                    while ( i < n )
                    {
                        array[i] = this->arr[i];
                        i++;
                    }
                    _alloc.destroy(this->arr);
                    i = 0;
                    while (i < n)
                    {
                        this->arr[i] = array[i];
                        i++;
                    }
                }
                else if (n > this->_size)
                {
                   array = _alloc.allocate(n);
                   while ( i < this->_size )
                    {
                        array[i] = this->arr[i];
                        i++;
                    }
                    while (i < n)
                    {
                        array[i] = val;
                        i++;
                    }
                    if (n > this->_capacity)
                    {
                        _alloc.deallocate(this->arr, this->_size);
                        this->arr = _alloc.allocate(n);
                        this->_capacity = n;
                    }
                    else
                        _alloc.destroy(this->arr);
                    i = 0;
                    while (i < n)
                    {
                        this->arr[i] = array[i];
                        i++;           
                    }
                }
                this->_size = n;
            }
            bool    empty()
            {
                if (this->_size > 0)
                    return true;
                return false;
            }
            void    reserve (size_type n)
            {
                if (n > this->max_size())
                    throw std::length_error("Length above of Max_Size");
                else
                    {
                        this->arr = _alloc.allocate(n);
                        this->_capacity = n;
                    }
            }
            // Modifiers
            void    assign(size_type n, const value_type& val)
            {
               this->_size = n; 
               _alloc.destroy(this->arr);
               if (this->_size > this->_capacity)
               {
                   _alloc.deallocate(this->arr, this->_capacity);
                   this->arr = _alloc.allocate(this->_size);
                   this->_capacity = n;
               }
               for (size_type i = 0; i < n; i++)
                   this->arr[i] = val;
            }
            template <class InputIterator>
            void assign (InputIterator first, InputIterator last)
            {
            	size_type count = count_range(first, last);
				this->_size = count;
				_alloc.destroy(this->arr);
				if (this->_size > this->_capacity)
				{
					_alloc.deallocate(this->arr, this->_capacity);
					this->arr = _alloc.allocate(this->_size);
					this->_capacity = count;
				}
				for (size_type i = 0; i < count; i++)
				{
					this->arr[i] = *first;
					first++;
				}
			}
		void    push_back(const value_type& val)
		{
			value_type  *array;
                size_type i = 0;

                this->_size += 1;
                array = _alloc.allocate(this->_size + 1);
                for (size_type k = 0; k < this->_size - 1; k++)
                {
                    array[k] = this->arr[k];
                }
				_alloc.destroy(this->arr);
				if (this->_size > this->_capacity)
                {
					this->arr = _alloc.allocate(this->_capacity * 2);
                    this->_capacity *= 2;
                }
                while (i < this->_size - 1)
                {
                    this->arr[i] = array[i];
                    i += 1;
                }
                std::cout << "val ==> " << val;
                this->arr[i] = val;
                _alloc.deallocate(array, this->_size);
            }
            void    pop_back()
            {
                _alloc.destroy(this->arr + this->_size - 1);
                this->_size -= 1;
            }
			iterator insert (iterator position, const value_type& val)
			{
            	size_type  pos = 0;
            	size_type j = 0;
				value_type *array;
				iterator  iter = begin();
				array = _alloc.allocate(this->_size + 1);
				while (iter != position)
				{
					iter++;
					pos += 1;
				}
				for (size_type  i = 0 ; i < this->_size; i++)
				{
					if (i != pos)
					{
						array[i] = arr[j];
						j += 1;
					}
					else if (i == pos)
						array[i] = val;
				}
				_alloc.destroy(this->arr);
				this->_size += 1;
				if (this->_size > this->_capacity)
				{
					this->arr = _alloc.allocate(this->_capacity * 2);
					this->_capacity *= 2;
				}
				for (size_type i = 0 ; i < this->_size ; i++)
				{
					this->arr[i] = array[i];
				}
				_alloc.deallocate(array, this->_size);
				return (iter);
			}
			void insert (iterator position, size_type n, const value_type& val)
			{
				size_type pos = 0;
				size_type j = 0;
				size_type len = 0;
				value_type *array;
				iterator  iter = begin();
				array = _alloc.allocate(this->_size + n);
				while (iter != position)
				{
					iter++;
					pos += 1;
				}
				for (size_type i = 0 ; i < this->_size; i++)
				{
					if (i != pos)
					{
						array[i] = arr[j];
						j += 1;
					}
					else if (i == pos)
					{
						while (len < n)
						{
							array[i] = val;
							len++;
							if (len < n)
								i++;
						}
					}
				}
				_alloc.destroy(this->arr);
				this->_size += n;
				if (this->_size > this->_capacity)
				{
					this->arr = _alloc.allocate(this->_capacity * 2);
					this->_capacity *= 2;
				}
				for (size_type i = 0 ; i < this->_size ; i++)
				{
					this->arr[i] = array[i];
				}
				_alloc.deallocate(array, this->_size);
			}
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last)
			{
				size_type pos = 0;
				size_type j = 0;
				value_type *array = NULL;
				iterator  iter = begin();
				array = _alloc.allocate(this->_size + count_range(first, last));
				while (iter != position)
				{
					iter++;
					pos += 1;
				}
				for (size_type i = 0 ; i < this->_size; i++)
				{
					if (i != pos)
					{
						array[i] = arr[j];
						j += 1;
					}
					else if (i == pos)
					{
						while (first != last)
						{
							array[i] = *first;
							first++;
							if (first != last)
								i++;
						}
					}
				}
				_alloc.destroy(this->arr);
				this->_size += count_range(first, last);
				if (this->_size > this->_capacity)
				{
					this->arr = _alloc.allocate(this->_capacity * 2);
					this->_capacity *= 2;
				}
				for (size_type i = 0 ; i < this->_size ; i++)
					this->arr[i] = array[i];
				_alloc.deallocate(array, this->_size);
			}

			iterator erase(iterator position)
			{
            	size_type pos = 0;
            	size_type j = 0;
            	value_type	*array = NULL;

            	for (size_type i= 0; i < this->_size; i++)
            		array[i] = this->arr[i];
            	iterator find = begin();

            	while (find != position)
				{
					pos += 1;
					find++;
				}
            	_alloc.deallocate(this->arr, this->_size);
            	this->arr = _alloc.allocate(this->_capacity);
				this->_size -= 1;
				for (size_type i =0 ; i < this->_size; i++)
				{
					if (i != pos)
					{
						this->arr[j] = array[i];
						j += 1;
					}

				}
				return find;
			}

			iterator erase(iterator first , iterator last)
			{
            	size_type j = 0;
				value_type	*array = NULL;

				for (size_type i= 0; i < this->_size; i++)
					array[i] = this->arr[i];
				size_type pos = 0;
				size_type pos1 = 0;
				iterator find = begin();
				iterator finds = begin();

				while (find != first)
				{
					pos += 1;
					find++;
				}
				while (finds != last)
				{
					pos1 += 1;
					finds++;
				}
				_alloc.deallocate(this->arr, this->_size);
				this->arr = _alloc.allocate(this->_capacity);
				this->_size -= count_range(first, last);
				for (size_type i =0 ; i < this->_size; i++)
				{
					if (i < pos && i >= pos1)
					{
						this->arr[j] = array[i];
						j += 1;
					}

				}
				return finds;

			}

		void    swap(vector& x)
            {
                vector hold;

                hold = *this;
                *this = x;
                x = hold;
            }
            void    clear()
            {
                _alloc.destroy(this->arr);
                this->_size = 0;
            }

            // Allocator
            allocator_type  get_allocator() const
            {
                return (_alloc);
            }

	private:
		template<class X>
    	size_type 	count_range(X first ,X last)
		{
            	size_type count = 0;
            	while (first != last)
				{
            		first++;
            		count += 1;
				}
			return count;
		}
        //  Non-Members functions
        
        //friend bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);
       // friend bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);
    };

}
template <class T, class Alloc>
    bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
  {
      if (lhs.size() == rhs.size())
      {
       // if (std::equal(lhs.begin(), lhs.end(), rhs.begin()))
            return (true);
       // else
         //   return (false);
      }
      else
        return (false);
  }
  template <class T, class Alloc>
    bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        return !(lhs == rhs);
        // if (lhs.size() != rhs.size())
        // {
        //     return (true);
        // }
        // else
        //     return (false);
    }

template <class T, class Alloc>
bool operator<  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	if (lhs.size() < rhs.size())
		return true;
	return false;
}

template <class T, class Alloc>
bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	return !(rhs < lhs);
}

template <class T, class Alloc>
bool operator>  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	return (rhs < lhs);
}

template <class T, class Alloc>
bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	return !(lhs < rhs);
}





template <class T, class Alloc>
    void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y) 
    {
        x.swap(y);
    }
