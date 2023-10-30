/*
 * System.h
 *
 *  Created on: Sep 7, 2021
 *      Author: OS1
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "SCHEDULE.h"
#include <dos.h>
#include <stdlib.h>
#include "PCB.h"
#include "thread.h"
#include "Idle.h"
#include "List.h"
#include "Event.h"
#include "IVTE.h"

typedef void interrupt (*Interrupt)(...);
typedef unsigned char IVTNo;

void init();
void term();
void dispatch();

void interrupt timerIRoutine(...);

#endif
