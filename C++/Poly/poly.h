#ifndef POLY_H_
#define POLY_H_
#include <iostream>
#include <map>

class Poly {
private:
	std::map<int,double> coefficients;
	std::string erase_one(std::string text);
public:
	Poly operator+(Poly const& poly) const;
	double &operator [](const int power);
	Poly(double new_number=0);
	friend std::ostream &operator<<(std::ostream &out,Poly pol);
	Poly operator-(Poly const& poly) const;
	Poly operator*(Poly const& poly) const;
	double operator()(double value_x) const;
	Poly operator-() const;
};
#endif
