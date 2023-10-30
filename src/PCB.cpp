/*
 * Pcb.cpp
 *
 *  Created on: Aug 26, 2021
 *      Author: OS1
 */

#include "PCB.h"

int PCB::ukID=7;

const int PCB::NEW = 0;
const int PCB::READY = 1;
const int PCB::BLOCKED = 2;
const int PCB::OVER = 3;

extern volatile int dispatched;
extern volatile PCB* running;

void PCB::wrapper(){
	((PCB*)running)->myThread->run();
	lock
	running->state=PCB::OVER;
	PCB* tmp;
	while(running->myQueue->getSize()   > 0){
		tmp=running->myQueue->get();
		tmp->state=PCB::READY;
		Scheduler::put(tmp);
	}
	unlock
	dispatch();
}


PCB::PCB(Thread* myT, StackSize stackSize, Time timeSlice) {
	ID=++ukID;
	myThread = myT;

	state =NEW;

	pcbTimeSlice = timeSlice;
	timePassedCounter=0;

	if(stackSize>MAX_SIZE)pcbStackSize=MAX_SIZE;
	pcbStackSize = stackSize/(sizeof(unsigned));
	stack=0;

	waitTime=-1;

	myQueue= new Queue();
}

PCB::~PCB() {
	if (myQueue) delete myQueue;
	if(stack) delete [] stack;
}

void PCB::createStack(){

	stack=new unsigned [pcbStackSize];
	if (stack==0) return;

	#ifndef BCC_BLOCK_IGNORE
	stack[pcbStackSize - 1] = 0x200;

	stack[pcbStackSize - 2] = FP_SEG(&PCB::wrapper);
	stack[pcbStackSize - 3] = FP_OFF(&PCB::wrapper);

	ss = FP_SEG(stack + pcbStackSize - 12);
	sp = FP_OFF(stack + pcbStackSize - 12);
	bp = sp;
	#endif

}





