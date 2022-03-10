

#include <memory>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stdexcept>

template <class Category, class T, class Distance = std::ptrdiff_t , class Pointer, class Reference>
class iterator
{
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Distance distance_type;
    typedef Pointer pointer;
    typedef Reference reference;
};