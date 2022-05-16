
#include <vector>
#include <iostream>
#include <map>
#include <unistd.h>
#include <sys/time.h>
#include "vector.hpp"
#include "is_integral.hpp"
#include "map.hpp"


#include <vector>
#include <iostream>
#include <iterator>
#include <utility>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <random>


#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
#define TIME_FAC 20

typedef std::pair<std::map<int, std::string>::iterator, std::map<int, std::string>::iterator> iter_def;
typedef ft::pair<ft::map<int, std::string>::iterator, ft::map<int, std::string>::iterator> ft_iter_def;
typedef std::pair<std::map<int, std::string>::const_iterator, std::map<int, std::string>::const_iterator> const_iter_def;
typedef ft::pair<ft::map<int, std::string>::const_iterator, ft::map<int, std::string>::const_iterator> ft_const_iter_def;

template <typename Iter1, typename Iter2>
bool compareMaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
	for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		if (first1->first != first2->first || first1->second != first2->second)
			return false;
	return true;
}

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp
{
	bool operator()(const char &lhs, const char &rhs) const
	{
		return lhs < rhs;
	}
};




bool testMapConstructors()
{
	bool cond;
	std::map<char, int> first;
	ft::map<char, int> m_first;

	for (size_t i = 97; i < 110; i++)
	{
		first[i - 97] = i;
		m_first[i - 97] = i;
	}

	std::map<char, int> copy(first);
	ft::map<char, int> m_copy(m_first);

	cond = first.size() == m_first.size() && compareMaps(first.begin(), first.end(), m_first.begin(), m_first.end());

	std::map<char, int> second(first.begin(), first.end());
	ft::map<char, int> m_second(m_first.begin(), m_first.end());

	cond = cond && second.size() == m_second.size() && compareMaps(second.begin(), second.end(), m_second.begin(), m_second.end());
	std::map<char, int> third(second);
	ft::map<char, int> m_third(m_second);

	cond = cond && third.size() == m_third.size() && compareMaps(third.begin(), third.end(), m_third.begin(), m_third.end());

	std::map<char, int, classcomp> fourth;  // class as Compare
	ft::map<char, int, classcomp> m_fourth; // class as Compare

	cond = fourth.size() == m_fourth.size() && cond && compareMaps(fourth.begin(), fourth.end(), m_fourth.begin(), m_fourth.end());

	bool (*fn_pt)(char, char) = fncomp;
	std::map<char, int, bool (*)(char, char)> fifth(fn_pt);  // function pointer as Compare
	ft::map<char, int, bool (*)(char, char)> m_fifth(fn_pt); // function pointer as Compare

	cond = fifth.size() == m_fifth.size() && cond && compareMaps(fifth.begin(), fifth.end(), m_fifth.begin(), m_fifth.end());

	first = std::map<char, int>();
	m_first = ft::map<char, int>();

	cond = copy.size() == m_copy.size() && cond && compareMaps(copy.begin(), copy.end(), m_copy.begin(), m_copy.end());

	return cond;
}

time_t get_time(void)
{
	struct timeval time_now;

	gettimeofday(&time_now, NULL);
	time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
	return (msecs_time);
}

