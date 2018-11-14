#include "poly.h"
#include <map>
#include <string>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>


using namespace std;
double &Poly::operator [](const int power){
	return coefficients[power];
}

Poly::Poly(double new_number) {
	coefficients[0] = new_number;
}

string erase_one(string text){
	int i = 0;
	string new_text = "";
	for(;text[i] != '\0'; i++) {
		if(text[i] != '1' || text[i + 1] != 'x')
		new_text += text[i];
	}
	return new_text;
}

Poly Poly::operator+(Poly const& poly) const{
	Poly new_poly;
	for(map<int, double>::const_iterator it = coefficients.begin(); it != coefficients.end(); ++it){
		new_poly.coefficients[(*it).first] = (*it).second;
	}
	for(map<int, double>::const_iterator it = poly.coefficients.begin();it != poly.coefficients.end(); ++it){
		new_poly.coefficients[(*it).first] += (*it).second;
		if (new_poly.coefficients.at((*it).first) == 0.0) new_poly.coefficients.erase((*it).first);
	}
	
	return new_poly;
}

Poly Poly::operator-(Poly const& poly) const{
	Poly new_poly;
	for(map<int, double>::const_iterator it = coefficients.begin();it != coefficients.end(); ++it){
		new_poly.coefficients[(*it).first] = (*it).second;
	}
	for(map<int, double>::const_iterator it = poly.coefficients.begin();it != poly.coefficients.end(); ++it){
		new_poly.coefficients[(*it).first] -= (*it).second;
		if (new_poly.coefficients.at((*it).first) == 0) new_poly.coefficients.erase((*it).first);
	}
	return new_poly;
}

Poly Poly::operator*(Poly const& poly) const{
	Poly new_poly;
	for(map<int, double>::const_iterator it = coefficients.begin();it != coefficients.end(); ++it){
			for(map<int, double>::const_iterator it2 = poly.coefficients.begin();it2 != poly.coefficients.end(); ++it2){
				int index = (*it).first + (*it2).first;
				new_poly.coefficients[index] += (*it).second * (*it2).second;
				if (new_poly.coefficients.at(index) == 0) new_poly.coefficients.erase(index);
		}
	}

	return new_poly;
}

Poly Poly::operator-() const{
	Poly new_poly;
	for(map<int, double>::const_iterator it = coefficients.begin();it != coefficients.end(); ++it){
		new_poly.coefficients[(*it).first] = -1 * (*it).second;
	}
	return new_poly;
}

double Poly::operator()(double value_x) const{
	double value = 0;
	for(map<int, double>::const_iterator it = coefficients.begin();it != coefficients.end(); ++it){
		value += (*it).second * pow(value_x, (*it).first);
	}
	return value;
}

ostream& operator<<(ostream &out, Poly pol) {
	string text = "";
	if(pol.coefficients.end() == pol.coefficients.begin()) return out << "0";
	for(map<int, double>::const_iterator it = --(pol.coefficients.end());;){
		stringstream ss;
		ss << (*it).second;
		text += ss.str();
		ss.str(string());
		if ((*it).first > 0 ){
			if((*it).first == 1) text += "x";
			else{
				ss << (*it).first;
				text += "x^" + ss.str();
			}
		}
		if (it == pol.coefficients.begin()) break;
		--it;
		if ((*it).second > 0 && text != "") text += "+";
	}
	return out << erase_one(text);
}
