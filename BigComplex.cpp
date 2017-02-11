#include "BigComplex.h"
#include "BigNum.h"

BigComplex::BigComplex(int real_num){
	real = new BigNum(real_num);
	imagine = new BigNum("0");
}

BigComplex::BigComplex(int real_num, int imagine_num) {
	real = new BigNum(real_num);
	imagine = new BigNum(imagine_num);
}

BigComplex::BigComplex(char * real_num){
	real = new BigNum(real_num);
	imagine = new BigNum("0");
}

BigComplex::BigComplex(char *real_num, char * imagine_num){
	real = new BigNum(real_num);
	imagine = new BigNum(imagine_num);
}

BigComplex::BigComplex(const BigComplex& big_complex){
	// sprawdzic czy na pewno kopiujacy jest uzywany
	real = big_complex.real;
	imagine = big_complex.imagine;
}

char* BigComplex::get_real_value() const{
	return real->value;
}

char* BigComplex::get_imagine_value() const{
	return imagine->value;
}

void BigComplex::set_real_value(int pos, char val){
	real->value[pos] = val;
}

void BigComplex::set_imagine_value(int pos, char val) {
	imagine->value[pos] = val;
}

BigComplex::~BigComplex(){
	delete real;
	delete imagine;
}

void BigComplex::input_real(std::istream& istr, BigComplex big_complex) {
	if (big_complex.real->size > 0) {
		std::cout << "Podaj czesc rzeczywista" << std::endl;
		for (int i = 0; i < big_complex.real->size; i++) {
			char val;
			istr >> val;
			while (!isdigit(val)) {
				std::cout << "Podaj prawidlowa cyfre" << std::endl;
				istr >> val;
			}
			big_complex.set_real_value(i, val);
		}
	}
}

void BigComplex::input_imagine(std::istream& istr, BigComplex big_complex) {
	if (big_complex.imagine->size > 0) {
		std::cout << "Podaj czesc urojona" << std::endl;
		for (int i = 0; i < big_complex.imagine->size; i++) {
			char val;
			istr >> val;
			while (!isdigit(val)) {
				std::cout << "Podaj prawidlowa cyfre" << std::endl;
				istr >> val;
			}
			big_complex.set_imagine_value(i, val);
		}
	}
}

void BigComplex::output_real(std::ostream& str, const BigComplex big_complex) const{
	if (big_complex.real->size > 0) {
		std::cout << "REAL PART: ";
		if (big_complex.is_real_negative()) {
			str << "-";
		}
		for (int i = 0; i < big_complex.real->size; i++) {
			str << big_complex.get_real_value()[i];
		}
	}
	str << std::endl;
}

void BigComplex::output_imagine(std::ostream& str, const BigComplex big_complex) const{
	if (big_complex.imagine->size > 0) {
		std::cout << "IMAGINE PART: ";
		if (big_complex.is_imagine_negative()) {
			str << "-";
		}
		for (int i = 0; i < big_complex.imagine->size; i++) {
			str << big_complex.get_imagine_value()[i];
		}
	}
	str << std::endl;
}

std::ostream & operator<<(std::ostream & str, const BigComplex &complex){
	complex.output_real(str, complex);
	complex.output_imagine(str, complex);
	return str;
}

std::istream & operator >> (std::istream & istr, BigComplex big_complex){
	big_complex.input_real(istr, big_complex);
	big_complex.input_imagine(istr, big_complex);
	return istr;
}

BigComplex BigComplex::operator = (const BigComplex& complex) {
	if (*this != complex) {
		delete real;
		delete imagine;
		real = new BigNum(complex.get_real_value());
		imagine = new BigNum(complex.get_imagine_value());
	}
	return *this;
}

bool BigComplex::operator== (const BigComplex& complex) {
	if (*real != *(complex.real) && *imagine != *(complex.imagine)) {
		return false;
	}
	return true;
}

BigComplex BigComplex::operator + (const BigComplex& complex) {
	BigComplex result;
	*(result.real) = *real + *(complex.real);
	*(result.imagine) = *imagine + *(complex.imagine);
	return result;
}

BigComplex BigComplex::operator - (const BigComplex& complex) {
	BigComplex result;
	*(result.real) = *real - *(complex.real);
	*(result.imagine) = *imagine - *(complex.imagine);
	return result;
}

BigComplex BigComplex::operator * (const BigComplex& complex) {
	BigComplex result;
	*(result.real) = *real * *(complex.real);
	*(result.imagine) = *imagine * *(complex.imagine);
	return result;
}

BigComplex BigComplex::operator += (const BigComplex& complex) {
	BigComplex result = *this + complex;
	*this = result;
	return *this;
}

BigComplex BigComplex::operator -= (const BigComplex& complex) {
	BigComplex result = *this - complex;
	*this = result;
	return *this;
}

BigComplex BigComplex::operator *= (const BigComplex& complex) {
	BigComplex result = *this * complex;
	*this = result;
	return *this;
}

BigComplex BigComplex::operator /= (const BigComplex& complex) {
	BigComplex result = *this / complex;
	*this = result;
	return *this;
}

bool BigComplex::operator != (const BigComplex& complex) {
	return !(*this == complex);
}

bool BigComplex::operator >= (const BigComplex& complex) {
	if (!(*this == complex && *this > complex)) {
		return false;
	}
	return true;
}

bool BigComplex::operator > (const BigComplex& complex) {
	// https://pl.wikipedia.org/wiki/Liczby_zespolone
	/*Choæ mo¿na sztucznie wprowadziæ jakiœ porz¹dek liczb zespolonych(np.porz¹dek leksykograficzny), 
	to jednak taka relacja nie zosta³a okreœlona i szerzej przyjêta.
	Nie da siê bowiem sformu³owaæ jej w taki sposób, aby w zbiorze liczb zespolonych spe³nia³a 
	aksjomaty cia³a uporz¹dkowanego, jak w przypadku liczb rzeczywistych.
	Tak wiêc nie da siê okreœliæ, która z dwóch liczb jest wiêksza lub mniejsza.
	Mo¿na natomiast porównywaæ ich modu³y oraz argumenty(g³ówne), 
	gdy¿ zarówno modu³, jak i argument liczby zespolonej s¹ liczbami rzeczywistymi.*/
	if (*real > *(complex.real)) {
		return true;
	}
	if (*imagine > *(complex.imagine)) {
		return true;
	}
	return false;
}

bool BigComplex::operator < (const BigComplex& complex) {
	if (*real < *(complex.real)) {
		return true;
	}
	if (*imagine < *(complex.imagine)) {
		return true;
	}
	return false;
}

BigComplex BigComplex::operator / (const BigComplex& complex) {
	BigComplex result;
	*(result.real) = *real / *(complex.real);
	*(result.imagine) = *imagine / *(complex.imagine);
	return result;
}

BigComplex BigComplex::operator - () {
	BigComplex result(*this);
	result.real->sign *= NEGATIVE;
	result.imagine->sign *= NEGATIVE;
	return result;
}

bool BigComplex::is_real_negative() const{
	return real->is_negative();
}

bool BigComplex::is_imagine_negative() const{
	return imagine->is_negative();
}

BigNum BigComplex::get_real_part() const{
	return BigNum(*real);
}

char * BigComplex::get_value() {
	char * val = new char[real->size + 1];
	strcpy(val, real->value);
}
