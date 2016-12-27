#include "BigNum.h"
#include <iostream>
#include <cstring>
#include <cctype>


BigNum::BigNum(const BigNum& big_num) {
	size = big_num.size;
	sign = big_num.sign;
	value = new char[size+1];
	strcpy(value, big_num.value);
}

BigNum::BigNum(int num) {
	set_sign(num);
	num = abs(num);
	size = get_int_size(num);
	value = new char[size + 1];
	num_to_char_array(num);
}

BigNum::BigNum(char *num_val) {
	validate_char_input(num_val);
	set_sign(num_val);
	if (is_negative()) {
		size = strlen(num_val) - SIGN_SIZE;
	}
	else {
		size = strlen(num_val);
	}
	copy_array_wihout_sign(num_val, size);
}

BigNum::~BigNum() {
	delete[] value;
	value = 0;
	size = 0;
}

std::istream& operator>>(std::istream & istr, BigNum big_num){
	if (strlen(big_num.value) > 0 && big_num.size > 0) {
		for (int i = 0; i < big_num.size; i++) {
			char val;
			istr >> val;
			while (!isdigit(val)) {
				std::cout << "Podaj prawidlowa cyfre" << std::endl;
				istr >> val;
			}
			big_num.value[i] = val;
		}
	}
	return istr;
}

BigNum BigNum::operator = (const BigNum& big_num) {
	if (*this != big_num) {
		delete[] value;
		size = big_num.size;
		sign = big_num.sign;
		value = new char[size + 1];
		strcpy(value, big_num.value);
	}
	return *this;
}

BigNum BigNum::operator = (char* arr) {
	if (strcmp(value, arr) != 0) {
		BigNum *big_num = new BigNum(arr);
		return *big_num;
	}
	return *this;
}

BigNum BigNum::operator = (int num) {
	BigNum *big_num = new BigNum(num);
	if (*this != *big_num) {
		return *big_num;
	}
	delete big_num;
	return *this;
}

bool BigNum::is_subtract(const BigNum& big_num) {
	// sprawdza przypadki jak np.: "20 + (-20)", ktore tak naprawde sa odejmowaniem
	if (big_num.is_negative() && is_positive()) {
		return true;
	}
	return false;
}

BigNum BigNum::operator+ (const BigNum& big_num) {
	if (is_subtract(big_num)) {
		return *this - big_num;
	}
	return addition(big_num);
}

BigNum BigNum::addition(const BigNum& big_num) {
	BigNum longer = ((*this).size > big_num.size) ? *this : big_num;
	BigNum shorter = (*this == longer) ? big_num : *this;
	if (longer.size > shorter.size) {
		shorter.normalize_value_length(longer.size);
	}
	longer.add_with_carry(shorter);
	longer.size = strlen(longer.value);
	longer.sign = POSITIVE;
	return longer;
}

void BigNum::normalize_value_length(int new_size) {
		char *temp = new char[size + 1];
		strcpy(temp, value);
		delete[] value;
		int prepend_size = new_size - size;
		value = new char[new_size + 1];
		std::fill_n(value, new_size + 1, '0');
		value[new_size] = '\0';
		value[prepend_size] = '\0';
		strcat(value, temp);
		size = new_size;
		delete[] temp;
}

//void BigNum::operator delete(void* ptr) {
//	return delete[] static_cast<BigNum*>(ptr);
//}

//void * BigNum::operator new(size_t size)
//{
//	BigNum big_num(size);
//	return *big_num;
//}

BigNum BigNum::operator+ (int num) {
	BigNum big_num(num);
	if (is_subtract(big_num)) {
		return *this - big_num;
	}
	return *this + big_num;
}

