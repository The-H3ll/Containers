
#include <memory>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <math.h>
#include "iterators.hpp"
#include "enable_if.hpp"

namespace ft
{
    template < class T, class Alloc = std::allocator<T> > 
    class vector
    {
            // Members Types
        public:
            typedef  float                          	size_type;
            typedef  T                                      	value_type;
            typedef  Alloc                                  	allocator_type;
            typedef typename Alloc::reference&               	reference;
            typedef const typename Alloc::const_reference&    	const_reference;
            typedef typename Alloc::pointer*           			pointer;
			typedef const typename Alloc::pointer*           	const_pointer;
			typedef Iterator<value_type>							iterator;


		//typedef typename std::allocator<T>::value_type  value_type;
	private:
            allocator_type _alloc;
            //T               _value_type;
            size_type       _size;
            size_type       _capacity;
            value_type      *arr;
        public:
            //  Constructors

            explicit vector(const allocator_type& alloc = allocator_type())
            {
                _alloc = alloc;
                _size = 0;
            }
            explicit vector(size_type n, const value_type& va = value_type(), const allocator_type& alloc= allocator_type())
            {
                _alloc = alloc;
                _size = n;
                this->arr = _alloc.allocate(n);
                _capacity = n;
                for (int i = 0; i < n; i++)
                {
                    this->arr[i] = va; 
                }
            }
		template <class InputIterator >
		vector (InputIterator first, InputIterator last,
		  typename  ft::enable_if<Iterator_trait<InputIterator>::value, InputIterator>::type,
				const allocator_type& alloc = allocator_type())
            {
                _alloc = alloc;
                int count = 0;
                int i = 0;
                while (first != last)
                {
                    count += 1;
                    first += 1;
                }
                this->arr = _alloc.allocate(count);
                while (first != last)
                {
                    this->arr[i] = *first;
                    first++;
                }
            }
            vector (const vector& x)
            {
                this->arr = x.arr;
                this->siz = x.siz;
            }
            // Iterators
           iterator	begin()
           {
            	iterator sec(&arr[0]);
            	return(sec);
           }
           iterator end()
		   {
            	iterator first(&arr[this->_size]);
            	return (first);
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
                return (arr(this->_size - 1));
            }
            const_reference back() const
            {
                return (arr(this->_size - 1));
            }
            //  Capacity

            size_type size() const
            {
                return (this->_size);
            }
            size_type max_size() const
            {
                unsigned long  hold = 1;
                const char *s = typeid(T).name();
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
                value_type *array;
                int i = 0;
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
                        this->arr = _alloc.allocate(this->_capacity * 2);
                        this->_capacity *= 2;
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
               for (int i = 0; i < n; i++)
                   this->arr[i] = val;
            }
            void    push_back(const value_type& val)
            {
                value_type  *array;
                int i = 0;

                this->_size += 1;
                array = _alloc.allocate(this->_size + 1);
                for (int i = 0; i < this->_size - 1; i++)
                {
                    array[i] = this->arr[i];
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
    void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y) 
    {
        x.swap(y);
    }
