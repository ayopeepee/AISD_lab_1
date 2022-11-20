#include "LongDouble.h"
#include <chrono>
#include <iostream>


int main(void) {
	LongDouble num1("123.32132");
	LongDouble num2("1000");
	auto slow_pow_start = std::chrono::steady_clock::now();
	LongDouble num3 = slow_pow(num1, num2);
	auto slow_pow_end = std::chrono::steady_clock::now();
	auto fast_pow_start = std::chrono::steady_clock::now();
	LongDouble num4 = pow(num1, num2);
	auto fast_pow_end = std::chrono::steady_clock::now();
	num3.print();
	std::cout << "slow_pow_time: " << std::chrono::duration_cast<std::chrono::milliseconds>(slow_pow_end - slow_pow_start).count() << '\n';
	num4.print();
	std::cout << "fast_pow_time: " << std::chrono::duration_cast<std::chrono::milliseconds>(fast_pow_end - fast_pow_start).count() << '\n';

	return 0;
}

