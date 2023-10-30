/*
 * List.h
 *
 *  Created on: Sep 14, 2021
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_

#include "KerSem.h"
class KernelSem;

struct Node{
	KernelSem* sem;
	Node* next;

	Node(KernelSem* s){
		sem=s;
		next=0;
	}
};

class List {
public:
	List();
	virtual ~List();
	void put(KernelSem*);
	int getSize(){return size;}
	void remove(KernelSem*);

private:
	friend class KernelSem;
	Node* head, *tail;
	int size;
};

#endif /* LIST_H_ */
