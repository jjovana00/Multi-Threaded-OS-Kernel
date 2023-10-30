/*
 * event.h
 *
 *  Created on: Sep 22, 2021
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_
#include "KerEv.h"
#include "IVTE.h"

typedef unsigned char IVTNo;
typedef void interrupt (*pInterrupt)(...);
class KernelEv;

#define PREPAREENTRY(numEntry, callOldFlag)\
void interrupt inter##numEntry(...); \
IVTEntry newEntry##numEntry(numEntry, inter##numEntry); \
void interrupt inter##numEntry(...) {\
newEntry##numEntry.signal();\
if (callOldFlag == 1)\
newEntry##numEntry.callOld();\
}

class Event {
	public:
		Event (IVTNo ivtNo);
		~Event ();
		void wait ();

	protected:
		friend class KernelEv;
		void signal(); // can call KernelEv

	private:
		KernelEv* myImpl;
};

#endif /* EVENT_H_ */
