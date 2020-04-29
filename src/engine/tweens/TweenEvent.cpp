#include "TweenEvent.h"

const string TweenEvent::TWEEN_START_EVENT = "TWEEN_START_EVENT";
const string TweenEvent::TWEEN_UPDATING_EVENT = "TWEEN_UPDATING_EVENT";
const string TweenEvent::TWEEN_COMPLETE_EVENT = "TWEEN_COMPLETE_EVENT";

TweenEvent::TweenEvent(string eventType, Tween* tween) : Event(0, NULL) {
    this->tween = tween;
}
	
Tween* TweenEvent::getTween() {
    return this->tween;
}

