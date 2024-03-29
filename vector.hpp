
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
				_capacity = 0;
            }
            explicit vector(size_type n, const value_type& va = value_type(), const allocator_type& alloc= allocator_type())
            {
                _alloc = alloc;
                _size = n;
                arr = _alloc.allocate(n);
                _capacity = n;
                for (size_type i = 0; i < n; i++)
                {
                    _alloc.construct(arr + i, va);
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
                this->arr = _alloc.allocate(count);
                while (first != last)
                {
					_alloc.construct(arr + i, *first);
                    first++;
                    i += 1;
                }
				_size = count;
                _capacity = count;

			}
			~vector()
			{
				for (size_type i = 0; i < this->_size; i++)
					_alloc.destroy(this->arr + i);
				if (this->_capacity > 0)
					_alloc.deallocate(this->arr, this->_capacity);
				this->arr = NULL;
				this->_size = 0;
				this->_capacity = 0;

				
			}
            vector (const vector& x)
            {
            	arr = _alloc.allocate(x._size);
				for (size_type i = 0 ; i < x._size; i++)
					_alloc.construct(arr + i, x[i]);
				_size = x._size;
				_capacity = x._capacity;
            }
			vector& operator= (const vector& x)
			{
				if (x._size > this->_capacity)
				{
					this->~vector();
					this->_capacity = x._size;
					this->arr = _alloc.allocate(this->_capacity);
				}
				for(size_type i = 0; i < x._size; i++)
				{
					_alloc.construct(this->arr + i, x[i]);
				}
				this->_size = x._size;
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
				return (_alloc.max_size());
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
						_alloc.construct(array + i, arr[i]);
                        i++;
                    }
                    _alloc.destroy(this->arr);
                    i = 0;
                    while (i < n)
                    {
						_alloc.construct(arr+ i, array[i]);
                        i++;
                    }
                }
                else if (n > this->_size)
                {
                   array = _alloc.allocate(n);
                   while ( i < this->_size )
                    {
						_alloc.construct(array + i, arr[i]);
                        i++;
                    }
                    while (i < n)
                    {
						_alloc.construct(array + i, val);
                        i++;
                    }
                    if (n > this->_capacity)
                    {
						if (this->arr)
                       		_alloc.deallocate(this->arr, this->_size);
                        this->arr = _alloc.allocate(n);
                        this->_capacity = n;
                    }
                    else
                        _alloc.destroy(this->arr);
                    i = 0;
                    while (i < n)
                    {
						_alloc.construct(arr + i, array[i]);
                        i++;           
                    }
                }
				if (array)
					_alloc.deallocate(array, n);
                this->_size = n;
            }
            bool    empty()
            {
                if (this->_size > 0)
                    return false;
                return true;
            }
            void    reserve (size_type n)
            {
				value_type  *array = NULL;
				if (n > this->max_size())
                    throw std::length_error("Length above of Max_Size");
                else if (n > this->_capacity)
                    {
                		if (this->_size > 0)
						{
							array = _alloc.allocate(this->_size);
							for (size_type i = 0 ; i < this->_size ; i++)
							{
								_alloc.construct(array + i, arr[i]);
							}
							if (arr)
								_alloc.deallocate(arr, this->_size);
							arr = NULL;
							arr = _alloc.allocate(n);
							this->_capacity = n;
							for (size_type i = 0; i < this->_size; i++)
								_alloc.construct(arr + i, array[i]);
							if (array)
								_alloc.deallocate(array, this->_size);
						}
                		else
						{
							if (arr)
								_alloc.deallocate(arr, this->_size);
							this->arr = _alloc.allocate(n);
							this->_capacity = n;
						}
					}
			}
            // Modifiers
            void    assign(size_type n, const value_type& val)
            {
               this->_size = n; 
               _alloc.destroy(this->arr);
               if (this->_size > this->_capacity)
               {
				   if (this->arr)
                		_alloc.deallocate(this->arr, this->_capacity);
                   this->arr = _alloc.allocate(this->_size);
                   this->_capacity = n;
               }
               for (size_type i = 0; i < n; i++)
			   {
				   _alloc.construct(arr + i, val);

			   }
            }
            template <class InputIterator>
            void assign (InputIterator first, InputIterator last)
            {
				size_type count = count_range(first, last);
				this->_size = count;
				if (this->arr)
					_alloc.destroy(this->arr);
				if (this->_size > this->_capacity)
				{
					if (this->arr)
						_alloc.deallocate(this->arr, this->_capacity);
					this->arr = _alloc.allocate(this->_size);
					this->_capacity = count;
				}
				for (size_type i = 0; i < count; i++)
				{
				   _alloc.construct(arr + i, *first);
					first++;
				}
			}
			void    push_back(const value_type& val)
			{
				value_type  *array;
                size_type i = 0;

                this->_size += 1;
				if (this->_size > this->_capacity)
                {
					array = _alloc.allocate(this->_size -1);
					for (size_type k = 0; k < this->_size - 1; k++)
					{
				   		_alloc.construct(array + k, arr[k]);
					}
					if (this->arr)
						_alloc.deallocate(this->arr, this->_size - 1);
					if (this->_capacity == 0)
					{
						this->_capacity = 1;
						this->arr = _alloc.allocate(this->_capacity);
					} else{
						this->arr = _alloc.allocate(this->_capacity * 2);
						this->_capacity *= 2;
					}
					while (i < this->_size - 1)
					{
				   		_alloc.construct(arr + i, array[i]);
						i += 1;
					}
					_alloc.construct(this->arr + i, val);
					if (array)
						_alloc.deallocate(array, this->_size);
				}
				else
				{
					_alloc.construct(this->arr + this->_size - 1, val);
				}
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
				if (this->_size == 0)
				{
					this->_size += 1;
					arr = _alloc.allocate(this->_size);
					this->_capacity = 1;
					_alloc.construct(arr + j, val);
					iter =begin();
					return iter;
				}
				array = _alloc.allocate(this->_size + 1);
				this->_size += 1;
				while (iter != position)
				{
					iter++;
					pos += 1;
				}
				for (size_type  i = 0 ; i < this->_size; i++)
				{
					if (i != pos)
					{
						_alloc.construct(array + i, arr[j]);
						j += 1;
					}
					else if (i == pos)
						_alloc.construct(array + i, val);
				}
				if (this->arr)
					_alloc.destroy(this->arr);
				if (this->_size > this->_capacity)
				{
					if (this->arr)
						_alloc.deallocate(this->arr, this->_size - 1);				
					this->arr = _alloc.allocate(this->_capacity * 2);
					this->_capacity *= 2;
				}
				for (size_type i = 0 ; i < this->_size ; i++)
				{
					_alloc.construct(arr + i, array[i]);
				}
				iter = begin();
				for (size_type  i = 0; i < pos; i++)
					iter++;
				if (array)
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
				this->_size += n;
				if (iter == position)
				{
					arr = _alloc.allocate(this->_size);
					for (size_type i = 0 ; i < this->_size ; i++)
					{
						_alloc.construct(arr + i , val);
					}
					this->_capacity = n;
					return ;
				}
				array = _alloc.allocate(this->_size + n);
				if (this->_capacity == 0)
				{
					this->_capacity = n;
					this->arr = _alloc.allocate(n);

				}
				while (iter != position)
				{
				
					iter++;
					pos += 1;
				}
				for (size_type i = 0 ; i < this->_size; i++)
				{
					if (i != pos)
					{
						_alloc.construct(array + i, arr[j]);
						j += 1;
					}
					else if (i == pos)
					{
						while (len < n)
						{
							_alloc.construct(array + i, val);
							len++;
							if (len < n)
								i++;
						}
					}
				}
				if (this->arr)
					_alloc.destroy(this->arr);
				if (this->_size > this->_capacity)
				{
					if (this->arr)
						_alloc.deallocate(this->arr, this->_size);
					this->_capacity *= 2;
					if (this->_capacity < this->_size)
						this->_capacity = this->_size;
					this->arr = _alloc.allocate(this->_capacity);
				}
				for (size_type i = 0 ; i < this->_size ; i++)
				{
					_alloc.construct(arr + i , array[i]);
				}
				if (array)
					_alloc.deallocate(array, this->_size);
			}
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last)
			{
				size_type pos = 0;
				size_type temp = this->_size;
				size_type j = 0;
				value_type *array = NULL;
				iterator  iter = begin();
				array = _alloc.allocate(this->_size + count_range(first, last));

				this->_size += count_range(first, last);
				while (iter != position)
				{
					iter++;
					pos += 1;
				}
				for (size_type i = 0 ; i < this->_size ; i++)
				{
					if (i != pos)
					{
						_alloc.construct(array + i, arr[j]);
						j += 1;
					}
					else if (i == pos)
					{
						while (first != last)
						{
							_alloc.construct(array+ i, *first);
							first++;
							if (first != last)
								i++;
						}
					}
				}
				if (this->arr)
					_alloc.destroy(this->arr);
				if (this->_size > this->_capacity)
				{
					if (this->arr)
						_alloc.deallocate(this->arr, temp);
					this->_capacity *= 2;
					if (this->_capacity < this->_size)
						this->_capacity = this->_size;
					this->arr = _alloc.allocate(this->_capacity);
				}
				for (size_type i = 0 ; i < this->_size ; i++)
					_alloc.construct(arr + i, array[i]);
				if (array)
					_alloc.deallocate(array, this->_size);
			}

			iterator erase(iterator position)
			{
            	size_type pos = 0;
            	size_type j = 0;
            	value_type	*array = NULL;


            	iterator find = begin();

				while (find != position)
				{
					pos += 1;
					find++;
				}
				if (find == end())
					return end();
				if (this->arr)
				{
					array = _alloc.allocate(this->_size);
					for (size_type i= 0; i < this->_size; i++)
						_alloc.construct(array + i, arr[i]);
					_alloc.destroy(this->arr + pos);
					for (size_type i =0 ; i < this->_size; i++)
					{
						if (i != pos)
						{
							_alloc.construct(arr + j, array[i]);
							j += 1;
						}
					}
					if (array)
						_alloc.deallocate(array, this->_size);
					this->_size -= 1;
				}
				find = begin();
				for(size_type i = 0 ; i < pos; i++)
					find++;
				return find;
			}

			iterator erase(iterator first , iterator last)
			{
            	size_type j = 0;
				value_type	*array = NULL;

				size_type pos = 0;
				size_type pos1 = 0;
				iterator find = begin();
				iterator finds = begin();
				if (first == end())
					return first;

				while (find != first)
				{
					pos += 1;
					find++;
				}
				if (find == end())
					return end();
				while (finds != last)
				{
					pos1 += 1;
					finds++;
				}
				if (this->arr)
				{
					array = _alloc.allocate(this->_size);
					for (size_type i= 0; i < this->_size; i++)
						_alloc.construct(array + i, arr[i]);
					if (this->arr)
						_alloc.deallocate(this->arr, this->_size);
					this->arr = _alloc.allocate(this->_capacity);
					for (size_type i =0 ; i < this->_size; i++)
					{
						if (i < pos || i >= pos1)
						{
							_alloc.construct(arr + j, array[i]);
							j += 1;
						}
					}
				}
				if (array)
					_alloc.deallocate(array, this->_size);
				this->_size -= count_range(first, last);
				if (this->_size ==0)
					return end();
				else
				{
					find = begin();
					if (find != end())
					{
						for(size_type i = 0 ; i < pos; i++)
							find++;
					}

				}
				return find;

			}

		void    swap(vector& x)
        {
                vector hold;
				
				hold.arr = this->arr;
				hold._capacity = this->_capacity;
				hold._size = this->_size;
				hold._alloc = this->_alloc;
				this->arr = x.arr;
				this->_size = x._size;
				this->_capacity = x._capacity;
				this->_alloc = x._alloc;
				x.arr = hold.arr;
				x._size = hold._size;
				x._capacity = hold._capacity;
				x._alloc = hold._alloc;
				hold._capacity = 0;
        }
            void    clear()
            {
				for (size_type i= 0; i < this->_size; i++)
					_alloc.destroy(this->arr + i);
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

		friend bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
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
		friend bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return !(lhs == rhs);
		}
		friend  bool operator<  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return (std::lexicographical_compare(lhs.begin(), lhs.end() - 1, rhs.begin(), rhs.end() - 1));
		}

		friend bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return !(rhs < lhs);
		}

		friend bool operator>  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return (rhs < lhs);
		}

		friend bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return !(lhs < rhs);
		}

		friend void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
		{
			x.swap(y);
		}
	};

}
