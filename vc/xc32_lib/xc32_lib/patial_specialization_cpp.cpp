#include<type_traits>
#include<iostream>
template<unsigned int no1, unsigned int no2>
struct test_type:public std::false_type{
};

template<>
struct test_type<1, 1>:public std::true_type{};

template<>
struct test_type<1, 2> :public std::true_type{};

template<unsigned int no2>
struct test_type<0, no2> :public std::true_type{};

template<>
struct test_type<0, 1> :public std::false_type{};
template<>
struct test_type<0, 2> :public std::false_type{};

int main(){
	std::cout << "3:3 = " << test_type<3, 3>::value << std::endl;
	std::cout << "1:1 = " << test_type<1, 1>::value << std::endl;
	std::cout << "1:2 = " << test_type<1, 2>::value << std::endl;
	std::cout << "1:3 = " << test_type<1, 3>::value << std::endl;
	std::cout << "1:9 = " << test_type<1, 9>::value << std::endl;
	std::cout << "0:1 = " << test_type<0, 1>::value << std::endl;
	std::cout << "0:2 = " << test_type<0, 2>::value << std::endl;
	std::cout << "0:3 = " << test_type<0, 3>::value << std::endl;
	std::cout << "0:9 = " << test_type<0, 9>::value << std::endl;
	system("pause");

	return 0;
}
