#include "LongDouble.h"
#include <chrono>
#include <iostream>
#include <fstream>


int main(void) {
	std::string string_number;
	std::string string_power;
	std::ifstream read_from("input.txt", std::ios::in);
	std::ofstream write_to("output.txt", std::ios::out);
	if (read_from && write_to) {
		while (!read_from.eof()) {
			read_from >> string_number;
			read_from >> string_power;
			LongDouble number(string_number);
			LongDouble power(string_power);
			auto time_start = std::chrono::steady_clock::now();
			LongDouble result = pow(number, power);
			auto time_end = std::chrono::steady_clock::now();
			auto total_time = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count();
			std::cout << "input vector size: " << GetNumber(number).capacity() << '\n';
			std::cout << "input string size: " << string_number.capacity() << '\n';
			std::cout << "input long number size: " << sizeof(number) + GetNumber(number).capacity() << '\n' << '\n';
			std::cout << "output vector size: " << GetNumber(result).capacity() << '\n';
			std::cout << "output string size: " << string_number.capacity() << '\n';
			std::cout << "output long number size: " << sizeof(result) + GetNumber(result).capacity() << '\n';
			std::cout << "----------------------------\n";
			for (int i = GetNumber(result).size() - 1; i >= GetDigitsAfterComma(result); i--)
				write_to << GetNumber(result)[i];
			write_to << '.';
			for (int i = GetDigitsAfterComma(result) - 1; i >= 0; i--)
				write_to << GetNumber(result)[i];
			write_to << '\n';
			write_to << "time (ms): " << total_time << '\n';
		}
	}
	read_from.close();
	write_to.close();

	return 0;
}

