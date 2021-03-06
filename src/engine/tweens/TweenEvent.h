#ifndef TWEENEVENT_H
#define TWEENEVENT_H

#include "Tween.h"
#include "../events/Event.h"
#include <string>
#include <fstream>

using namespace std;


class TweenEvent : public Event {

public:
    static const string TWEEN_START_EVENT;
    static const string TWEEN_UPDATING_EVENT;
    static const string TWEEN_COMPLETE_EVENT;

    TweenEvent(string eventType, Tween* tween);
    Tween* getTween();

private:
    Tween* tween;
};

#endif