#include <unordered_map>
#include <vector>
#include <string>

#include "EventDispatcher.h"
#include "EventListener.h"

EventDispatcher::EventDispatcher(){
	this->listeners = new unordered_map<std::string, std::vector<EventListener*>*>();
}

EventDispatcher::~EventDispatcher(){

}

void EventDispatcher::addEventListener(EventListener* l, string eventType){
	unordered_map<string, vector<EventListener*>*>::const_iterator got = this->listeners->find(eventType);
	if (got == this->listeners->end()){
		vector <EventListener*>* temp = new vector<EventListener*>();
		temp->push_back(l);
		this->listeners->emplace(eventType, temp);
	}
	else{
		for (auto event: *listeners){
			if (event.first == eventType){
				event.second->push_back(l);
			}
		}
	}
}

//The EventDispatcher contains a hash map that hold associates an event type with
// each Event Listener that has access to that event type. <string,vector of listeners>
void EventDispatcher::removeEventListener(EventListener*l, string eventType){
	unordered_map<string, vector<EventListener*>*>::const_iterator got = this->listeners->find(eventType);
	if (!(got == this->listeners->end())){
		for (auto event: *listeners){
			if (event.first == eventType){
				for (int i = 0; i < event.second->size(); i++){
					if (event.second->at(i) == l){
						event.second->erase(event.second->begin()+i);
					}
				}
			}
		}
	}
}

bool EventDispatcher::hasEventListener(EventListener* l, string eventType){
	unordered_map<string, vector<EventListener*>*>::const_iterator got = this->listeners->find(eventType);
	if (got == this->listeners->end()){
		return false;
	}
	return true;
}

void EventDispatcher::dispatchEvent(Event* e){
	
}
