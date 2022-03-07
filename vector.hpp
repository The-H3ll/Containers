
#include <memory>
#include <algorithm>
#include <iostream>
#include <cstring>

namespace ft
{
    template < class T, class Alloc = std::allocator<T> > 
    class vector
    {
        typedef  std::size_t        size_type;
        typedef const std::allocator<T>           allocator_type;        
        typedef typename std::allocator<T>::value_type  value_type;

        private:
            int siz;
            T   *arr;
        public:
            explicit vector(const allocator_type& alloc = allocator_type())
            {
                siz = 0;
             //   arr = alloc.allocate(0);
            }
            explicit vector(size_type n, const value_type& va = value_type(), const allocator_type& alloc = allocator_type())
            {
                this->arr = alloc.allocate(n);
                for (int i = 0; i < n; i++)
                {
                    this->arr[i] = va; 
                }
            }
            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
            {
                int count = 0;
                int i = 0;
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
                this->siz = x.siz;
            }

            size_type size() const
            {
                return (this->siz);
            }
            size_type max_size() const
            {
                unsigned long  hold = 1;
                const char *s = typeid(T).name();

                if (strcmp(s, "i") == 0)
                {
                    for (int i = 0; i <62; i++ )
                        hold *= 2;
                    return (hold - 1);
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
                     {
                         hold *= 2;
                     }
                     return (hold - 1);
                }   
                return 0;
            }
    };
}