/*
 * List.cpp
 *
 *  Created on: Sep 14, 2021
 *      Author: OS1
 */

#include "List.h"

extern volatile int dispatched;
int num=1;

List::List() {
	head=tail=0;
	size=0;
}

List::~List() {
	Node* pom=head;
	while(pom){
		pom=pom->next;
		delete head;
		head=pom;
		size--;
	}
}

void List::put(KernelSem* s){
	lock
	if (head==0) head=tail=new Node(s);
	else {
		tail->next=new Node(s);
		tail=tail->next;
	}
	size++;
	unlock
}

void List::remove(KernelSem* s){
	Node* prev=0,*cur=head;
		    while(cur!=0){
		    	if (s==cur->sem) {
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


