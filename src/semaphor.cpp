/*
 * Sem.cpp
 *
 *  Created on: Sep 13, 2021
 *      Author: OS1
 */

#include "semaphor.h"

extern volatile int dispatched;
extern void dispatch();
extern volatile unsigned int lockFlag;
extern List* semaphores;

Semaphore::Semaphore(int init){
	lock
	myImpl=new KernelSem(init);
	if (semaphores==0) semaphores=new List();
	semaphores->put(myImpl);
	unlock
}

Semaphore::~Semaphore(){
	lock
	semaphores->remove(myImpl);
	if (myImpl) delete myImpl;
	unlock
}

int Semaphore::wait(Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
}

void Semaphore::signal(){
	lock
	myImpl->signal();
	unlock
}

int Semaphore::val() const{
	return myImpl->getVal();
}

