
#include <vector>
#include <iostream>
#include "vector.hpp"


int     main()
{
    std::vector<int> first;
    std::vector<char> firsts;
    std::vector<double> firstss;
    std::vector<long> firstsss;

    first.shrink_to_fit();
    
    ft::vector<int> test;
    ft::vector<char> tests;
    ft::vector<double> testss;
    ft::vector<long> testsss;
  //  std::cout << test.size() << std::endl
    // std::cout << first.max_size() << std::endl;
    // std::cout << firsts.max_size() << std::endl;
    // std::cout << firstss.max_size() << std::endl;
    std::cout << first.max_size() << " || " << test.max_size() <<  std::endl;
    std::cout << firsts.max_size() << " || " << tests.max_size() <<  std::endl;
    std::cout << firstss.max_size() << " || " << testss.max_size() <<  std::endl;
    std::cout << firstsss.max_size() << " || " << testsss.max_size() <<  std::endl;
    return 0;
}