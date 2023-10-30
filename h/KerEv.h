/*
 * KerEv.h
 *
 *  Created on: Sep 22, 2021
 *      Author: OS1
 */

#ifndef KEREV_H_
#define KEREV_H_
#include "PCB.h"

typedef unsigned char IVTNo;

class KernelEv {

public:
	KernelEv(IVTNo ivt);
	void wait();
	int getVal(){return val;}
	void signal();
	IVTNo getIVTNo(){return ivtNo;}

private:
	int val;
	IVTNo ivtNo;
	PCB* owner,*blocked;

};

#endif /* KEREV_H_ */
