#include "Event.h"
#include "EventDispatcher.h"
#include <iostream>
#include <string>

using namespace std;

Event::Event(int type, EventDispatcher* source){
	this->eventType = type;
	this->source = source;
}


int Event::getType(){
	return this->eventType;
}

EventDispatcher* Event::getSource(){
	return this->source;
}

