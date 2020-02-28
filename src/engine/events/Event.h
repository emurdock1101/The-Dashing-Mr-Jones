#ifndef EVENT_H
#define EVENT_H

#include <string>

#include "EventDispatcher.h"

using namespace std;


class EventDispatcher;

class Event{

public:
	Event(int type, EventDispatcher* source);

	int getType();
	EventDispatcher* getSource();

private:
	// 0 is no event
	int eventType = 0;
	EventDispatcher* source;
	
};

#endif
