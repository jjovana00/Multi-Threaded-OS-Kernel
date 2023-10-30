/*
 * Queue.h
 *
 *  Created on: Aug 26, 2021
 *      Author: OS1
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "PCB.h"
#include <stdlib.h>

typedef int ID;

struct Elem{
	PCB* pcb;
	Elem* next;

	Elem(PCB* p) {
		pcb=p;
		next=0;
	}
};

class Queue {

public:
	Queue();
	virtual ~Queue();
	void put(PCB*);
	PCB* get();
	int getSize(){return size;}
	PCB* find(ID);
	int timeIsUp();
	void remove(PCB*);

private:
	Elem* head, *tail;
	int size;

};

#endif /* QUEUE_H_ */
