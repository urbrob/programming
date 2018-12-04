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
    rcstring generateSubstring(unsigned int len);
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
    char* s; // Nasz tekst
    unsigned int size; // Jego d³ugoœæ
    unsigned int n; // Licznik referenci / to ile posiada tekstów

	// Zwyk³y konstruktor tworz¹cy tekst 
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

	// Odczepienie referencji do obiektu i zwrócenie go. Jeœli to pojedyncza referencja to tylko zwróæ.
    rctext* detach() {
        if(n == 1) {
            return this;
        }
        rctext* t = new rctext(size, s);
        n--;
        return t;
    }

	// Nadpisanie zawartoœci tekstu
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

// Konstruktory 

inline rcstring::rcstring() {
    data = new rctext(0, "");
}

inline rcstring::rcstring(const rcstring& x) {
    x.data->n++;
    data=x.data;
}

rcstring::rcstring(const char* s) {
    data = new rctext(strlen(s), s);
}


// Destruktor
inline rcstring::~rcstring() {
    if(--data->n == 0) {
        delete data;
    }
}

rcstring& rcstring::operator=(const rcstring & x) {
	// Zwiêksz licznik referencji
    x.data->n++;
	// Jeœli nie ma referencji do obiektu to usuñ
    if(--data->n == 0) {
        delete data;
    }
    // Przypisz nowy rctext
    data = x.data;
    return *this;
}

rcstring& rcstring::operator=(const char* s) {
	// Jeœli rctext ma tylko jedn¹ referencj¹ to zamieñ string
    if(data->n == 1) {
        data->assign(strlen(s), s);
    }
    // w przeciwnimy wypadku stwórz nowy rctext i przypisz go do struktury
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
	// Jeœli nie ma referencji to usuñ dane
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
    rctext* new_text = data->detach();
    char* new_text_pom = new char[data->n + 1];
    while(data->s[i++]) {
        *(new_text_pom + i - 1) = tolower(data->s[i - 1]);
    }
    *(new_text_pom + i) = '\0';
    new_text->s = new_text_pom;
    data = new_text;
}

rcstring rcstring::generateSubstring(unsigned int len) {
    if (len == data->size) return rcstring(*this);
    rcstring new_rctring = rcstring(*this);
	new_rctring.data->detach();
	new_rctring.data->assign(len, new_rctring.data->s);
    return new_rctring;
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
