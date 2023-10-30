/*
 * System.cpp
 *
 *  Created on: Sep 7, 2021
 *      Author: OS1
 */

#include "System.h"

volatile unsigned int lockFlag=1;
volatile PCB* running=0;
volatile int dispatched=0;
Thread *starting=0;
IdleThread* idleThread=0;
void interrupt (*oldIRoutine)(...) = 0;
Queue* threads=0;
List* semaphores=0;
const int numOfEntries=256;
IVTEntry *IVTEntries[numOfEntries]={0};

void tick();
int userMain(int, char*[]);

void init(){
	lock
	oldIRoutine=getvect(0x08);
	setvect(0x08,timerIRoutine);
	threads=new Queue();
	idleThread = new IdleThread();
	idleThread->start();
	if (semaphores == 0) semaphores = new List();
	starting = new Thread(1024, minTimeSlice);
	starting->getMyPCB()->state=PCB::READY;
	running = (volatile PCB*)starting->getMyPCB();
	unlock
}

void dispatch(){
	asm cli
	dispatched=1;
	timerIRoutine();
	asm sti
}

void term(){
	if ((PCB*)running!=starting->getMyPCB()) return;
	lock
	setvect(0x08,oldIRoutine);
	delete starting;
	delete threads;
	delete semaphores;
	delete idleThread;
	unlock

}


void interrupt timerIRoutine(...){
	static unsigned int tsp,tss,tbp;
	static volatile PCB* newThread;

	if (!dispatched){
		tick();
		(*oldIRoutine)();
		KernelSem::timer();
	}


	if (!dispatched && running->pcbTimeSlice!=0) running->timePassedCounter++;

	if (!dispatched && (running->timePassedCounter< running->pcbTimeSlice || running->pcbTimeSlice==0)) return;

	if (dispatched || running->timePassedCounter>= running->pcbTimeSlice){
		if (lockFlag>0){
			if( running->state == PCB::READY && running != idleThread->getMyPCB() ) Scheduler::put((PCB*)running);
			while(1){
				newThread = Scheduler::get();
				if (newThread == 0) newThread = idleThread->getMyPCB();
				if (newThread->state != PCB::READY) continue;

				asm{
					mov tsp,sp
					mov tss,ss
					mov tbp,bp
				}

				running->sp=tsp;
				running->ss=tss;
				running->bp=tbp;

				running=newThread;

				tsp=running->sp;
				tss=running->ss;
				tbp=running->bp;

				asm{
					mov sp,tsp
					mov ss,tss
					mov bp,tbp
				}

				running->timePassedCounter=0;
				dispatched=0;
				break;
			}
		}
		else dispatched=1;
	}
}

int main(int argc, char** argv){

	init();

	int ret=userMain(argc,argv);

	term();

	return ret;

}
