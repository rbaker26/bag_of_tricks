#include <type_traits>
#include <iostream>

#include <chrono>

//**************************************************************

template<typename... T>
auto veridac_sum(T... s)
{
	typename std::common_type<T...>::type result{};
	(void)std::initializer_list<int>{ (result += s, 0)... };
	return result;
}

//**************************************************************

template<typename... T>
auto fold_sum(T... s) 
{
	return (... + s);
}

//**************************************************************

template<typename... T>
auto avg(T... a)
{
	int count = 0;
	count++;
	return((... + a) / count);
}

//**************************************************************

int main()
{
	auto start_vs = std::chrono::high_resolution_clock::now();
	veridac_sum(1,2,3,5.5,6.6,.001);
	auto end_vs = std::chrono::high_resolution_clock::now();

	auto start_fs = std::chrono::high_resolution_clock::now();
	fold_sum(1,2,3,5.5,6.6,.001);
	auto end_fs = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> time_vs = end_vs - start_vs;
	std::chrono::duration<double> time_fs = end_fs - start_fs;
		
	std::cout << "veridac_sum(1,2,3,5.5,6.6,.001):  " 
			  << veridac_sum(1,2,3,5.5,6.6,.001) << "\t"
		      << time_vs.count() << "s\n";

	std::cout << "fold_sum(1,2,3,5.5,6.6,.001):     " 
			  << fold_sum(1,2,3,5.5,6.6,.001) << "\t"
			  << time_fs.count() << "s\n";
	
	return 0;
}