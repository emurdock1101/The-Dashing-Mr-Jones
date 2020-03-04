#ifndef QUESTMANAGER_H
#define QUESTMANAGER_H

#include "EventListener.h"

using namespace std;

class QuestManager : public EventListener {
public:
	virtual void handleEvent(Event* e);

private:
};

#endif
