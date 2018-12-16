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

			record(const record &rec) {
				id = rec.id;
				next = rec.next;
				data = rec.data;
			}

	    record(ID_T zid, T zdata):next(NULL){
	        id = zid;
	        data = zdata;
	    };
			
			record &operator=(record rec){
				record new_rec;
				new_rec->id = rec.id;
				new_rec->next = rec.next;
				new_rec->data = rec.data;
				return &new_rec;
			}
	};

public:
	record *head;

	Map(){
		head = NULL;
	}

	T *find(const ID_T key){
		record *table = head;
		while (table){
			if (key == table->id)
				return &table->data;
			table = table->next;
		}
		return NULL;
	}

	void add(ID_T id, T data){
		if(!head) head = new record(id, data);
		else {
			record* pom = head;
			while(pom){
				if(pom->id == id){
					delete &pom->data;
					pom->data = data;
					break;
				}
				if(!pom->next) break;
				pom = pom->next;
			}
			pom->next = new record(id, data);
		}
	}

	friend ostream &operator<<(std::ostream &out, const Map& map) {
		record *pom_head = map.head;
		while(pom_head){
			out << pom_head->id << " - " << pom_head->data << endl;
			pom_head = pom_head->next;
		}
		return out;
	};

};
#endif
