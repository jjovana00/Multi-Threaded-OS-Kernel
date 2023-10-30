// File: thread.h
#ifndef _thread_h_
#define _thread_h_

#include "PCB.h"
#include "SCHEDULE.h"
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;
const Time minTimeSlice=1;

class Thread {

public:
	void start();
	void waitToComplete();

	virtual ~Thread();

 	 ID getId();
 	 static ID getRunningId();
 	 static Thread * getThreadById(ID id);
 	 PCB* getMyPCB() { return myPCB; }

 	 Thread (StackSize stackSize = defaultStackSize, Time timeSlice =defaultTimeSlice);

protected:
 	 friend class PCB;
 	 friend class IdleThread;
 	 virtual void run();

private:
 	 PCB* myPCB;
};
void dispatch ();
extern void tick();
#endif
