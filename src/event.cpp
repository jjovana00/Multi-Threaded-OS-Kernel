/*
 * event.cpp
 *
 *  Created on: Sep 22, 2021
 *      Author: OS1
 */

#include "event.h"

extern volatile int dispatched;
extern void dispatch();
extern volatile unsigned int lockFlag;
const int numOfEntries=256;
extern IVTEntry *IVTEntries[numOfEntries];

Event::Event(IVTNo ivtNo) {
	lock
	myImpl=new KernelEv(ivtNo);
	IVTEntries[ivtNo]->oldIRoutine=getvect(ivtNo);
	setvect(ivtNo,IVTEntries[ivtNo]->newIRoutine);
	IVTEntries[ivtNo]->setEvent(myImpl);
	unlock
}

Event::~Event() {
	lock
	setvect(myImpl->getIVTNo(),IVTEntries[myImpl->getIVTNo()]->oldIRoutine);
	if (myImpl) delete myImpl;
	unlock
}

void Event::wait(){
	lock
	myImpl->wait();
}

void Event::signal(){
	lock
	myImpl->signal();
	unlock
}

