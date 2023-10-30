/*
 * KernelSem.cpp
 *
 *  Created on: Sep 14, 2021
 *      Author: OS1
 */

#include "KerSem.h"

extern volatile int dispatched;
extern void dispatch();
extern volatile PCB* running;
extern volatile unsigned int lockFlag;
extern List* semaphores;

KernelSem::KernelSem(int init) {
	val=init;
	list=new Queue();
}


KernelSem::~KernelSem() {
	if (list) delete list;
}

int KernelSem::wait(Time maxTimeToWait){
	lock
	if (maxTimeToWait!=0) running->waitTime=maxTimeToWait;
	if (--val<0) block();
	else unlock;
	lock
	int ret;
	if (maxTimeToWait!=0 && running->waitTime==0)ret= 0;
	else ret= 1;
	unlock
	return ret;
}

void KernelSem::signal(){
	if (++val<=0) unblock();
}

void KernelSem::block(){
	running->state=PCB::BLOCKED;
	list->put((PCB*)running);
	unlock
	dispatch();
}

void KernelSem::unblock(){
	PCB* temp=list->get();
	temp->state=PCB::READY;
	temp->waitTime=-1;
	Scheduler::put(temp);
}

void KernelSem::timer(){
	lock
	for(Node* cur=semaphores->head; cur!=0; cur=cur->next){
		cur->sem->val+=cur->sem->list->timeIsUp();
	}
	unlock
}
