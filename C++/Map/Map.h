#ifndef __MAP_H__
#define __MAP_H__

#include <iostream>
#include <string>

using namespace std;

template <class ID_T, class T>
class Map{
	
	struct record {
	    record *next;
	    ID_T id;
	    T data;
		
		
	    record(ID_T zid, T zdata):next(NULL){
	        id = zid;
	        data = zdata;
	    };
	};
	
	private:
    	record & operator= (const record &);
public:
	record *head;
	Map(){
		head = NULL;
	}
	// If there is no record with given ID, return last record (NULL)
	
	record* find_record(ID_T id){
		record *pom_head = head;
		while(pom_head){
			if(pom_head->id == id) return pom_head->next;
			pom_head = pom_head->next;
		}
		return pom_head;
	}
	
	T* find(ID_T id){
		T* pom = find_record(id)->data
		return pom;
	}
	
	void add(ID_T id, T data){
		record *pom_record = find_record(id);
		pom_record = new record(id, data);
	}
	
	friend ostream &operator<<(std::ostream &out, const Map& map) {
		record *pom_head = map.head;
		while(pom_head){
			out << pom_head->id << " - " << pom_head->data << endl;
		}
		return out<< " KUPA";
	};

};
#endif
