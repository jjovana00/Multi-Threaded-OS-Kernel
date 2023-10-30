/*
 * IVTE.cpp
 *
 *  Created on: Sep 22, 2021
 *      Author: OS1
 */

#include "IVTE.h"
const int numOfEntries=256;
extern IVTEntry *IVTEntries[numOfEntries];

IVTEntry::IVTEntry(IVTNo ivt,pInterrupt i) {
	ivtNum=ivt;
	myEvent=0;
	oldIRoutine=0;
	newIRoutine=i;
	IVTEntries[ivt]=this;
}

void IVTEntry::callOld(){
	(*oldIRoutine)();
}

void IVTEntry::signal(){
	myEvent->signal();
}
