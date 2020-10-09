// alarm.h 
//	Data structures for a software alarm clock.
//
//	We make use of a hardware timer device, that generates
//	an interrupt every X time ticks (on real systems, X is
//	usually between 0.25 - 10 milliseconds).
//
//	From this, we provide the ability for a thread to be
//	woken up after a delay; we also provide time-slicing.
//
//	NOTE: this abstraction is not completely implemented.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef ALARM_H
#define ALARM_H

#include "copyright.h"
#include "utility.h"
#include "callback.h"
#include "timer.h"
#include <list>
#include "thread.h"

class Process {
  public:
    Process(Thread* t, int x): thread(t), wakeup_time(x) {};
    Thread* thread;
    int wakeup_time;
};

class WaitQueue {
  public:
    WaitQueue():current_time(0) {};
    void addThread(Thread *t, int x);
    bool dispatch();
    bool IsEmpty();
  private:
    int current_time;
    std::list<Process> processes;
};

// The following class defines a software alarm clock. 
class Alarm : public CallBackObj {
  public:
    Alarm(bool doRandomYield);	// Initialize the timer, and callback 
				// to "toCall" every time slice.
    ~Alarm() { delete timer; }
    
    void WaitUntil(int x);	// suspend execution until time > now + x

  private:
    Timer *timer;		// the hardware timer device
    WaitQueue waitQueue;
    void CallBack();		// called when the hardware
				// timer generates an interrupt
};

#endif // ALARM_H
