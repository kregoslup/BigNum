#pragma once
#include <iostream>
#include "BigNum.h"

class BigComplex {
private:
	const int BASE = 10;
	const char CHAR_TO_INT = '0';
	const int NEGATIVE = -1;
	const int POSITIVE = 1;
	const int SIGN_SIZE = 1;
	BigNum *real;
	BigNum *imagine;
	void input_real(std::istream&, BigComplex);
	void input_imagine(std::istream&, BigComplex);
	void output_real(std::ostream&, const BigComplex) const;
	void output_imagine(std::ostream&, const BigComplex) const;
	bool is_real_negative(void) const;
	bool is_imagine_negative(void) const;
public:
	BigComplex(int = 0);
	BigComplex(int, int);
	BigComplex(char*);
	BigComplex(char*, char*);
	BigComplex(const BigComplex&);
	BigNum get_real_part(void) const;
	char* get_real_value(void) const;
	char* get_imagine_value(void) const;
	void set_real_value(int, char);
	void set_imagine_value(int, char);
	~BigComplex();
	friend std::ostream& operator<<(std::ostream&, const BigComplex&);
	friend std::istream& operator>> (std::istream&, BigComplex);
	BigComplex operator = (const BigComplex&);
	BigComplex operator + (const BigComplex&);
	BigComplex operator - (const BigComplex&);
	BigComplex operator - (void);
	BigComplex operator * (const BigComplex&);
	BigComplex operator / (const BigComplex&);
	BigComplex operator += (const BigComplex&);
	BigComplex operator -= (const BigComplex&);
	BigComplex operator /= (const BigComplex&);
	BigComplex operator *= (const BigComplex&);
	char * get_value();
	bool operator == (const BigComplex&);
	bool operator != (const BigComplex&);
	bool operator >= (const BigComplex&);
	bool operator > (const BigComplex&);
	bool operator < (const BigComplex&);
};