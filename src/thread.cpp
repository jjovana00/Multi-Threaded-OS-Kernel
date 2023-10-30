/*
 * thread.cpp
 *
 *  Created on: Aug 26, 2021
 *      Author: OS1
 */

#include "thread.h"

extern volatile int dispatched;
extern Thread *starting;
extern IdleThread* idleThread;
extern void dispatch();
extern volatile PCB* running;
extern Queue* threads;


Thread::Thread(StackSize stackSize, Time timeSlice) {
	lock
	myPCB=new PCB(this, stackSize, timeSlice);
	if (myPCB!=0) threads->put(myPCB);
	unlock
}

Thread::~Thread(){
	lock
	threads->remove(myPCB);
	if (myPCB) delete myPCB;
    unlock
}

void Thread::start(){
	lock
	if (myPCB->state==PCB::NEW){
		myPCB->state=PCB::READY;
		myPCB->createStack();
		if (myPCB->stack==0) {
				myPCB==0;
				unlock
				return;
		}
		Scheduler::put(myPCB);
	}
	unlock
}


void Thread::waitToComplete(){
	lock
	if (this == starting) { unlock return; }
	if (this == idleThread) { unlock return; }
	if (myPCB->state == PCB::OVER) { unlock return; }
	if (myPCB == (PCB*)running) { unlock return; }
	running->state = PCB::BLOCKED;
	myPCB->myQueue->put((PCB*)running);
	unlock
	dispatch();
}

ID Thread::getId(){
	return (this->myPCB)?this->myPCB->ID:-1;
}

ID Thread::getRunningId(){
	return (running)?running->ID:-1;
}

void Thread::run(){}

Thread* Thread::getThreadById(ID id){
	lock
	PCB* t=threads->find(id);
	unlock
	return t? t->myThread: 0;
}


