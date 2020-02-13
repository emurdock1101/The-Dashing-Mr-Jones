#include "Event.h"
#include "EventDispatcher.h"
#include <iostream>
#include <string>

using namespace std;

const string Event::COIN_PICKED_UP = "COIN_PICKED_UP";

Event::Event(string type, EventDispatcher* source){
	this->eventType = type;
	this->source = source;
}


string Event::getType(){
	return this->eventType;
}

EventDispatcher* Event::getSource(){
	return this->source;
}

