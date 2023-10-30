/*
 * KerSem.h
 *
 *  Created on: Sep 14, 2021
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_

#include "Queue.h"
#include "semaphor.h"

class KernelSem{
	public:
		KernelSem(int);
		~KernelSem();

		int wait (Time maxTimeToWait);
		void signal();
		int getVal() const{return val;}
		static void timer();

	protected:
		void block();
		void unblock();

	private:
		int val;
		Queue* list;
};

#endif /* KERSEM_H_ */
