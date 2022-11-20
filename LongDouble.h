#pragma once
#include <vector>
#include <string>

class LongDouble {
public:
	LongDouble();
	LongDouble(std::string str);
	LongDouble(std::vector<int> number);
	LongDouble operator () (const std::vector<int> number);
	LongDouble operator = (const LongDouble& number);
	friend LongDouble operator + (const LongDouble& first_number, const LongDouble& second_number);
	friend LongDouble operator - (const LongDouble& first_number, const LongDouble& second_number);
	friend LongDouble operator * (const LongDouble& first_number, const LongDouble& second_number);
	friend LongDouble operator / (const LongDouble& first_number, const LongDouble& second_number);
	friend bool operator <= (const LongDouble& first_number, const LongDouble& second_number);
	friend bool operator < (const LongDouble& first_number, const LongDouble& second_number);
	friend bool even(const LongDouble& number);
	friend LongDouble pow(LongDouble& first_number, LongDouble& second_number);
	friend LongDouble slow_pow(LongDouble& first_number, LongDouble& second_number);
	void print_reverse() const;
	void print();
	void print_no_comma();
	friend int GetRealLength(const LongDouble& number);
private:
	std::vector <int> number;
	int digits_before_comma = 0;
	int digits_after_comma = 0;
	static const int base = 10;

};