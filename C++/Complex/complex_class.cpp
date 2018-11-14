#include "complex.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;

void error(char *err);

void error(const char* err) {
	printf("%s", err);
	abort();
}

Complex Complex::operator+(Complex& comp){
	Complex new_comp;
	new_comp.set_real(this->real + comp.get_real());
	new_comp.set_imaginary(this->imaginary + comp.get_imaginary());
	return new_comp;
}

Complex Complex::operator-(Complex& comp) {
	Complex new_comp;
	new_comp.set_real(this->real - comp.get_real());
	new_comp.set_imaginary(this->imaginary - comp.get_imaginary());
	return new_comp;
}

Complex Complex::operator*(Complex& comp) {
	Complex new_comp;
	new_comp.set_real(this->real * comp.get_real() - this->imaginary * comp.get_imaginary());
	new_comp.set_imaginary(this->real * comp.get_imaginary() + this->imaginary * comp.get_real());
	return new_comp;
}

Complex Complex::operator/(Complex& comp) {
	Complex new_comp;
	double divider = comp.get_real() * comp.get_real() + comp.get_imaginary() *comp.get_imaginary();
	new_comp.set_real((this->real * comp.get_real() - this->imaginary * comp.get_imaginary()) / divider);
	new_comp.set_imaginary((this->real * comp.get_imaginary() + this->imaginary * comp.get_real()) / divider);
	return new_comp;
}

Complex& Complex::operator+=(Complex& comp){
	this->real += comp.get_real();
	this->imaginary += comp.get_imaginary();
	return *this;
}

Complex& Complex::operator-=(Complex& comp) {
	this->real -= comp.get_real();
	this->imaginary -= comp.get_imaginary();
	return *this;
}

Complex& Complex::operator*=(Complex& comp) {
	this->real = this->real * comp.get_real() - this->imaginary * comp.get_imaginary();
	this->imaginary = this->real * comp.get_imaginary() + this->imaginary * comp.get_real();
	return *this;
}

Complex& Complex::operator/=(Complex& comp) {
	double divider = comp.get_real() * comp.get_real() + comp.get_imaginary() *comp.get_imaginary();
	this->real = (this->real * comp.get_real() - this->imaginary * comp.get_imaginary()) / divider;
	this->imaginary = (this->real * comp.get_imaginary() + this->imaginary * comp.get_real()) / divider;
	return *this;
}

bool Complex::operator==(Complex& comp) {
	if (this->real == comp.get_real() && this->imaginary == comp.get_imaginary()) {
		return true;
	}
	return false;
}

std::ostream &operator<<(std::ostream &out, Complex &comp) {
	if (comp.get_imaginary() < 0) {
		return out << comp.get_real() << " - i" << -comp.get_imaginary() << '\n';
	}
	return out << comp.get_real() << " + i" << comp.get_imaginary() << '\n';
}

Complex::Complex(double real, double imaginary) {
	this->real = real;
	this->imaginary = imaginary;
}

Complex operator+(int i_num, Complex &num) {
    Complex temp;
    temp.real = num.get_real() + i_num;
    temp.imaginary = num.get_imaginary();
    return temp;
}

Complex operator+(Complex& num, int i_num) {
    Complex temp;
    temp.real = num.get_real() + i_num;
    temp.imaginary = num.get_imaginary();
    return temp;
}

Complex operator-(int i_num, Complex &num) {
    Complex temp;
    temp.real = num.get_real() - i_num;
    temp.imaginary = num.get_imaginary();
    return temp;
}

Complex operator-(Complex &num, int i_num) {
    Complex temp;
    temp.real = i_num - num.get_real();
    temp.imaginary = num.get_imaginary() * -1;
    return temp;
}

Complex operator*(int i_num, Complex &num) {
    Complex temp;
    temp.real = num.get_real() * i_num;
    temp.imaginary = num.get_imaginary() * i_num;
    return temp;
}

Complex operator*(Complex &num, int i_num) {
    Complex temp;
    temp.real = num.get_real() * i_num;
    temp.imaginary = num.get_imaginary() * i_num;
    return temp;
}

Complex operator/(int i_num, Complex &num) {
  Complex temp;
  double divider = num.get_real() * num.get_real() + num.get_imaginary() * num.get_imaginary();
  temp.real = i_num * num.get_real() / divider;
  temp.imaginary = -i_num * num.get_imaginary() / divider;
  return temp;
}

Complex operator/(Complex &num, int i_num) {
    Complex temp;
    temp.real = num.get_real() / i_num;
    temp.imaginary = num.get_imaginary() / i_num;
    return temp;
}

bool operator==(Complex& num, int i_num) {
    if(num.real == i_num && num.imaginary == 0) {
        return true;
    }
    else
        return false;
}

bool operator==(int i_num, Complex& num) {
    if(num.real == i_num && num.imaginary == 0) {
        return true;
    }
    else
        return false;
}

void Complex::set_real(double real) {
	this->real = real;
}

double Complex::get_real() {
	return real;
}

void Complex::set_imaginary(double imaginary) {
	this->imaginary = imaginary;
}

double Complex::get_imaginary() {
	return imaginary;
}

void Complex::show(){
	cout << real << " i" << imaginary << '\n';
}

double Complex::get_amplitude(){
	if (real < 0) {
        return atan(real/imaginary);
    }
    else if (real > 0) {
        return atan(real / imaginary) + M_PI;
    }
    else if (real == 0 && imaginary < 0) {
        return -(M_PI / 2);
    }
    else if(real == 0 && imaginary > 0) {
        return M_PI / 2;
    }
    else {
        return 0;
    }
}

double Complex::get_phase(){
	return sqrt((real * real) + (imaginary * imaginary));
}
