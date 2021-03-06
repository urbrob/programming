#include "assoctab.h"


void assocTabInterface::insert(const char *key, int value) {
    node *nnew = new node(key);
    nnew->next = head;
    head = nnew;
    nnew->val = value;
}

void assocTabInterface::clear() {
    while(head) {
        node *temp = head->next;
        delete head;
        head = temp;
    }
}

assocTabInterface::assocTabInterface() {
    head = NULL;
}

assocTabInterface::~assocTabInterface() {
    if(head) clear();
}

assocTabInterface& assocTabInterface::operator= (const assocTabInterface& tab) {
    if(&tab == this) {
        return *this;
    }
    head = tab.head;
    return *this;
}

int& assocTabInterface::operator[] (const char* str) {
    node *temp = find(str);
    if(!temp) {
        insert(str, 0);
        temp = head;
    }
    return temp->val;
}


assocTabInterface::assocTabInterface (const assocTabInterface& tab) {
    node *src, **dst;
    head = NULL;
    src = tab.head;
    dst = &head;
    try {
        while(src) {
            *dst = new node(*src);
            src = src->next;
            dst = &((*dst)->next);
        }
    }
    catch (...) {
        clear();
        throw;
    }
}

node *assocTabInterface::find(const char *key){
    node * temp = head;
    while(temp) {
        if(!find_pom(temp->key, key)) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

int caseAssocTab::find_pom(const char *key, const char *key2){
    return strcmp(key2, key);
}

int nonCaseAssocTab::find_pom(const char *key, const char *key2){
    return strcasecmp(key2, key);
}
