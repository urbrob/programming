#ifndef __ASSOCTAB_H__
#define __ASSOCTAB_H__

#include "string.h"

struct node {
    node *next;
    char *key;
    int val;

    node(const char *str) {
        key = new char[strlen(str) + 1];
        strcpy (key, str);
    };

    ~node() {
        delete[]key;
    }

    node(const node & st) {
        key = new char[strlen(st.key) + 1];
        strcpy(key, st.key);
        val = st.val;
    };
private:
    node & operator= (const node &);
};

class assocTabInterface {
protected:
    node *head;
    void insert(const char *key, int value);
    void clear();
    virtual node *find(const char *key)=0;
public:
    assocTabInterface();
    ~assocTabInterface();
    assocTabInterface (const assocTabInterface & l);
    assocTabInterface& operator= (const assocTabInterface & tab);
    int &operator[] (const char * str);
};

class caseAssocTab : public assocTabInterface {
public:
	node *find(const char *key);
};

class nonCaseAssocTab : public assocTabInterface {
public:
	node *find(const char *key);
};

#endif /* __ASSOCTAB_H__ */