BigNum BigNum::operator - (const BigNum& big_num) {
	// sprawdza przypadek 20 - (-20)
	if (big_num.is_negative()) {
		BigNum temp(big_num);
		temp.sign = POSITIVE;
		return *this + temp;
	}
	// sprawdza przypadek -20 - 20 == (-1) * 20 + 20
	if (big_num.is_negative() && is_negative()) {
		BigNum temp(big_num);
		temp.sign = NEGATIVE;
		return *this + temp;
	}
	BigNum *result = new BigNum();
	(*result).size = size > big_num.size ? size : big_num.size;
	result->initialize_value(result->size);
	if (*this > big_num) {
		result->carry_subtraction(*this, big_num);
	}
	else {
		result->carry_subtraction(big_num, *this);
		result->sign = NEGATIVE;
	}
	return *result;
}

BigNum BigNum::operator-(void){
	BigNum *result = new BigNum(*this);
	result->sign = result->sign * -1;
	return *result;
}

BigNum BigNum::operator* (const BigNum& big_num) {
	BigNum longer = ((*this).size > big_num.size) ? *this : big_num;
	BigNum shorter = (*this == longer) ? big_num : *this;
	BigNum result;
	result.initialize_value(longer.size);
	result.carry_multiplication(longer, shorter);
	result.size = strlen(result.value);
	result.set_sign(longer.sign*shorter.sign);
	return result;
}

BigNum BigNum::operator/(const BigNum & big_num){
	//// tu wystraczy zrobic count = 0
	//if (big_num < *this) {
	//	return BigNum();
	//}
	BigNum temp(*this);
	BigNum *count = new BigNum();
	while (big_num > temp) {
		*count += 1;
		temp += temp;
	}
	return *count;
	//return count
}

std::ostream& operator<<(std::ostream& str, const BigNum& big_num){
	if (strlen(big_num.value) > 0 && big_num.size > 0) {
		if (big_num.is_negative()) {
			str << BigNum::MINUS_CHAR;
		}
		for (int i = 0; i < big_num.size; i++) {
			str << big_num.value[i];
		}
	}
	str << std::endl;
	return str;
}

char BigNum::operator[](const int position) {
	if (position > 0 && position <= size && strlen(value) > 0) {
		return value[position];
	}
	return '0';
}

BigNum BigNum::operator/=(const BigNum & big_num){
	BigNum result = *this / big_num;
	*this = result;
	return *this;
}

BigNum BigNum::operator*= (const BigNum& big_num) {
	BigNum result = *this * big_num;
	*this = result;
	return *this;
}

BigNum BigNum::operator+= (const BigNum& big_num) {
	BigNum result = *this + big_num;
	*this = result;
	return *this;
}

BigNum BigNum::operator-= (const BigNum& big_num) {
	BigNum result = *this - big_num;
	*this = result;
	return *this;
}

bool BigNum::operator == (const BigNum& compare) {
	if (this == &compare) {
		return true;
	}
	if (size != compare.size) {
		return false;
	}
	if (sign != compare.sign) {
		return false;
	}
	if (strcmp(value, compare.value) != 0) {
		return false;
	}
	return true;
}

bool BigNum::operator == (char* arr) {
	BigNum big_num(arr);
	return *this == big_num;
}

bool BigNum::operator != (const BigNum& big_num){
	return !(*this == big_num);
}

bool BigNum::operator >= (const BigNum& comp) {
	return !(*this < comp);
}

bool BigNum::operator > (const BigNum& comp) const{
	if (size > comp.size) {
		return true;
	}
	if (sign > comp.sign) {
		return true;
	}
	if (strcmp(value, comp.value) > 0) {
		return true;
	}
	return false;
}

bool BigNum::operator < (const BigNum& comp) const {
	if (size <= comp.size) {
		return true;
	}
	if (sign < comp.sign) {
		return true;
	}
	if (strcmp(value, comp.value) < 0) {
		return true;
	}
	return false;
}

int BigNum::get_int_size(int num) {
	// (number == 0) ? 1 : (floor(log10(number)) + 1)
	int size = 0;
	do {
		size++;
		num /= BASE;
	} while (num);
	return size;
}

void BigNum::set_sign(int num) {
	if (num >= 0) {
		sign = POSITIVE;
		return;
	}
	sign = NEGATIVE;
}

