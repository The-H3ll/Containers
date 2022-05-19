
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

void testElementAccess()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator [] "
              << "] --------------------]\t\t\033[0m";
    {
        /*{
            time_t start, end, diff;
            // ------------------ std::maps ---------------------
            std::map<int, std::string> m1;
            ft::map<int, std::string> ft_m1;

            for (size_t i = 0; i < 1e6; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string2"));
            }
            start = get_time();
            m1[1e6] = "string";
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            // -----------------------------------------------------
            // ------------------ ft::maps ---------------------
            ualarm(diff * 1e3, 0);
            ft_m1[1e6] = "string";
            ualarm(0, 0);
            // ----------------------------------------------------
            // ------------------ std::maps ---------------------
            start = get_time();
            m1[1e6 - 100] = "string";
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            // -----------------------------------------------------
            // ------------------ ft::maps ---------------------
            ualarm(diff * 1e3, 0);
            ft_m1[1e6 - 100] = "string";
            ualarm(0, 0);
            // ----------------------------------------------------
            // ------------------ std::maps ---------------------
            start = get_time();
            m1[1e6 - 100] = m1[1e5];
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            // -----------------------------------------------------
            // ------------------ ft::maps ---------------------
            ualarm(diff * 1e3, 0);
            ft_m1[1e6 - 100] = ft_m1[1e5];
            ualarm(0, 0);
            // ----------------------------------------------------
        }*/
        std::map<char, std::string> m;
        ft::map<char, std::string> ft_m;

        m['a'] = "an element";
        m['b'] = "another element";
        m['c'] = m['b'];
        m['a'] = "test";

        ft_m['a'] = "an element";
        ft_m['b'] = "another element";
        ft_m['c'] = ft_m['b'];
        ft_m['a'] = "test";

        EQUAL(m['a'] == ft_m['a'] && m['b'] == ft_m['b'] && m['c'] == ft_m['c'] && m.size() == ft_m.size());
    }
}
int     main()
{

 	//  iterator_tests();
	// testElementAccess();


        bool cond(true);
        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::map<int, std::string> ft_m1;
            for (size_t i = 0; i < 1200/*1e6*/; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();

            for (size_t i = 1e1; i < 1200/*1e5*/; i += 10)
                m1.find(i);

            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::maps ---------------------*/
            ualarm(diff * 1e3, 0);
            for (size_t i = 1e1; i < 1e5; i += 10)
                ft_m1.find(i);
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }

        std::vector<int> vec;
        std::vector<int> ft_vec;
        std::random_device randDev;
        std::mt19937 generator(randDev());
        std::uniform_int_distribution<int> distr(0, 1e8);

        std::map<int, std::string> m1;
        ft::map<int, std::string> ft_m1;
        std::map<int, std::string>::iterator it;
        ft::map<int, std::string>::iterator ft_it;

        for (size_t i = 0; i < 1200/*1e6*/; i++)
        {
            m1.insert(std::make_pair(i, "string2"));
            ft_m1.insert(ft::make_pair(i, "string2"));
        }

        for (size_t i = 0; i < 1200/*1e6*/; i++)
        {
            int n = distr(generator);
            it = m1.find(n);
            ft_it = ft_m1.find(n);
            if (it == m1.end() && ft_it == ft_m1.end())
                continue;
            if (it == m1.end() && ft_it != ft_m1.end())
            {
                cond = false;
                break;
            }
            else
            {
                vec.push_back(it->first);
                ft_vec.push_back(ft_it->first);
            }
        }

        std::map<char, int> m;
        ft::map<char, int> ft_m;
        std::map<char, int>::iterator it2;
        ft::map<char, int>::iterator ft_it2;

        m['a'] = 50;
        m['b'] = 100;
        m['c'] = 150;
        m['d'] = 200;

        ft_m['a'] = 50;
        ft_m['b'] = 100;
        ft_m['c'] = 150;
        ft_m['d'] = 200;

        it2 = m.find('b');
        ft_it2 = ft_m.find('b');

        cond = cond && it2->first == ft_it2->first && it2->second == ft_it2->second;

        if (it2 != m.end())
            m.erase(it2);
        if (ft_it2 != ft_m.end())
            ft_m.erase(ft_it2);

        cond = cond && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        EQUAL(cond && vec == ft_vec);

	return 0;
}