/*
 * Idle.h
 *
 *  Created on: Sep 11, 2021
 *      Author: OS1
 */


#ifndef IDLE_H_
#define IDLE_H_

extern volatile int dispatched;
extern void dispatch();

class IdleThread : public Thread{
public:
	IdleThread() : Thread(256, minTimeSlice){}

	void run(){
		while(1){}
	}

	void start(){
		myPCB->state=PCB::READY;
		myPCB->createStack();
	}
};

#endif /* IDLE_H_ */

