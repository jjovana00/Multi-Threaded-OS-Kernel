/*
 * Queue.cpp
 *
 *  Created on: Aug 26, 2021
 *      Author: OS1
 */


#include "Queue.h"
Queue::Queue() {
	head=tail=0;
	size=0;
}

Queue::~Queue() {
	Elem* pom=head;
	while(pom){
		pom=pom->next;
		delete head;
		head=pom;
		size--;
	}
}


void Queue::put(PCB* p){
	if (!head) head=tail=new Elem(p);
	else {
		tail->next=new Elem(p);
		tail=tail->next;
	}
	size++;
}

PCB* Queue::get(){
	if (head==0) return 0;
	Elem* e=head;
	head=head->next;
	if (head==0) tail=0;
	PCB* p=e->pcb;
	delete e;
	size--;
	return p;
}

PCB* Queue::find(ID id){
	Elem* pom=head;
	while (pom){
		if (pom->pcb->ID==id) return pom->pcb;
		pom=pom->next;
	}
	return 0;
}

int Queue::timeIsUp(){
	int counter=0;
	Elem* el=head, *prev=0;
	while (el){
		el->pcb->waitTime--;
		if (el->pcb->waitTime==0){
			if (prev==0) head=head->next;
			else prev->next=el->next;
			if (el==tail){
				if (head!=0) tail=prev;
				else tail=head=0;
			}
			PCB* pom=el->pcb;
			pom->state=PCB::READY;
			Scheduler::put(pom);
			Elem* del=el;
			el=el->next;
			del->next=0;
			delete del;
			size--;
			counter++;
		}
		else{
			prev=el;
			el=el->next;
		}
	}
	return counter;
}

void Queue::remove(PCB* p){
	    Elem* prev=0,*cur=head;
	    while(cur!=0){
	    	if (p==cur->pcb) {
	    		if (!prev) head=head->next;
	    		else prev->next=cur->next;
	    		if (cur==tail){
	    			if (head!=0) tail=prev;
	    			else tail=head=0;
	    		}
	    		cur->next=0;
	    		delete cur;
	    		return;
	    	}
	    	else{
	    		prev=cur;
	    		cur=cur->next;
	    	}
	    }
}

