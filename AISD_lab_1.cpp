#include <iostream>
#include <string>
#include <vector>
#include <chrono>

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

LongDouble::LongDouble()
{
	number.resize(1);
	number[0] = 0;
}

LongDouble::LongDouble(std::string str)
{
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '.' or str[i] == ',') {
			digits_before_comma = i;
			continue;
		}
		number.push_back(str[i] - '0');
	}
	std::reverse(number.begin(), number.end());
}


LongDouble::LongDouble(std::vector<int> number)
{
	this->number = number;
}

LongDouble LongDouble::operator()(const std::vector<int> number)
{
	this->number = number;
	return *this;
}

LongDouble LongDouble::operator=(const LongDouble& number)
{
	this->number = number.number;
	this->digits_after_comma = number.digits_after_comma;
	this->digits_before_comma = number.digits_before_comma;
	return *this;
}



void LongDouble::print_reverse() const
{
	for (auto digit : number)
		std::cout << digit;
	std::cout << '\n';
}

void LongDouble::print()
{
	for (int i = number.size() - 1; i >= digits_after_comma; i--)
		std::cout << number[i];
	std::cout << '.';
	for (int i = digits_after_comma - 1; i >= 0; i--)
		std::cout << number[i];
	std::cout << '\n';
}

void LongDouble::print_no_comma()
{
	for (int i = number.size() - 1; i >= 0; i--)
		std::cout << number[i];
	std::cout << '\n';
}

int GetRealLength(const LongDouble& number)
{
	int temp = 0;
	for (int i = number.number.size() - 1; i >= 0; i--) {
		temp += number.number[i] * std::pow(LongDouble::base, i);
	}
	return temp;
}


LongDouble operator+(const LongDouble& first_number, const LongDouble& second_number)
{
	std::vector<int> result;
	LongDouble temp;
	int carry = 0;
	temp.digits_before_comma = std::max(first_number.digits_before_comma, second_number.digits_before_comma);
	for (int i = 0; i < std::min(first_number.number.size(), second_number.number.size()); i++) {
		int current_sum = carry + first_number.number[i] + second_number.number[i];
		result.push_back(current_sum % LongDouble::base);
		carry = current_sum / LongDouble::base;
	}
	for (int i = std::min(first_number.number.size(), second_number.number.size()); i < std::max(first_number.number.size(), second_number.number.size()); i++) {
		if (first_number.number.size() > second_number.number.size()) {
			int current_sum = carry + first_number.number[i];
			result.push_back(current_sum % LongDouble::base);
			carry = current_sum / LongDouble::base;
		}
		else {
			int current_sum = carry + second_number.number[i];
			result.push_back(current_sum % LongDouble::base);
			carry = current_sum / LongDouble::base;
		}
	}
	if (carry) {
		result.push_back(carry);
		temp.digits_before_comma++;
	}

	return temp(result);
}

LongDouble operator-(const LongDouble& first_number, const LongDouble& second_number)
{
	std::vector<int> result;
	int carry = 0;
	for (int i = 0; i < second_number.number.size(); i++) {
		int cur_diff = first_number.number[i] - second_number.number[i] - carry;
		if (cur_diff < 0) {
			cur_diff += 10;
			carry = 1;
		}
		else
			carry = 0;
		result.push_back(cur_diff);
	}
	for (int i = second_number.number.size(); i < first_number.number.size(); i++) {
		if (first_number.number[i] - carry < 0) {
			result.push_back(first_number.number[i] + 10 - carry);
			carry = 1;
		}
		else {
			result.push_back(first_number.number[i] - carry);
			carry = 0;
		}

	}
	return LongDouble(result);
}

LongDouble operator*(const LongDouble& first_number, const LongDouble& second_number)
{
	LongDouble temp;
	temp.digits_before_comma = std::max(first_number.digits_before_comma, second_number.digits_before_comma);
	std::vector<int> result(first_number.number.size() * second_number.number.size(), 0);
	for (int i = 0; i < first_number.number.size(); i++) {
		int carry = 0;
		for (int j = 0; j < second_number.number.size(); j++) {
			int current = result[i + j] + first_number.number[i] * second_number.number[j] + carry;
			carry = current / LongDouble::base;
			result[i + j] = current % LongDouble::base;
		}
		int current = second_number.number.size();
		while (carry) {
			result[i + current] = carry % LongDouble::base;
			current++;
			carry /= LongDouble::base;
		}
	}

	while (result.size() > 1 && !result.back())
		result.pop_back();
	return temp(result);
}

LongDouble operator/(const LongDouble& first_number, const LongDouble& second_number)
{
	std::vector<int> result(first_number.number.size() - second_number.number.size() + 1, 0);
	LongDouble temp(result);
	temp.digits_before_comma = first_number.digits_before_comma - second_number.digits_before_comma;
	for (int i = result.size() - 1; i >= 0; i--) {
		while (second_number * temp <= first_number)
			temp.number[i]++;
		temp.number[i]--;
	}
	while (temp.number.size() > 1 && !temp.number.back())
		temp.number.pop_back();
	return temp;
}

bool operator<=(const LongDouble& first_number, const LongDouble& second_number)
{
	if (first_number.number.size() < second_number.number.size())
		return true;
	else if (first_number.number.size() > second_number.number.size())
		return false;
	else {
		for (int i = first_number.number.size() - 1; i >= 0; i--) {
			if (first_number.number[i] > second_number.number[i])
				return false;
			if (first_number.number[i] < second_number.number[i])
				return true;
		}

	}
	return true;
}

bool operator<(const LongDouble& first_number, const LongDouble& second_number)
{
	if (first_number.number.size() < second_number.number.size())
		return true;
	else
		return false;
}



bool even(const LongDouble& number)
{
	if (number.number[0] % 2 == 0)
		return true;
	return false;
}

LongDouble pow(LongDouble& first_number, LongDouble& second_number)
{
	LongDouble result("1");
	int temp_digits_after_comma = GetRealLength(second_number);
	while (second_number.number.back()) {
		if (even(second_number)) {
			second_number = second_number / LongDouble("2");
			first_number = first_number * first_number;
		}
		else {
			second_number = second_number - LongDouble("1");
			result = result * first_number;
		}
	}
	result.digits_after_comma = temp_digits_after_comma;
	return result;
}

LongDouble slow_pow(LongDouble& first_number, LongDouble& second_number)
{
	LongDouble result("1");
	for (LongDouble i = LongDouble("1"); i <= second_number; i = i + LongDouble("1")) {
		result = result * first_number;
	}
	result.digits_after_comma = GetRealLength(second_number);
	return result;
}


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

