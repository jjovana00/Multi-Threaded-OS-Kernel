// File: Sem.h

#ifndef _sem_h_
#define _sem_h_

#include "thread.h"
#include "Queue.h"
#include "PCB.h"
#include "KerSem.h"
#include "List.h"

typedef unsigned int Time;
typedef unsigned char IVTNo;

class KernelSem;

class Semaphore {
	public:
		Semaphore (int init=1);
		virtual ~Semaphore ();
		virtual int wait (Time maxTimeToWait);
		virtual void signal();
		int val () const;
private:
		KernelSem* myImpl;
};
#endif
