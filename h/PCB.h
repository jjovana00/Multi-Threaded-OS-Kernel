/*
 * PCB.h
 *
 *  Created on: Aug 26, 2021
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include <dos.h>
#include <stdlib.h>
#include "thread.h"
#include "SCHEDULE.H"
#include "Queue.h"

typedef unsigned long StackSize;
typedef unsigned int Time;
typedef int ID;

#define MAX_SIZE 65535

extern volatile unsigned int lockFlag;

#define lock lockFlag--;

#define unlock lockFlag++;\
	if (dispatched==1){\
		dispatch();\
}

class Queue;
class Thread;

class PCB {

public:
	PCB(Thread* myT, StackSize stackSize, Time timeSlice);
	virtual ~PCB();

	static const int NEW, READY, BLOCKED, OVER;
	volatile int state;


	 friend class Thread;
	 Thread* myThread;
	 unsigned int sp, ss, bp;

	 static ID ukID;
	 ID ID;


	 volatile Time timePassedCounter;
	 Time pcbTimeSlice;

	 StackSize pcbStackSize;
	 unsigned* stack;

	 Queue* myQueue;

	 int waitTime;

	 void createStack();

	 static void wrapper();
};


#endif