void testConstructors()
{
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " empty constructor "
			  << "] --------------------]\t\t\033[0m";
	{
		/*---------------------------------- time limit test --------------------------------------------*/
		/*{
			time_t start, end, diff;

			start = get_time();
			std::map<int, std::string> m;
			for (int i = 0; i < 1e6; ++i)
				m.insert(std::make_pair(i, "fill constructor test"));
			end = get_time();
			diff = end - start;
			diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

			ualarm(diff * 1e3, 0);

			ft::map<int, std::string> my_m;
			for (int i = 0; i < 1e6; ++i)
				my_m.insert(ft::make_pair(i, "fill constructor test"));
			ualarm(0, 0);
		}*/
		/*----------------------------------------------------------------------------------------------*/
		/*--------------- fill tow vectors with a 10 strings ------*/
		ft::map<int, std::string> my_m;
		std::map<int, std::string> m;
		for (int i = 0; i < 10; i++)
		{
			m.insert(std::make_pair(i, "Hello"));
			my_m.insert(ft::make_pair(i, "Hello"));
		}

		/*---------------------------------------------------------*/
		/*--------------- declare tow strings to store the results ------*/
		std::string res, my_res;
		/*---------------------------------------------------------*/
		for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it) // fill res from std::map
			res += it->second;
		for (ft::map<int, std::string>::iterator it = my_m.begin(); it != my_m.end(); ++it) // fill res from std::map
			my_res += it->second;
		EQUAL(res == my_res);
	}
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " range constructor "
			  << "] --------------------]\t\t\033[0m";
	{
		/*---------------------------------- time limit test --------------------------------------------*/
		/*{
			time_t start, end, diff;
			std::map<int, std::string> m;
			ft::map<int, std::string> my_m;

			for (size_t i = 0; i < 1e6; i++)
			{
				m.insert(std::make_pair(i, "range constructor test"));
				my_m.insert(ft::make_pair(i, "range constructor test"));
			}

			start = get_time();
			std::map<int, std::string> m1(m.begin(), m.end());
			end = get_time();
			diff = end - start;
			diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

			ualarm(diff * 1e3, 0);
			ft::map<int, std::string> my_m1(my_m.begin(), my_m.end());
			ualarm(0, 0);
		}*/
		/*-----------------------------------------------------------------------------------------------*/
		/*--------------- fill std::map with 10 strings and ft::map with range of iterators ------*/
		std::map<int, std::string> m;
		ft::map<int, std::string> my_m;
		for (size_t i = 0; i < 10; i++)
		{
			m.insert(std::make_pair(i, "range constructor test"));
			my_m.insert(ft::make_pair(i, "range constructor test"));
		}

		ft::map<int, std::string> my_m1(my_m.begin(), my_m.end()); // this one is to check if the range works with ft::map
		/*----------------------------------------------------------------------------------------------*/
		/*--------------- declare tow strings to store the results ------*/
		std::string res, my_res, my_res1;
		int sum(0), my_sum(0), my_sum1(0);
		/*--------------------------------------------------------*/
		for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it)
		{ // fill res from std::map
			res += it->second;
			sum += it->first;
		}

		for (ft::map<int, std::string>::iterator it = my_m.begin(); it != my_m.end(); ++it)
		{ // fill my_res from ft::map
			my_res += it->second;
			my_sum += it->first;
		}

		for (ft::map<int, std::string>::iterator it = my_m1.begin(); it != my_m1.end(); ++it)
		{ // fill my_res1 from ft::map
			my_res1 += it->second;
			my_sum1 += it->first;
		}
		EQUAL(res == my_res && my_res == my_res1);
	}
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
			  << "] --------------------]\t\t\033[0m";
	{
		/*---------------------------------- time limit test --------------------------------------------*/
		/*{
			time_t start, end, diff;
			std::map<int, char> m;
			ft::map<int, char> my_m;

			for (size_t i = 0; i < 1e3; i++)
			{
				m.insert(std::make_pair(i, 'X'));
				my_m.insert(ft::make_pair(i, 'X'));
			}

			start = get_time();
			std::map<int, char> copy_m(m);
			end = get_time();
			diff = end - start;
			diff = (diff) ? (diff * 20) : 20;

			alarm(diff);
			ft::map<int, char> my_copy_m(my_m);
			alarm(0);
		}*/
		/*---------------------------------------------------------------------------------------------*/
		/*---------------------------- declare a vector and fill with 'a', and create a copy of it ------------------*/
		ft::map<int, char> m1;
		for (int i = 0; i < 10; i++)
			m1.insert(ft::make_pair(i, 'a'));
		ft::map<int, char> copy_m(m1);
		/*-----------------------------------------------------------------------------------------------------------*/
		/*--------------- declare tow strings to store the results ------*/
		std::string res, res1;
		/*--------------------------------------------------------*/
		for (ft::map<int, char>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
			res += it->second;

		for (ft::map<int, char>::iterator it = copy_m.begin(); it != copy_m.end(); ++it) // fill res from copy_m
			res1 += it->second;
		EQUAL(res == res1);
	}
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " Constructors with costum compare "
			  << "] --------------------]\t\t\033[0m";
	//EQUAL(testMapConstructors());
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator= (lhs.size = rhs.size) "
			  << "] --------------------]\t\t\033[0m";
	{
		/*-------------------------------------- time limit test -----------------------------------*/
		// {
		//     time_t start, end, diff;
		//     std::map<int, std::string> m1;
		//     std::map<int, std::string> m2;
		//     ft::map<int, std::string> ft_m1;
		//     ft::map<int, std::string> ft_m2;
		//     for (int i = 0; i < 1e6; ++i)
		//     {
		//         m1.insert(std::make_pair(i, "string1"));
		//         m2.insert(std::make_pair(i, "string2"));
		//         ft_m1.insert(ft::make_pair(i, "string1"));
		//         ft_m2.insert(ft::make_pair(i, "string2"));
		//     }

		//     start = get_time();
		//     m1 = m2;
		//     end = get_time();
		//     diff = end - start;
		//     diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
		//     /*-----------------------------------------------------*/
		//     /*------------------ ft::map ---------------------*/
		//     ualarm(diff * 1e3, 0);
		//     ft_m1 = ft_m2;
		//     ualarm(0, 0);
		//     /*----------------------------------------------------*/
		// }
		/*------------------------------------------------------------------------------------------*/
		/*------------------ std::map ---------------------*/
		std::map<int, std::string> m1;
		std::map<int, std::string> m2;
		ft::map<int, std::string> ft_m1;
		ft::map<int, std::string> ft_m2;
		for (int i = 0; i < 10; ++i)
		{
			m1.insert(std::make_pair(i, "string1"));
			m2.insert(std::make_pair(i, "string2"));
			ft_m1.insert(ft::make_pair(i, "string1"));
			ft_m2.insert(ft::make_pair(i, "string2"));
		}

		m1 = m2;
		ft_m1 = ft_m2;
		/*----------------------------------------------------*/
		/*------------------ strings to store the results ----*/
		std::string res, ft_res;
		/*----------------------------------------------------*/
		for (std::map<int, std::string>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
			res += it->first;

		for (ft::map<int, std::string>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
			ft_res += it->first;

		EQUAL(res == ft_res);
	}

	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator= deep copy "
			  << "] --------------------]\t\t\033[0m";
	{
		std::map<int, std::string> m1;
		std::map<int, std::string> m2;
		ft::map<int, std::string> ft_m2;
		ft::map<int, std::string> ft_m1;
		for (int i = 0; i < 20; ++i)
		{
			m2.insert(std::make_pair(i, "string2"));
			ft_m2.insert(ft::make_pair(i, "string2"));
		}

		m1 = m2;
		ft_m1 = ft_m2;
		m2.begin()->second = "hello";
		ft_m2.begin()->second = "hello";

		EQUAL((m1.begin()->second != m2.begin()->second) && (ft_m1.begin()->second != ft_m2.begin()->second));
	}

	/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
	/*------------------------------------------ test 2 : test with diff size vecotrs ----------------------------------------------------------------------*/
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size < rhs.size) "
			  << "] --------------------]\t\t\033[0m";
	{
		/*-------------------------------------- time limit test -----------------------------------*/
		// {
		//     time_t start, end, diff;
		//     /*------------------ std::map ---------------------*/
		//     std::map<int, std::string> m1;
		//     std::map<int, std::string> m2;
		//     ft::map<int, std::string> ft_m1;
		//     ft::map<int, std::string> ft_m2;

		//     for (int i = 0; i < 1e4; ++i)
		//     {
		//         m1.insert(std::make_pair(i, "string1"));
		//         ft_m1.insert(ft::make_pair(i, "string1"));
		//     }

		//     for (int i = 0; i < 1e6; ++i)
		//     {
		//         m2.insert(std::make_pair(i, "string2"));
		//         ft_m2.insert(ft::make_pair(i, "string2"));
		//     }

		//     start = get_time();
		//     m1 = m2;
		//     end = get_time();
		//     diff = end - start;
		//     diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
		//     /*-----------------------------------------------------*/
		//     /*------------------ ft::map ---------------------*/
		//     ualarm(diff * 1e3, 0);
		//     ft_m1 = ft_m2;
		//     ualarm(0, 0);
		//     /*----------------------------------------------------*/
		// }
		/*------------------------------------------------------------------------------------------*/
		/*------------------ std::map ---------------------*/
		std::map<int, std::string> m1;
		std::map<int, std::string> m2;
		ft::map<int, std::string> ft_m1;
		ft::map<int, std::string> ft_m2;
		for(size_t i = 0; i < 20; ++i)
		{
			m2.insert(std::make_pair(i, "value"));
			ft_m2.insert(ft::make_pair(i, "value"));
		}
		m1 = m2;
		/*-----------------------------------------------------*/
		/*------------------ ft::map ---------------------*/
		ft_m1 = ft_m2;
		/*----------------------------------------------------*/
		/*------------------ strings to store the results ----*/
		std::string res, ft_res;
		/*----------------------------------------------------*/
		for (std::map<int, std::string>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
			res += it->second;

		for (ft::map<int, std::string>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
			ft_res += it->second;

		EQUAL(res == ft_res);
	}
	/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
	/*------------------------------------------ test 3 : test with diff size vecotrs ----------------------------------------------------------------------*/
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size > rhs.size) "
			  << "] --------------------]\t\t\033[0m";
	{
		/*-------------------------------------- time limit test -----------------------------------*/
		// {
		//     time_t start, end, diff;
		//     /*------------------ std::map ---------------------*/
		//     std::map<int, std::string> m1;
		//     std::map<int, std::string> m2;
		//     ft::map<int, std::string> ft_m1;
		//     ft::map<int, std::string> ft_m2;

		//     for (int i = 0; i < 1e4; ++i)
		//     {
		//         m1.insert(std::make_pair(i, "string1"));
		//         ft_m1.insert(ft::make_pair(i, "string1"));
		//     }

		//     for (int i = 0; i < 1e2; ++i)
		//     {
		//         m2.insert(std::make_pair(i, "string2"));
		//         ft_m2.insert(ft::make_pair(i, "string2"));
		//     }
		//     start = get_time();
		//     m1 = m2;
		//     end = get_time();
		//     diff = end - start;
		//     diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
		//     /*-----------------------------------------------------*/
		//     /*------------------ ft::map ---------------------*/
		//     ualarm(diff * 1e3, 0);
		//     ft_m1 = ft_m2;
		//     ualarm(0, 0);
		//     /*----------------------------------------------------*/
		// }
		/*------------------------------------------------------------------------------------------*/
		/*------------------ std::map ---------------------*/
		std::map<int, std::string> m1;
		std::map<int, std::string> m2;
		ft::map<int, std::string> ft_m1;
		ft::map<int, std::string> ft_m2;

		for (int i = 0; i < 20; ++i)
		{
			m1.insert(std::make_pair(i, "string1"));
			ft_m1.insert(ft::make_pair(i, "string1"));
		}

		for (int i = 0; i < 10; ++i)
		{
			m2.insert(std::make_pair(i, "string2"));
			ft_m2.insert(ft::make_pair(i, "string2"));
		}
		m1 = m2;
		/*-----------------------------------------------------*/
		/*------------------ ft::map ---------------------*/
		ft_m1 = ft_m2;
		/*----------------------------------------------------*/
		/*------------------ strings to store the results ----*/
		std::string res, ft_res;
		/*----------------------------------------------------*/
		for (std::map<int, std::string>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
			res += it->second;

		for (ft::map<int, std::string>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
			ft_res += it->second;

		EQUAL(res == ft_res);
	}
	/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
	/*------------------------------------------ test 4 : test with one empty vector ----------------------------------------------------------------------*/
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size = 0) "
			  << "] --------------------]\t\t\033[0m";
	{
		/*-------------------------------------- time limit test -----------------------------------*/
		// {
		//     time_t start, end, diff;
		//     std::map<int, std::string> m1;
		//     std::map<int, std::string> m2;
		//     ft::map<int, std::string> ft_m1;
		//     ft::map<int, std::string> ft_m2;

		//     for (int i = 0; i < 1e6; ++i)
		//     {
		//         m2.insert(std::make_pair(i, "string2"));
		//         ft_m2.insert(ft::make_pair(i, "string2"));
		//     }

		//     start = get_time();
		//     m1 = m2;
		//     end = get_time();
		//     diff = end - start;
		//     diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
		//     /*-----------------------------------------------------*/
		//     /*------------------ ft::map ---------------------*/
		//     ualarm(diff * 1e3, 0);
		//     ft_m1 = ft_m2;
		//     ualarm(0, 0);
		//     /*----------------------------------------------------*/
		// }
		/*------------------------------------------------------------------------------------------*/
		/*------------------ std::map ---------------------*/
		std::map<int, std::string> m1;
		std::map<int, std::string> m2;
		ft::map<int, std::string> ft_m1;
		ft::map<int, std::string> ft_m2;

		for (int i = 0; i < 10; ++i)
		{
			m2.insert(std::make_pair(i, "string2"));
			ft_m2.insert(ft::make_pair(i, "string2"));
		}
		m1 = m2;
		/*-----------------------------------------------------*/
		/*------------------ ft::map ---------------------*/

		ft_m1 = ft_m2;
		/*----------------------------------------------------*/
		/*------------------ strings to store the results ----*/
		std::string res, ft_res;
		/*----------------------------------------------------*/
		for (std::map<int, std::string>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
			res += it->second;

		for (ft::map<int, std::string>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
			ft_res += it->second;

		EQUAL(res == ft_res);
	}
	/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
	/*------------------------------------------ test 5 : test with one empty vector ----------------------------------------------------------------------*/
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (rhs.size = 0) "
			  << "] --------------------]\t\t\033[0m";
	{
		/*-------------------------------------- time limit test -----------------------------------*/
		// {
		//     time_t start, end, diff;
		//     /*------------------ std::nap ---------------------*/
		//     std::map<int, std::string> m1;
		//     std::map<int, std::string> m2;
		//     ft::map<int, std::string> ft_m1;
		//     ft::map<int, std::string> ft_m2;

		//     for (int i = 0; i < 1e6; ++i)
		//     {
		//         m1.insert(std::make_pair(i, "string1"));
		//         ft_m1.insert(ft::make_pair(i, "string1"));
		//     }
		//     start = get_time();
		//     m1 = m2;
		//     end = get_time();
		//     diff = end - start;
		//     diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
		//     /*-----------------------------------------------------*/
		//     /*------------------ ft::map ---------------------*/
		//     ualarm(diff * 1e3, 0);
		//     ft_m1 = ft_m2;
		//     ualarm(0, 0);
		//     /*----------------------------------------------------*/
		// }
		/*------------------------------------------------------------------------------------------*/
		/*------------------ std::map ---------------------*/
		std::map<int, std::string> m1;
		std::map<int, std::string> m2;
		ft::map<int, std::string> ft_m1;
		ft::map<int, std::string> ft_m2;

		for (int i = 0; i < 10; ++i)
		{
			m1.insert(std::make_pair(i, "string2"));
			ft_m1.insert(ft::make_pair(i, "string2"));
		}
		m1 = m2;
		/*-----------------------------------------------------*/
		/*------------------ ft::map ---------------------*/
		ft_m1 = ft_m2;
		/*----------------------------------------------------*/
		/*------------------ strings to store the results ----*/
		std::string res, ft_res;
		/*----------------------------------------------------*/
		for (std::map<int, std::string>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
			res += it->second;

		for (ft::map<int, std::string>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
			ft_res += it->second;

		EQUAL(res == ft_res);
	}
}


void iterator_tests(void)
{
	/*------------ std::map ---------*/
	std::map<int, char> m;
	std::map<int, char>::iterator it, it1;

	ft::map<int, char> my_m;
	ft::map<int, char>::iterator my_it, my_it1, tmp;

	for (int i = 0; i < 10; ++i)
	{
		my_m.insert(ft::make_pair(i, static_cast<char>(i + 97)));
		m.insert(std::make_pair(i, static_cast<char>(i + 97)));
	}

	it = m.begin();
	it1 = ++(m.begin());
	my_it = my_m.begin();
	my_it1 = ++(my_m.begin());
	/*----------------------------------*/
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
			  << "] --------------------]\t\t\033[0m";
	{
		ft::map<int, char>::iterator ob(my_it);
		EQUAL(&(*my_it) == &(*ob));
	}
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " iterator to const_iterator "
			  << "] --------------------]\t\t\033[0m";
	{
		ft::map<int, char>::const_iterator c_it, c_ob(my_it);
		c_it = my_it;
		EQUAL(&(*my_it) == &(*c_it) && (&(*my_it) == &(*c_ob)));
	}
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
			  << "] --------------------]\t\t\033[0m";
	EQUAL((it == it1) == (my_it == my_it1));
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
			  << "] --------------------]\t\t\033[0m";
	EQUAL((it != it1) == (my_it != my_it1));
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
			  << "] --------------------]\t\t\033[0m";
	EQUAL((((*my_it).second = '6') == '6') && ((*my_it).first == ((*my_m.begin()).first)));
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
			  << "] --------------------]\t\t\033[0m";
	{
		/*--------------- std::map-------------------- */
		std::map<int, std::string> m;
		ft::map<int, std::string> my_m;

		for (int i = 0; i < 5; ++i)
		{
			m.insert(std::make_pair(13, "HELLO"));
			my_m.insert(ft::make_pair(13, "HELLO"));
		}

		ft::map<int, std::string>::iterator my_it = my_m.begin();
		std::map<int, std::string>::iterator it = m.begin();
		/*---------------------------------------------- */
		EQUAL(it->second.length() == my_it->second.length());
	}
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++it operator "
			  << "] --------------------]\t\t\033[0m";
	{
		/*---------------------------------- time limit test --------------------------------------------*/
		/*{
			time_t start, end, diff;

			std::map<int, std::string> m;
			ft::map<int, std::string> ft_m;
			for (size_t i = 0; i < 1e6; ++i)
			{
				m.insert(std::make_pair(i, "value"));
				ft_m.insert(ft::make_pair(i, "value"));
			}
			start = get_time();
			for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it)
				;
			end = get_time();
			diff = end - start;
			diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

			ualarm(diff * 1e3, 0);
			for (ft::map<int, std::string>::iterator it = ft_m.begin(); it != ft_m.end(); ++it)
				;
			ualarm(0, 0);
		}*/
		bool cond(false);
		{
			int res(0);
			int myints[] = {12, 82, 37, 64, 15};
			ft::map<int, int> m;
			for (size_t i = 0; i < 5; ++i)
				m.insert(ft::make_pair(myints[i], i));
			for (ft::map<int, int>::iterator it = m.begin(); it != m.end(); ++it)
				res += it->first;
			cond = res == 210;
		}
		{
			int res(0), tmp;
			int myints[] = {12, 82, 37, 64, 15};
			ft::map<int, int> m;
			for (size_t i = 0; i < 5; ++i)
				m.insert(ft::make_pair(myints[i], i));
			ft::map<int, int>::iterator it = m.begin(), eit = --m.end();
			tmp = eit->first;
			m.erase(eit);
			for (; it != m.end(); ++it)
				res += it->first;
			cond = cond && (res == (210 - tmp));
		}
		++my_it; // I incremented here to make sure that the object changes
		EQUAL(*my_it == *my_it1);


	}
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --it operator "
			  << "] --------------------]\t\t\033[0m";
	{
		/*---------------------------------- time limit test --------------------------------------------*/
		/*{
			time_t start, end, diff;

			std::map<int, std::string> m;
			ft::map<int, std::string> ft_m;
			for (size_t i = 0; i < 1e6; ++i)
			{
				m.insert(std::make_pair(i, "value"));
				ft_m.insert(ft::make_pair(i, "value"));
			}
			start = get_time();
			std::map<int, std::string>::iterator it = --m.end();
			for (; it != m.begin(); --it)
				;
			end = get_time();
			diff = end - start;
			diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

			ualarm(diff * 1e3, 0);
			ft::map<int, std::string>::iterator ft_it = --ft_m.end();
			for (; ft_it != ft_m.begin(); --ft_it)
				;
			ualarm(0, 0);
		}*/
		int res(0);
		{
			int myints[] = {12, 82, 37, 64, 15};
			ft::map<int, int> m;
			for (size_t i = 0; i < 5; ++i)
				m.insert(ft::make_pair(myints[i], i));
			ft::map<int, int>::iterator it = --m.end();
			for (;; --it)
			{
				if (it == m.begin())
				{
					res += it->first;
					break;
				}
				res += it->first;
			}
		}
		--my_it; // I decremented here to make sure that the object changes
		EQUAL(*my_it != *my_it1);
	}
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it++ operator "
			  << "] --------------------]\t\t\033[0m";
	tmp = my_it++;
	EQUAL(*my_it != *tmp && *my_it == *my_it1);
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it-- operator "
			  << "] --------------------]\t\t\033[0m";
	tmp = my_it--;
	EQUAL(*my_it != *tmp && *my_it == *(my_m.begin()));
}


void const_iterator_tests(void)
{
	/*------------ std::map ---------*/
	std::map<int, char> m;
	std::map<int, char>::const_iterator it, it1;

	ft::map<int, char> my_m;
	ft::map<int, char>::const_iterator my_it, my_it1, tmp;

	for (int i = 0; i < 10; ++i)
	{
		my_m.insert(ft::make_pair(i, static_cast<char>(i + 97)));
		m.insert(std::make_pair(i, static_cast<char>(i + 97)));
	}

	it = m.begin();
	it1 = ++(m.begin());
	my_it = my_m.begin();
	my_it1 = ++(my_m.begin());
	/*----------------------------------*/

	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
			  << "] --------------------]\t\t\033[0m";
	{
		ft::map<int, char>::const_iterator ob(my_it);
		EQUAL(*my_it == *ob);
	}
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
			  << "] --------------------]\t\t\033[0m";
	EQUAL((it == it1) == (my_it == my_it1));
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
			  << "] --------------------]\t\t\033[0m";
	EQUAL((it != it1) == (my_it != my_it1));
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
			  << "] --------------------]\t\t\033[0m";
	{
		/*--------------- std::map-------------------- */
		std::map<int, std::string> m;
		ft::map<int, std::string> my_m;

		for (int i = 0; i < 5; ++i)
		{
			m.insert(std::make_pair(13, "HELLO"));
			my_m.insert(ft::make_pair(13, "HELLO"));
		}

		ft::map<int, std::string>::iterator my_it = my_m.begin();
		std::map<int, std::string>::iterator it = m.begin();
		/*---------------------------------------------- */
		EQUAL(it->second.length() == my_it->second.length());
	}
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++it operator "
			  << "] --------------------]\t\t\033[0m";
	++my_it; // I incremented here to make sure that the object changes
	EQUAL(*my_it == *my_it1);
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --it operator "
			  << "] --------------------]\t\t\033[0m";
	--my_it; // I decremented here to make sure that the object changes
	EQUAL(*my_it != *my_it1);
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it++ operator "
			  << "] --------------------]\t\t\033[0m";
	tmp = my_it++;
	EQUAL(*my_it != *tmp && *my_it == *my_it1);
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it-- operator "
			  << "] --------------------]\t\t\033[0m";
	tmp = my_it--;
	EQUAL(*my_it != *tmp && *my_it == *(my_m.begin()));
}


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
*/
//	std::cout << "**** Testing is Integral ****\n";
//
//	std::cout << "char: " <<ft::is_integral<char>::value << std::endl;
//	std::cout << "int: " << ft::is_integral<int>::value << std::endl;
//endl	std::cout << "float: " << ft::is_integral<float>::value << std::endl;
/*
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


//	ft::vector<int> myvector (5);  // 5 default-constructed ints
//
//	int i=0;
//
//	std::cout << "Start\n";
//
//	ft::vector<int>::reverse_iterator rit = myvector.rbegin();
//	for (; rit!= myvector.rend(); ++rit)
//	{
//		*rit = ++i;
//		std::cout << " -==> " << *rit << std::endl;
//	}
//	std::cout << "ewe \n";
//	std::cout << "myvector contains:";
//	ft::vector<int>::const_iterator it = myvector.begin();
//	std::cout << "WPW\n";
//	std::cout << ' ' << *it;
////	for (ft::vector<int>::const_iterator  it = myvector.begin(); it != myvector.end(); ++it)
////	{
////		std::cout << ' ' << *it;
////	}it
//	std::cout << '\n';n


//	ft::vector<int> first;                                // empty vector of ints
//	ft::vector<int> second (4,100);                       // four ints with value 100
//	ft::vector<int> third (second.begin(),second.end());  // iterating through second
//	ft::vector<int> fourth (third);                       // a copy of third
//
//	// the iterator constructor can also be used to construct from arrays:
//
//	std::cout << "The contents of fifth are:";
//	for (ft::vector<int>::iterator it = fourth.begin(); it != fourth.end(); it++)
//	{
//		std::cout << ' ' << *it;
//	}
//	std::cout << '\n';

//	ft::vector<int> v(4, 5);
//
//	ft::vector<int>::reverse_iterator my_rit2(v.end());
//	ft::vector<int>::const_reverse_iterator c_it, c_ob(v.end());
//
//	c_it = my_rit2;



	/*------------------ std::vectors ---------------------*/
//	ft::vector<std::string> ft_v1(1e6, "string2");
//	// std::vector<std::string>    v1(1e6, "string2");
//	std::vector<std::string> v2(1e4, "string2");
//	start = get_time();
//	v2.assign(ft_v1.begin(), ft_v1.end());
//	end = get_time();
//	diff = end - start;
//	diff = (diff) ? (diff * 5) : 5;
//	/*------------------ ft::vectors ---------------------*/
//	// ft::vector<std::string>    ft_v1(1e6, "string2");
//	ft::vector<std::string> ft_v2(1e4, "string2");
//	ualarm(diff * 1e3, 0);
//	ft_v2.assign(ft_v1.begin(), ft_v1.end());
//	ualarm(0, 0);


//	time_t start, end, diff;
//	/*------------------ std::vectors ---------------------*/
//
//	std::vector<std::string> v1(1e6, "string2");
//	v1.reserve(1e6 + 1);
//	start = get_time();
//	v1.push_back("string1");
//	end = get_time();
//	diff = end - start;
//	diff = (diff) ? (diff * 5) : 5;
//	/*------------------ ft::vectors ---------------------*/
//	ft::vector<std::string> ft_v1(1e6, "string2");
//	ft_v1.reserve(1e6 + 1);
//	//ualarm(diff * 1e3, 0);
//	ft_v1.push_backback("string1");
	//ualarm(0, 0);


//	std::vector<std::string> v1(10, "string");string
//	std::vector<int> v2;
//	std::vector<double> v4;
//	/*-----------------------------------------------------*/
//	/*------------------ ft::vectors ---------------------*/
//	ft::vector<std::string> ft_v1(10, "string2");
//	ft::vector<int> ft_v2;
//	ft::vector<double> ft_v4;
//
//	std::cout << "MaxS  V1==> " << v1.max_size() << std::endl;
//	std::cout << "MaxS  v2==> " << v2.max_size() << std::endl;
//	std::cout << "MaxS  v4==> " << v4.max_size() << std::endl;
//	std::cout << "MaxS  ft_v1==> " << ft_v1.max_size() << std::endl;
//	std::cout << "MaxS  ft_v2==> " << ft_v2.max_size() << std::endl;
//	std::cout << "MaxS  ft_v4==> " << ft_v4.max_size() << std::endl;



	/*------------------------------- test 1: empty vector ----------------------------------------*/
	// insert at the begin
//	{
//		std::vector<std::string> v;
//		ft::vector<std::string> ft_v;
//		it = v.insert(v.begin(), "hello");
//		ft_it = ft_v.insert(ft_v.begin(), "hello");
//		ft_it->length();
//
//		s = v.size();
//		ft_s = ft_v.size();
//		c = v.capacity();
//		ft_c = ft_v.capacity();
//		for (size_t i = 0; i < v.size(); ++i)
//			str += v[i];
//		for (size_t i = 0; i < ft_v.size(); ++i)
//			ft_str += ft_v[i];
//		cond = ((str == ft_str) && (s == ft_s) && (c == ft_c) && (*ft_it == *it));
//	}
//	// insert at the end
//	{
//		std::vector<std::string> v;
//		ft::vector<std::string> ft_v;
//
//		it = v.insert(v.end(), "hello");
//		ft_it = ft_v.insert(ft_v.end(), "hello");
//		ft_it->length();
//
//		str.clear();
//		ft_str.clear();
//
//		s = v.size();
//		ft_s = ft_v.size();
//		c = v.capacity();
//		ft_c = ft_v.capacity();
//		for (size_t i = 0; i < v.size(); ++i)
//			str += v[i];
//		for (size_t i = 0; i < ft_v.size(); ++i)
//			ft_str += ft_v[i];
//		cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (*it == *ft_it));
//	}
//	/*---------------------------------------------------------------------------------------------------*/
//	/*------------------------------- test 2: the vector capacity >= size + the new element ----------------------------------------*/
//	{
//		std::vector<std::string> v(20, "string");
//		ft::vector<std::string> ft_v(20, "string");
//		ft::vector<std::string>::iterator valid_it;
//
//		v.reserve(30);
//		ft_v.reserve(30);
//		valid_it = ft_v.begin();
//		it = v.insert(v.begin() + 10, "hello");
//		ft_it = ft_v.insert(ft_v.begin() + 10, "hello");
//		ft_it->length();
//
//		str.clear();
//		ft_str.clear();
//		s = v.size();
//		ft_s = ft_v.size();
//		c = v.capacity();
//		ft_c = ft_v.capacity();
//		for (size_t i = 0; i < v.size(); ++i)
//			str += v[i];
//		for (size_t i = 0; i < ft_v.size(); ++i)
//			ft_str += ft_v[i];
//		cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (*it == *ft_it) && (&(*valid_it) == &(*ft_v.begin())));
//	}
	/*---------------------------------------------------------------------------------------------------*/
	/*------------------------------- test 3: the vector capacity < size + the new element ----------------------------------------*/





	/*------------------------------- test 1: empty vector ----------------------------------------*/
	// insert at the begin
//	{begin
//		std::cout << "HER1\n";
		/*
//		 * var tomatoes store the size and the capacity
//		 */
//		ft::vector<std::string>::size_type s, ft_s;
//		ft::vector<std::string>::size_type c, ft_c;
//		ft::vector<std::string>::iterator ft_it;
//		std::vector<std::string>::iterator it;
//		/*
//		 * bool to store the comparison
//		 */
//		bool cond;
//		condstd::vector<std::string> v1(300, "string");
//		std::vector<std::string> v;
//		ft::vector<std::string> ft_v;
//		v.insert(v.begin(), v1.begin(), v1.end());
//		ft_v.insert(ft_v.begin(), v1.begin(), v1.end());
//		ft_v.begin()->length();
//
//		s = v.size();
//		ft_s = ft_v.size();
//		c = v.capacity();
//		ft_c = ft_v.capacity();
//		for (size_t i = 0; i < v.size(); ++i)
//			str += v[i];
//		for (size_t i = 0; i < ft_v.size(); ++i)
//			ft_str += ft_v[i];
//		cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
//	}
//	// insert at the end
//	{
//		std::cout << "HER2\n";
//		std::vector<std::string> v;
//		ft::vector<std::string> v1(300, "string");
//		ft::vector<std::string> ft_v;
//
//		v.insert(v.end(), v1.begin(), v1.end());
//		ft_v.insert(ft_v.end(), v1.begin(), v1.end());
//		ft_v.begin()->length();
//
//		str.clear();
//		ft_str.clear();
//
//		s = v.size();
//		ft_s = ft_v.size();
//		c = v.capacity();
//		ft_c = ft_v.capacity();
//		for (size_t i = 0; i < v.size(); ++i)
//			str += v[i];
//		for (size_t i = 0; i < ft_v.size(); ++i)
//			ft_str += ft_v[i];
//		cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
//	}
	/*---------------------------------------------------------------------------------------------------*/
	/*------------------------------- test 2: the vector capacity >= size + n ----------------------------------------*/

//	std::vector<std::string> v(200, "hello");
//	ft::vector<std::string> ft_v(200, "hello");
//	ft::vector<std::string>::iterator valid_it;
//	std::vector<std::string>::iterator it;
//	ft::vector<std::string>::iterator ft_it;
//	valid_it = ft_v.begin() + 99;
//	it = v.erase(v.begin() + 100);
//	ft_it = ft_v.erase(ft_v.begin() + 100);
//	ft_it->length();
//
//	s = v.size();
//	ft_s = ft_v.size();
//	c = v.capacity();
//	ft_c = ft_v.capacity();
//	for (size_t i = 0; i < v.size(); ++i)
//		str += v[i];
//	for (size_t i = 0; i < ft_v.size(); ++i)
//		ft_str += ft_v[i];
//	//cond = ((str == ft_str) && (s == ft_s) && (c == ft_c) && (&(*valid_it) == &(*(ft_v.begin() + 99))));
//
//	std::cout << "Dist ==> " << std::distance(v.begin(), it ) << std::endl;
//	std::cout << "Dis1 ==> " <<std::distance(ft_v.begin(), ft_it) << std::endl;
//
//
//	cond = (/*cond && */(std::distance(v.begin(), it) == std::distance(ft_v.begin(), ft_it)));
//	EQUAL(cond);


//	{
//		std::vector<std::string> v(100, "hello");
//		ft::vector<std::string> ft_v(100, "hello");
//
//		it = v.erase(v.begin() + 60, v.end());
//		ft_it = ft_v.erase(ft_v.begin() + 60, ft_v.end());
//
//		str.clear();
//		ft_str.clear();
//		s = v.size();
//		ft_s = ft_v.size();
//		c = v.size();
//		ft_c = ft_v.size();
//		for (size_t i = 0; i < v.size(); ++i)
//			str += v[i];
//		for (size_t i = 0; i < ft_v.size(); ++i)
//			ft_str += ft_v[i];
//		cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
//		cond = (cond && (std::distance(v.begin(), it) == std::distance(ft_v.begin(), ft_it)));
//	}
//
//	/*--------------------------------------------------------------------------*/
//	/*------------------ test 4: erase from the begin + 20 to end - 30 -------------------*/
//	{
//		std::vector<std::string> v(100, "hello");
//		ft::vector<std::string> ft_v(100, "hello");
//
//		it = v.erase(v.begin() + 20, v.end() - 30);
//		ft_it = ft_v.erase(ft_v.begin() + 20, ft_v.end() - 30);
//		ft_it->length();
//
//		str.clear();
//		ft_str.clear();
//		s = v.size();
//		ft_s = ft_v.size();
//		c = v.size();
//		ft_c = ft_v.size();
//		for (size_t i = 0; i < v.size(); ++i)
//			str += v[i];
//		for (size_t i = 0; i < ft_v.size(); ++i)
//			ft_str += ft_v[i];
//		cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
//		cond = (cond && (std::distance(v.begin(), it) == std::distance(ft_v.begin(), ft_it)));
//	}
	/*--------------------------------------------------------------------------*/


// 	iterator_tests();
// //
// 	const_iterator_tests();
// //
// 	testConstructors();

		
        /*---------------------------------- time limit test --------------------------------------------*/
        // {
        //     time_t start, end, diff;
        //     iter_def res;
        //     ft_iter_def ft_res;

        //     std::map<int, std::string> m;
        //     ft::map<int, std::string> ft_m;
        //     for (size_t i = 0; i < 1e6; ++i)
        //     {
        //         m.insert(std::make_pair(i, "value"));
        //         ft_m.insert(ft::make_pair(i, "value"));
        //     }
        //     start = get_time();
        //     res = m.equal_range(1e5);
        //     end = get_time();
        //     diff = end - start;
        //     diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        //     ualarm(diff * 1e3, 0);
        //     ft_res = ft_m.equal_range(1e5);
        //     ualarm(0, 0);
        //     cond = (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first);
        // }



        bool cond(false);
        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::map<int, std::string> ft_m1;

            start = get_time();
            for (size_t i = 0; i < 1200; i++)
                m1.insert(std::make_pair(i, "string2"));
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
           /* ------------------ ft::maps ---------------------*/
 			//  ualarm(diff * 1e3, 0);
            for (size_t i = 0; i < 1200/*1e6*/; i++)
            	ft_m1.insert(ft::make_pair(i, "string2"));

            // ualarm(0, 0);
            //----------------------------------------------------
            //------------------ std::maps ---------------------
            std::map<int, std::string> m_range;
            ft::map<int, std::string> ft_m_range;

            start = get_time();
            m_range.insert(m1.begin(), m1.end());
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
           // ----------------------------------------------------
            //------------------ ft::maps ---------------------
            //  ualarm(diff * 1e3, 0);
            ft_m_range.insert(ft_m1.begin(), ft_m1.end());
            //  ualarm(0, 0);
           // ---------------------------------------------------
        }

        {
            time_t start, end, diff;
           // ------------------ std::maps ---------------------
            std::map<int, std::string> m1;
            ft::map<int, std::string> ft_m1;

            start = get_time();
            m1.insert(std::make_pair(1200/*1e9*/, "string2"));
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            //-----------------------------------------------------
           // ------------------ ft::maps ---------------------
            // ualarm(diff * 1e3, 0);
            ft_m1.insert(ft::make_pair(1200 /*1e9*/, "string2"));
            // ualarm(0, 0);
            //----------------------------------------------------
        }

        std::map<char, int> m;
        ft::map<char, int> ft_m;

        cond = m.size() == ft_m.size() && m.empty() == ft_m.empty();

        // first insert function version (single parameter):
        m.insert(std::pair<char, int>('a', 100));
        m.insert(std::pair<char, int>('z', 200));

        ft_m.insert(ft::pair<char, int>('a', 100));
        ft_m.insert(ft::pair<char, int>('z', 200));

        cond = cond && (m.size() == ft_m.size() && m.empty() == ft_m.empty());

        std::pair<std::map<char, int>::iterator, bool> ret;
        ft::pair<ft::map<char, int>::iterator, bool> ft_ret;

        ret = m.insert(std::pair<char, int>('z', 500));
        ft_ret = ft_m.insert(ft::pair<char, int>('z', 500));

        cond = cond && ret.second == ft_ret.second;

        // second insert function version (with hint position):
        std::map<char, int>::iterator it = m.begin();
        ft::map<char, int>::iterator ft_it = ft_m.begin();
        m.insert(it, std::pair<char, int>('b', 300));
        m.insert(it, std::pair<char, int>('c', 400));

        ft_m.insert(ft_it, ft::pair<char, int>('b', 300));
        ft_m.insert(ft_it, ft::pair<char, int>('c', 400));
        cond = cond && (m.size() == ft_m.size() && m.empty() == ft_m.empty());

        //for (ft::map<char, int>::iterator iter)

        // third insert function version (range insertion):
        std::map<char, int> anothermap;
        ft::map<char, int> ft_anothermap;
        anothermap.insert(m.begin(), m.find('c'));
        ft_anothermap.insert(ft_m.begin(), ft_m.find('c'));

        cond = cond && (anothermap.size() == ft_anothermap.size() && anothermap.empty() == ft_anothermap.empty());

        cond = cond && compareMaps(ft_m.begin(), ft_m.end(), m.begin(), m.end()) && compareMaps(ft_anothermap.begin(), ft_anothermap.end(), anothermap.begin(), anothermap.end());
        EQUAL(cond);

	return 0;
}