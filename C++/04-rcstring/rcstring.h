#ifndef __RCSTRING_H__
#define __RCSTRING_H__
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class rcstring {
    struct rctext;
    rctext* data;
public:
    class Range{};
    rcstring();
    rcstring(const char*);
    rcstring(const rcstring&);
    ~rcstring();
    rcstring& operator=(const char*);
    rcstring& operator=(const rcstring&);
    rcstring& operator+=(const rcstring &);
    rcstring operator+(const rcstring &) const;
    rcstring generateSubstring(int len);
    void convertToLowercase();
    int convertToInteger();
    friend ostream& operator<<(ostream&, const rcstring&);
    void check (unsigned int i) const;
    char read(unsigned int i) const;
    void write(unsigned int i, char c);
    char operator[](unsigned int i) const;
    char& operator[](unsigned int i);
};

struct rcstring::rctext {
    char* s;
    unsigned int size;
    unsigned int n;

    rctext(unsigned int nsize, const char* p) {
        n = 1;
        size = nsize;
        s = new char[size + 1];
        strncpy(s, p, size);
        s[size] = '\0';
    };

    ~rctext() {
    delete [] s;
    }

    rctext* detach() {
        if(n == 1) {
            return this;
        }
        rctext* t = new rctext(size, s);
        n--;
        return t;
    }

    void assign(unsigned int nsize, const char *p) {
        if(size != nsize) {
            char* ns = new char[nsize+1];
            size = nsize;
            strncpy(ns, p, size);
            delete [] s;
            s = ns;
        }
        else {
            strncpy(s,p,size);
        }
        s[size]='\0';
    }
private:
    rctext(const rctext&);
    rctext& operator= (const rctext&);
};

inline rcstring::rcstring() {
    data = new rctext(0,"");
}

inline rcstring::rcstring(const rcstring& x) {
    x.data->n++;
    data=x.data;
}
inline rcstring::~rcstring() {
    if(--data->n == 0) {
        delete data;
    }
}

rcstring& rcstring::operator=(const rcstring & x) {
    x.data->n++;
    if(--data->n == 0) {
        delete data;
    }
    data=x.data;
    return *this;
}

rcstring::rcstring(const char* s) {
    data = new rctext(strlen(s), s);
}

rcstring& rcstring::operator=(const char* s) {
    if(data->n == 1) {
        data->assign(strlen(s), s);
    }
    else {
        rctext* t = new rctext(strlen(s),s);
        data->n--;
        data = t;
    }
    return *this;
}

ostream& operator << (ostream& o, const rcstring& s) {
    return o << s.data->s;
}

rcstring& rcstring::operator+=(const rcstring & s) {
    unsigned int newsize = data->size + s.data->size;
    rctext *newdata = new rctext(newsize, data->s);
    strcat(newdata->s, s.data->s);
    if(--data->n == 0) {
        delete data;
    }
    data = newdata;
    return *this;
}

rcstring rcstring::operator+(const rcstring & s) const {
  return rcstring(*this) += s;
}

int rcstring::convertToInteger() {
    return atoi(data->s);
}

void rcstring::convertToLowercase() {
    int i = 0;
    while(data->s[i++]) {
        data->s[i - 1] = tolower(data->s[i - 1]);
    }
}

rcstring rcstring::generateSubstring(int len) {
    int i;
    rcstring new_string = "";
    new_string.data->size = 0;
    for(i = 0; i < len; i++) {
        new_string.data->s[i] = data->s[i];
        new_string.data->size++;
    }
    return new_string;
}


inline void rcstring::check (unsigned int i) const {
    if(data->size <= i)
        throw Range();
}

inline char rcstring::read(unsigned int i) const {
    return data->s[i];
}

inline void rcstring::write(unsigned int i, char c) {
    data = data->detach();
    data->s[i] = c;
}

char rcstring::operator[](unsigned int i) const {
    cout << "char rcstring::operator[](unsigned int i) const" << endl;
    check(i);
    return data->s[i];
}

char& rcstring::operator[](unsigned int i) {
    cout << "char& rcstring::operator[](unsigned int i)" <<endl;
    check(i);
    data = data->detach();
    return data->s[i];
}

#endif /* __RCSTRING_H__ */
