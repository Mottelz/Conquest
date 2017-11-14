#pragma once
#include "Observer.h"
#include <list>
using namespace std;

//Needs to have a forward reference due to 
//circular reference between Observer and Subject
class Observer;

class Subject {
  public:
	virtual void attach(Observer* o);
	virtual void detach(Observer* o);
	virtual void notify();
	list<Observer*> * getObserverList();
	Subject();
	~Subject();
  private:
	list<Observer*> *_observers;
};
