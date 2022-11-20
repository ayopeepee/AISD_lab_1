#include "LongDouble.h"
#include <chrono>
#include <iostream>
#include <fstream>


int main(void) {
	std::string string_number;
	std::string string_power;
	std::ifstream read_from("input.txt", std::ios::in);
	if (read_from) {
		while (!read_from.eof()) {
			read_from >> string_number;
			read_from >> string_power;
			LongDouble number(string_number);
			LongDouble power(string_power);
			auto time_start = std::chrono::steady_clock::now();
			LongDouble result = pow(number, power);
			auto time_end = std::chrono::steady_clock::now();
			auto total_time = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count();
			result.print();
			std::cout << "time (ms): " << total_time << '\n';
		}
	}
	read_from.close();

	return 0;
}

