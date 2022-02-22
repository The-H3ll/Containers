
#include <vector>
#include <iostream>
#include "vector.hpp"


int     main()
{
    std::vector<int> first;
    std::vector<int> second(first);

    ft::vector<int> test;

    std::cout << test.size() << std::endl;
}