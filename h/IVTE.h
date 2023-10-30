/*
 * IVTE.h
 *
 *  Created on: Sep 22, 2021
 *      Author: OS1
 */

#ifndef IVTE_H_
#define IVTE_H_
#include "KerEv.h"
#include <dos.h>
#include <iostream.h>
#include <stdio.h>

typedef void interrupt (*pInterrupt)(...);


class IVTEntry {
public:
	IVTEntry(IVTNo ivtNum, pInterrupt);
	void signal();
	void callOld();
	void setEvent(KernelEv* e){
		myEvent=e;
	}

	pInterrupt oldIRoutine, newIRoutine;

private:
	KernelEv* myEvent;
	IVTNo ivtNum;
};

#endif /* IVTE_H_ */
