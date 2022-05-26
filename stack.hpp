#ifndef CONTAINERS_MAP_HPP
#define CONTAINERS_MAP_HPP


#include "vector.hpp"

namespace ft
{

    template<class T, class  Container = ft::vector<T> >
    class stack
    {
        public:
            typedef T   value_type;
            typedef Container   container_type;
            typedef typename container_type::size_type    size_type;
            
            container_type container;

            explicit stack (const container_type& ctnr = container_type()) : container(ctnr) {}

            bool empty() const
            {
                return (container.size() == 0);
            }
            size_type size() const
            {
                return (container.size());
            }
            value_type& top()
            { 
                return container.back();
            }
            const value_type& top() const
            {
                return container.back();
            }
            void push (const value_type& val)
            {
                return container.push_back(val);
            }
            void pop()
            {
                container.pop_back();

            }

		friend bool operator== (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return (lhs.container == rhs.container);
		}
		friend bool operator!= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return (lhs.container != rhs.container);
		}
		friend bool operator< (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return (lhs.container < rhs.container);
		}
		friend bool operator<= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return (lhs.container <= rhs.container);
		}
		friend bool operator> (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return (lhs.container > rhs.container);
		}
		friend bool operator>= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return (lhs.container >= rhs.container);
		}
	};

}

#endif