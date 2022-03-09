
#include <vector>
#include <iostream>
#include "vector.hpp"


int     main()
{
    std::vector<int> first(5, 100);
    ft::vector<int> test(5, 100);

    first.assign(4, 22);
    test.assign(4, 22);
    // std::vector<char> firsts;
    // std::vector<double> firstss;
    // std::vector<long> firstsss;

    

    // ft::vector<char> tests;
    // ft::vector<double> testss;
    // ft::vector<long> testsss;
    for (int i = 0 ; i < 3; i++)
    {
        first.push_back(i);
        test.push_back(i);
    }
    first.pop_back();
    test.pop_back();
    for (int i = 0; i < first.size(); i++)
        std::cout << first[i] << " || " << test[i] << std::endl;
    std::cout << "Size ==> "<< test.size() <<  " || " << first.size() <<std::endl;
    // std::cout << first.max_size() << std::endl;
    // std::cout << firsts.max_size() << std::endl;
    // std::cout << firstss.max_size() << std::endl;
     std::cout << first.max_size() << " || " << test.max_size() <<  std::endl;
     std::cout << "Capacity ==> " << first.capacity() << " || " << test.capacity() << std::endl;
    // std::cout << firsts.max_size() << " || " << tests.max_size() <<  std::endl;
    // std::cout << firstss.max_size() << " || " << testss.max_size() <<  std::endl;
    // std::cout << firstsss.max_size() << " || " << testsss.max_size() <<  std::endl;

    std::cout << "CAP1 ==> " << first.capacity() << std::endl;
    std::cout << "CAP1 ==> " << test.capacity() << std::endl;
    test.resize(5);
    first.resize(5);

    std::cout << "CAP2 ==> " << first.capacity() << std::endl;
    std::cout << "CAP2 ==> " << test.capacity() << std::endl;
    // for (int i = 0; i < first.size(); i++)
    // {
    //     std::cout << "Resize ==> " <<  first[i] << " || " <<  test[i] << std::endl; 
    // }
    test.resize(6, 100);
    first.resize(6, 100);
    std::cout << "CAP3 ==> " << first.capacity() << std::endl;
    std::cout << "CAP3 ==> " << test.capacity() << std::endl;
    // for (int i = 0; i < first.size(); i++)
    // {
    //     std::cout << "Resize1 ==> " <<  first[i] << " || " <<  test[i] << std::endl; 
    // }
    test.resize(12);
    first.resize(12);
    // for (int i = 0; i < first.size(); i++)
    // {
    //     std::cout << "Resize3 ==> " <<  first[i] << " || " <<  test[i] << std::endl; 
    // }
    std::cout << "CAP4 ==> " << first.capacity() << std::endl;
    std::cout << "CAP4 ==> " << test.capacity() << std::endl;
    return 0;
}