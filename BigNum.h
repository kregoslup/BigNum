#pragma once
#include <iostream>

class BigNum {
private:
	const int BASE = 10;
	const char CHAR_TO_INT = '0';
	const int NEGATIVE = -1;
	const int POSITIVE = 1;
	const int SIGN_SIZE = 1;
	char *value;
	int size;
	int sign;
	int get_int_size(int);
	void extend_value(void);
	void initialize_value(int);
	void set_sign(int);
	void set_sign(char*);
	bool is_negative(void) const;
	bool is_positive(void) const;
	void num_to_char_array(int);
	void normalize_value_length(int);
	void copy_array_wihout_sign(char*, int);
	void validate_char_input(char*);
	void add_with_carry(const BigNum&);
	void carry_multiplication(const BigNum&, const BigNum&);
	void carry_subtraction(const BigNum&, const BigNum&);
	bool is_subtract(const BigNum&);
	void equals_operation(const BigNum&);
	BigNum addition(const BigNum&);
public:
	BigNum(int=0);
	BigNum(char *value);
	BigNum(const BigNum&);
	~BigNum();
	BigNum operator!();
	friend std::ostream& operator<<(std::ostream&, const BigNum&);
	friend std::istream& operator>> (std::istream&, BigNum);
	char operator[](const int);
	//static void operator delete(void*);
	BigNum operator = (const BigNum&);
	BigNum operator = (char*);
	BigNum operator = (int);
	BigNum operator + (const BigNum&);
	BigNum operator + (int);
	BigNum operator - (const BigNum&);
	BigNum operator - (void);
	BigNum operator * (const BigNum&);
	BigNum operator / (const BigNum&);
	BigNum operator += (const BigNum&);
	BigNum operator -= (const BigNum&);
	BigNum operator /= (const BigNum&);
	BigNum operator *= (const BigNum&);
	bool operator == (const BigNum&);
	bool operator == (char*);
	bool operator != (const BigNum&);
	bool operator >= (const BigNum&);
	bool operator > (const BigNum&) const;
	bool operator < (const BigNum&) const;
};