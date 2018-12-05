#ifndef __ASSOC_H__
#define __ASSOC_H__
#include <string.h>

using namespace std;

class Assoc {
	struct socket;
	socket* sockets;
	unsigned int capacity;
	unsigned int size;
public:
	Assoc();
	socket* search_by_index(char *index) const;
	int& operator[](char* index);
	int operator[](char* index) const;
};

struct Assoc::socket {
    char* index;
    int val;
    
    socket(const char* zindex, zval) {
        val = zval;
        index = zindex;
    };
};

inline Assoc::Assoc() {
	
}

int Assoc::operator[](char* index) const {
    return data->s[i];
}

int& Assoc::operator[](char* index) {
    return data->s[i];
}

#endif
