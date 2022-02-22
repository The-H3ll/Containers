
#include <memory>
#include <algorithm>
#include <iostream>

namespace ft
{
    template < class T, class Alloc = std::allocator<T> > 
    class vector
    {
        private:
        int size;
        T   *arr;
        public:
            explicit vector(const allocator_type& alloc = allocator_type())
            {
                this->size = 0;
                this->arr = alloc.allocate(0);
            }
            explicit vector(size_type n, const value_type& va = value_type(), const allocator_type& alloc = allocator_type())
            {
                this->arr = alloc.allocate(n);
                for (int i = 0; i < n; i++)
                {
                    this->arr[i] = val; 
                }
            }
            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
            {
                int count;
                while (first != last)
                {
                    count += 1;
                    first += 1;
                }
                this->arr = alloc.allocate(count);
                while (first != last)
                {
                    this->arr[i] = *first;
                    first++;
                }
            }
            vector (const vector& x)
            {
                this->arr = x.arr;
                this->size = x.size;
            }

            size_type size() const
            {
                return (this->size);
            }
    };    
}