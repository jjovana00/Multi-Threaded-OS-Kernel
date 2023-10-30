/*
 * KerEv.cpp
 *
 *  Created on: Sep 22, 2021
 *      Author: OS1
 */

#include "KerEv.h"

extern volatile int dispatched;
extern void dispatch();
extern volatile unsigned int lockFlag;
extern volatile PCB* running;

KernelEv::KernelEv(IVTNo ivt) {
	ivtNo=ivt;
	owner=(PCB*)running;
	blocked=0;
	val=0;
}

void KernelEv::wait(){
	if (running != owner) { unlock return; }
	if (val==0) {
		running->state=PCB::BLOCKED;
		blocked=(PCB*)running;
		unlock
		dispatch();
	}
	else {
		val=0;
		unlock
	}
}

void KernelEv::signal(){
	if (blocked==0) val=1;
	else{
		blocked->state=PCB::READY;
		Scheduler::put(blocked);
		blocked=0;
	}
}
