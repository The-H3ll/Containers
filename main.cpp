
#include <vector>
#include <iostream>
#include "vector.hpp"


int     main()
{
    std::vector<int> first(10);
    // std::vector<char> firsts;
    // std::vector<double> firstss;
    // std::vector<long> firstsss;

    
    ft::vector<int> test;

    // ft::vector<char> tests;
    // ft::vector<double> testss;
    // ft::vector<long> testsss;
    std::cout << test.size() <<  " || " << first.size() <<std::endl;
    // std::cout << first.max_size() << std::endl;
    // std::cout << firsts.max_size() << std::endl;
    // std::cout << firstss.max_size() << std::endl;
     std::cout << first.max_size() << " || " << test.max_size() <<  std::endl;
     std::cout << "Capacity ==> " << first.capacity() << std::endl;
    // std::cout << firsts.max_size() << " || " << tests.max_size() <<  std::endl;
    // std::cout << firstss.max_size() << " || " << testss.max_size() <<  std::endl;
    // std::cout << firstsss.max_size() << " || " << testsss.max_size() <<  std::endl;
    return 0;
}