void BigNum::set_sign(char *num) {
	if (num[0] == MINUS_CHAR) {
		sign = NEGATIVE;
	}
	else {
		sign = POSITIVE;
	}
}

void BigNum::extend_value() {
	normalize_value_length(size + 1);
}

void BigNum::initialize_value(int arr_len) {
	size = arr_len;
	value = new char[size + 1];
	std::fill_n(value, size + 1, '0');
	value[size] = '\0';
}

bool BigNum::is_negative() const{
	return sign == NEGATIVE;
}

bool BigNum::is_positive() const{
	return sign == POSITIVE;
}

void BigNum::num_to_char_array(int num){
	int i = size-1;
	do {
		value[i] = (num % BASE) + CHAR_TO_INT;
		num = num / BASE;
		i--;
	} while (num > 0);
	value[size] = '\0';
}

void BigNum::copy_array_wihout_sign(char* arr, int size) {
	value = new char[size + 1];
	if (sign == NEGATIVE) {
		strcpy(value, arr + SIGN_SIZE);
	}
	else {
		strcpy(value, arr);
	}
}

void BigNum::validate_char_input(char * input){
	for (int i = 0; i < strlen(input); i++) {
		if (!isdigit(input[i]) && input[i] != '-') {
			std::cout << "W podanej 'liczbie' znaleziono znaki nie bedace cyframi, program nie bedzie dzialal poprawnie" << std::endl;
		}
	}
}

void BigNum::add_with_carry(const BigNum& shorter) {
	int carry = 0;
	int addition_size = shorter.size;
	for (int i = addition_size - 1; i >= 0; i--) {
		int sum = ((value[i] - CHAR_TO_INT) + (shorter.value[i] - CHAR_TO_INT));
		if (carry != 0) {
			sum += carry;
		}
		carry = 0;
		value[i] = ((sum % BASE) + CHAR_TO_INT);
		carry = sum / BASE;
		if (i == 0 && carry != 0) {
			extend_value();
			value[0] = carry + CHAR_TO_INT;
		}
	}
	addition_size = size;
}

int BigNum::my_atoi(char c) { return c - CHAR_TO_INT; };
int BigNum::my_itoa(int c) { return c + CHAR_TO_INT; };

void BigNum::carry_multiplication(const BigNum& longer, const BigNum& shorter) {
	int carry = 0;
	int row = 0;
	for (int i = shorter.size - 1; i >= 0; i--) {
		if (row > 0) {
			extend_value();
		}
		for (int y = longer.size - 1; y >= 0; y--) {
			int sum = my_atoi(longer.value[y]) * my_atoi(shorter.value[i]);
			if (carry != 0) {
				sum += carry;
			}
			carry = 0;
			int temp = my_atoi(value[y]) + sum;
			int val = temp % BASE;
			value[y] = my_itoa(val);
			carry = sum / BASE;
		}
		row += 1;
	}
	if (carry != 0) {
		extend_value();
		value[0] = my_itoa(carry);
	}
}

void BigNum::carry_subtraction(const BigNum& minuend, const BigNum& subtrahend){
	int carry = 0;
	int subtrahend_position = subtrahend.size;
	int subtrahend_offset = 0;
	for (int i = minuend.size -1; i >= 0; i--) {
		int minuend_val = minuend.value[i] - CHAR_TO_INT;
		int subtrahend_val = subtrahend_position - subtrahend_offset > subtrahend.size ? subtrahend.value[subtrahend_position - subtrahend_offset] - CHAR_TO_INT : 0;
		int diff = minuend_val - subtrahend_val - carry;
		if (diff < 0) {
			diff += BASE;
			carry = 1;
		}
		else {
			carry = 0;
		}
		value[i] = diff + CHAR_TO_INT;
		subtrahend_offset++;
	}
}

char * BigNum::get_value() {
	char * val = new char[size + 1];
	strcpy(val, value);
}

//BigNum BigNum::operator!() {
//	/*BigNum *temp(this);
//	BigNum compare("1");
//	BigNum result;
//	result.initialize_value(size);
//	while (*temp > compare) {
//		result 
//	}*/
//}
