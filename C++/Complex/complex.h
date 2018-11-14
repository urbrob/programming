#ifndef SET_PLUS_H_
#define SET_PLUS_H_
#include <stdbool.h>
#include <iostream>


class Complex {
private:
	double real;
	double imaginary;
	friend Complex operator+(int, Complex&);
    friend Complex operator+(Complex&, int);
    friend Complex operator-(int, Complex&);
    friend Complex operator-(Complex&, int);
    friend Complex operator*(int, Complex&);
    friend Complex operator*(Complex&, int);
    friend Complex operator/(int, Complex&);
    friend Complex operator/(Complex&, int);
    friend bool operator==(int, Complex&);
    friend bool operator==(Complex&, int);

public:
	Complex(double real = 0, double imaginary = 0);
	Complex operator+(Complex& );
	Complex operator-(Complex&);
	Complex operator*(Complex&);
	Complex operator/(Complex&);
	Complex& operator+=(Complex&);
	Complex& operator-=(Complex&);
	Complex& operator*=(Complex&);
	Complex& operator/=(Complex&);
	bool operator==(Complex&);
	friend std::ostream &operator<<(std::ostream &out,Complex &comp);
	void set_real(double real);
	double get_real();
	void set_imaginary(double imaginary);
	double get_imaginary();
	void show();
	double get_amplitude();
	double get_phase();
};

#endif
