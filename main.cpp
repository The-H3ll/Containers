
#include <vector>
#include <iostream>
#include <map>
#include "vector.hpp"
//#include "is_integral.hpp"
#include "map.hpp"



int     main()
{
	/*
    std::vector<int> first(5, 100);
    std::vector<int> first1(3, 300);

    ft::vector<int> test(5, 100);
    ft::vector<int> test1(3, 100);

    std::vector<int>::iterator it;

    first1.swap(first);
    test1.swap(test);
    
    std::cout << "=====Testing Swaps=====\n";
    for (int i = 0; i < first.size(); i++)
        std::cout << first[i] << " || " << test[i] << std::endl;
    
    std::cout << "Capacity0 ==> " << first.capacity() << " || " << test.capacity() << std::endl;

    std::cout << "=====Testing Assign=====\n";

    first.assign(10, 22);
    test.assign(10, 22);
    std::cout << "Capacity1 ==> " << first.capacity() << " || " << test.capacity() << std::endl;

    std::cout << "=====Testing PushBack / PopBack=====\n";
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
     std::cout <<"Max Size ==> "<< first.max_size() << " || " << test.max_size() <<  std::endl;
     std::cout << "Capacity2 ==> " << first.capacity() << " || " << test.capacity() << std::endl;
    // std::cout << firsts.max_size() << " || " << tests.max_size() <<  std::endl;
    // std::cout << firstss.max_size() << " || " << testss.max_size() <<  std::endl;
    // std::cout << firstsss.max_size() << " || " << testsss.max_size() <<  std::endl;

    std::cout << "=====Testing Resize=====\n";
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

    std::cout << "=====Testing Clear====\n";

    test.clear();
    first.clear();
    std::cout << "Size ==> "<< test.size() <<  " || " << first.size() <<std::endl;
    std::cout << "Capacity ==> " << first.capacity() << " || " << test.capacity() << std::endl;

    std::cout << "====Testing Allocator=====\n";
    std::vector<int> myvector;
  int * p;
  unsigned int i;

  // allocate an array with space for 5 elements using vector's allocator:
  p = myvector.get_allocator().allocate(5);

  // construct values in-place on the array:
  for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

  std::cout << "The allocated array contains:";
  for (i=0; i<5; i++) std::cout << ' ' << p[i];
  std::cout << '\n';

  // destroy and deallocate:
  for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
  myvector.get_allocator().deallocate(p,5);

    ft::vector<int> myvectors;
  int * ps;
 // unsigned int is;

  // allocate an array with space for 5 elements using vector's allocator:
  ps = myvectors.get_allocator().allocate(5);

  // construct values in-place on the array:
  for (i=0; i<5; i++) myvectors.get_allocator().construct(&ps[i],i);

  std::cout << "The allocated array contains:";
  for (i=0; i<5; i++) std::cout << ' ' << ps[i];
  std::cout << '\n';

  // destroy and deallocate:
  for (i=0; i<5; i++) myvectors.get_allocator().destroy(&ps[i]);
  myvectors.get_allocator().deallocate(ps,5);


  std::cout << "=====Testing Relational Operators======\n";

    std::vector<int> foo (3,100);   // three ints with a value of 100
    std::vector<int> bar (2,200);   // two ints with a value of 200
    ft::vector<int> foos(3, 100);
    ft::vector<int> bars (2,200);   // two ints with a value of 200

    if ( foo ==bar)
        std::cout << "foo and bar are equal\n";
    if (foos == bars)
        std::cout << "foos and bars are equal\n";
    //if ()
   // if (ft::operator!=(foos, bars))
   //     std::cout << "Are not equal\n";

   std::cout << "======Testing Iterators=========\n";

   	ft::vector<int> myVec;

	std::cout << "**** Testing Operator -> ****\n";
	ft::vector<int> myVec1;
	std::vector<int> t;
	t.push_back(3);
	myVec1.push_back(3);
	std::vector<int>::iterator itt;
	ft::vector<int>::iterator it2;
	itt = t.begin();
	it2 = myVec1.begin();
	std::cout << itt.operator->() << std::endl;
	std::cout << it2.operator->() << std::endl;

	std::cout << "**** Testing Operator !=, ==, ++ ****\n";
	t.clear();
	for (int i = 1 ; i < 5; i++)
		t.push_back(i);
	itt = t.begin();
	*itt++;
	std::cout << *itt << std::endl;
	myVec.clear();
	for (int i = 1; i < 5; i++)
		myVec.push_back(i);
	ft::vector<int>::iterator ite;
	for (ite = myVec.begin(); ite != myVec.end(); ite++)
		std::cout << *ite << std::endl;
	myVec.clear();
	for (int i = 1; i < 5; i++)
		myVec.push_back(i);
	ite = myVec.begin();
	*ite++;
	std::cout << *ite << std::endl;
	std::cout << "**** Testing Operator *it = m *****\n";
	ft::vector<int>car;
	car.push_back(10);
	ft::vector<int>::iterator tes = car.begin();
	std::cout << "Fir ==> " << *tes << std::endl;
	*tes = 3;
	std::cout << "test ==> " << *tes << std::endl;

	std::cout << "**** Testing Operator -- *****\n";
	myVec.clear();
	t.clear();
	std::cout << "Size1==> " << myVec.size() << std::endl;
	for (int i = 1; i < 5; i++)
	{
		myVec.push_back(i);
		std::cout << "I ==> " << i << std::endl;
 	}
	std::cout << "Size1==> " << myVec.size() << std::endl;
	for (int i = 0 ; i < myVec.size() ; i++)
		std::cout << myVec[i] << std::endl;
	std::cout << "=====\n";


	ite = myVec.begin();
	//ite = 2 + ite;
	for(int i = 0; i < 4 ;i++)
		std::cout << ite[i] << std::endl;

	std::cout << "**** Testing is Integral ****\n";

	//std::cout << "char: " << is_integral<char>::value << std::endl;
	//std::cout << "int: " << is_integral<int>::value << std::endl;
	//std::cout << "float: " << is_integral<float>::value << std::endl;

	std::cout << "**** Testing std::pair ****\n";

	std::pair <std::string,double> product1;                     // default constructor
	std::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
	std::pair <std::string,double> product3 (product2);          // copy constructor

	ft::pair <std::string,double> me_product1;                     // default constructor
	ft::pair <std::string,double> me_product2 ("tomatoes",2.30);   // value init
	ft::pair <std::string,double> me_product3 (me_product2);          // copy constructor

	product1.first = "labhairi";
	product1.second = 1;

	me_product1.first = "Mouaad";
	me_product1.second = 2;

	std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
	std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
	std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';

	std::cout << "The price of " << me_product1.first << " is $" << me_product1.second << '\n';
	std::cout << "The price of " << me_product2.first << " is $" << me_product2.second << '\n';
	std::cout << "The price of " << me_product3.first << " is $" << me_product3.second << '\n';

	ft::pair<int,char> fooo (10,'z');
	ft::pair<int,char> barr (90,'a');

	if (fooo==barr) std::cout << "foo and bar are equal\n";
	if (fooo!=barr) std::cout << "foo and bar are not equal\n";
	if (fooo< barr) std::cout << "foo is less than bar\n";
	if (fooo> barr) std::cout << "foo is greater than bar\n";
	if (fooo<=barr) std::cout << "foo is less than or equal to bar\n";
	if (fooo>=barr) std::cout << "foo is greater than or equal to bar\n";
*/
//	std::cout << "*****	Testing Map *****\n";
//	std::cout << "-------Testing Insert Delete-----\n";
//	ft::map<int, int> mapi;
//	std::map<char, int> map;
//
//	std::pair<std::map<char, int>::iterator ,bool>map_it1;
//	map.insert(std::pair<char, int>('a', 200));
//	map_it1 = map.insert(std::pair<char, int>('b', 100));
//
//	std::map<char, int>::iterator map_it;
//	ft::map<int, int>::iterator map_i;
//
//	for (map_it = map.begin(); map_it != map.end(); map_it++)
//		std::cout << "First ==> " << map_it->first << " || Second ==> " << map_it->second <<std::endl;
//
//	map.erase('b');
//
//	ft::pair<ft::map<int,int>::iterator,bool> ret;
//	ft::pair<ft::map<int,int>::iterator,bool> ret1;
////	 mapi.insert(ft::pair<char, int > ('a',2));
////	 ret = mapi.insert(ft::pair<char , int > ('b', 4));
////	 mapi.insert(ft::pair<char, int >('c', 5));
////	mapi.insert(ft::pair<char, int > ('1',2));
//
//	std::cout << "Starting \n";
//	ret = mapi.insert(ft::pair<int , int>(33, 2));
//	mapi.insert(ft::pair<int , int>(13, 2));
//	 mapi.insert(ft::pair<int , int>(54, 2));
//	mapi.insert(ft::pair<int , int>(9, 2));
//	mapi.insert(ft::pair<int , int>(21, 2));
//	ret1 = mapi.insert(ft::pair<int , int>(61, 2));
//	mapi.insert(ft::pair<int , int>(8, 2));
//	mapi.insert(ft::pair<int , int>(11, 2));
//
//	std::cout << "Size ==> " << mapi.size() << std::endl;
//	//mapi.erase(ret.first);
//	//mapi.erase(21);
//	//mapi.erase(33);
//	//mapi.erase(54);
//
//	mapi.erase(ret.first, mapi.end());
//	//mapi.erase(33);
//	std::cout << "After Eraaase\n";
//	std::cout << "Size ==> " << mapi.size() << std::endl;
//
//	map_i = mapi.begin();
//	while (map_i != mapi.end())
//	{
//		std::cout << " ==> " << map_i->first << std::endl;
//		map_i++;
//	}
//	std::cout << "To go backwards\n";
//	/*while (ret1.first != mapi.begin())
//	{
//		std::cout << " Back ==> " <<ret1.first->first << std::endl;
//		ret1.first--;
//	}
//	std::cout << " Back ==> " <<ret1.first->first << std::endl;*/
//
//	std::cout << "EEEENNNND\n";
//
//	std::cout << "------Testing Swap------\n";
//
//	ft::map<char, int> foo;
//
//	foo.insert(ft::pair<char, int>('e', 100));
//	foo.insert(ft::pair<char, int>('f', 200));
//	foo.insert(ft::pair<char, int>('g', 300));
//
//	ft::map<char, int> bar;
//	bar.insert(ft::pair<char, int>('x', 11));
//	bar.insert(ft::pair<char, int>('y', 110));
//	bar.insert(ft::pair<char, int>('z', 120));
//
//	std::cout << "BBBB\n";
//
//	foo.swap(bar);
//
//	std::cout << "AAAA\n";
//
//	std::cout << "HHHHEEEEELLLLOOOOO\n";
//	std::cout << "foo contains:\n";
//	for (ft::map<char,int>::iterator itw=foo.begin(); itw!=foo.end(); ++itw)
//		std::cout << itw->first << " => " << itw->second << '\n';
//
//	std::cout << "SizeFoo ==> " << foo.size() << std::endl;
//
//	std::cout <<"-------Testing Clear && Empty ------\n";
//
//	mapi.clear();
//
//	if (mapi.empty())
//	{
//		mapi.insert(ft::pair<char, int>(20, 100));
//		mapi.insert(ft::pair<char, int>(40, 200));
//	}
//
//	std::cout << "Iterate\n";
//	for (map_i = mapi.begin(); map_i != mapi.end(); map_i++)
//		std::cout << map_i->first << " ==> " << map_i->second << std::endl;
//
//	std::cout << "Size ==> " << mapi.size() << std::endl;
//
//	std::cout << "Max Size ==> " << map.max_size() << std::endl;
//	std::cout << "Ft Max Size ==> " << mapi.max_size() << std::endl;
//
//	std::cout << "-------Testing Value Comp-------\n";
//
//	ft::map<char, int >value_comps;
//
//	ft::pair<ft::map<char, int>::iterator , bool> paiss;
//	value_comps.insert(ft::pair<char, int>('a', 100));
//	value_comps.insert(ft::pair<char, int>('b', 100));
//	paiss = value_comps.insert(ft::pair<char, int>('c', 100));
//	ft::pair<char, int> high = *paiss.first;
//
//
//	ft::map<char, int>::iterator kol = value_comps.begin();
//	do{
//		std::cout << kol->first << " ==> " << kol->second << std::endl;
//	} while(value_comps.value_comp()(*kol++, high));
//
//
//	std::cout << "-------Testing Key Compare------\n";
//
//	ft::map<char,int> mymap;
//
//	ft::map<char,int>::key_compare mycomp = mymap.key_comp();
//
//	mymap.insert(ft::pair<char,int >('a', 100));
//	mymap.insert(ft::pair<char,int >('b', 100));
//	mymap.insert(ft::pair<char,int >('c', 100));
//
//	char x = 'c';
//	ft::map<char, int >::iterator polo = mymap.begin();
//
//	do {
//		std::cout << polo->first << " => " << polo->second << '\n';
//	} while ( mycomp((*polo++).first, x) );
//
//	std::cout << "----Testing Find-------\n";
//
//	ft::map<char, int >casa;
//
//	casa.insert(ft::pair<char, int>('a', 100));
//	casa.insert(ft::pair<char, int>('b', 200));
//	casa.insert(ft::pair<char, int>('c', 300));
//	casa.insert(ft::pair<char, int>('d', 400));
//	ft::map<char, int >::iterator pol;
//
//	pol = casa.find('b');
//
//	if (pol != casa.end())
//		casa.erase(pol->first);
//
//	std::cout << "elements in mymap:" << '\n';
//	std::cout << "a => " << casa.find('a')->second << '\n';
//	std::cout << "c => " << casa.find('c')->second << '\n';
//	std::cout << "d => " << casa.find('d')->second << '\n';
//
//	std::cout << "------Testing Count-------\n";
//
//	std::map<char,int> mymaps;
//	char c;
//
//	mymaps ['a']=101;
//	mymaps ['c']=202;
//	mymaps ['f']=303;
//
//	for (c='a'; c<'h'; c++)
//	{
//		std::cout << c;
//		if (mymaps.count(c)>0)
//			std::cout << " is an element of mymap.\n";
//		else
//			std::cout << " is not an element of mymap.\n";
//	}
//
//	std::cout << "-----Testing Lower Upper Band-----\n";
//
//	std::map<char,int> myma;
//	std::map<char,int>::iterator itlow,itup;
//
//	myma['a']=20;
//	myma['b']=40;
//	myma['c']=60;
//	myma['d']=80;
//	myma['e']=100;
//
//	itlow=myma.lower_bound ('b');  // itlow points to b
//	itup=myma.upper_bound ('d');   // itup points to e (not d!)
//
//	myma.erase(itlow,itup);        // erases [itlow,itup)
//
//	// print content:
//	for (std::map<char,int>::iterator it=myma.begin(); it!=myma.end(); ++it)
//		std::cout << it->first << " => " << it->second << '\n';
//
//
//	std::cout << "-----Testing Equal Range-------\n";
//	std::map<char,int> mymapo;
//
//	mymapo['a']=10;
//	mymapo['b']=20;
//	mymapo['c']=30;
//
//	std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> retss;
//	retss = mymapo.equal_range('b');
//
//	std::cout << "lower bound points to: ";
//	std::cout << retss.first->first << " => " << retss.first->second << '\n';
//
//	std::cout << "upper bound points to: ";
//	std::cout << retss.second->first << " => " << retss.second->second << '\n';
//
//
//	std::cout << "--------Testing Get ALLOCATOR--------\n";
//
//
//	int psize;
//	std::map<char,int> mymappp;
//	std::pair<const char,int>* p;
//
//	// allocate an array of 5 elements using mymap's allocator:
//	p=mymappp.get_allocator().allocate(5);
//
//	// assign some values to array
//	psize = sizeof(std::map<char,int>::value_type)*5;
//
//	std::cout << "The allocated array has a size of " << psize << " bytes.\n";
//
//	mymappp.get_allocator().deallocate(p,5);


	ft::vector<int> myvector (5);  // 5 default-constructed ints

	int i=0;

	ft::vector<int>::reverse_iterator rit = myvector.rbegin();
	for (; rit!= myvector.rend(); ++rit)
	{
		*rit = ++i;
		std::cout << " -==> " << *rit << std::endl;
	}
	std::cout << "ewe \n";
	std::cout << "myvector contains:";
	ft::vector<int>::const_iterator it = myvector.begin();
	std::cout << "WPW\n";
	std::cout << ' ' << *it;
//	for (ft::vector<int>::const_iterator  it = myvector.begin(); it != myvector.end(); ++it)
//	{
//		std::cout << ' ' << *it;
//	}it
	std::cout << '\n';


	return 0;
}