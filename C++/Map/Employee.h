#ifndef __EMPLOYEE_H__
#define __EMPLOYEE_H__

#include <string>

using namespace std;

class Employee{
public:
	string full_name;
	string position;
	unsigned int age;
	
	Employee(){
	};
	
	Employee(string full_name, string position, unsigned int age){
		this->full_name = full_name;
		this->position = position;
		this->age = age;
	}
	
	friend ostream &operator<<(std::ostream &out, const Employee& emp) {
		return out << emp.full_name << " " << emp.position << " " << emp.age;;
	};
	
};

#endif
