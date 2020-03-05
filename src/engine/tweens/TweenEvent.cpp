#include "TweenEvent.h"

TweenEvent::TweenEvent(string eventType, Tween* tween) : Event(0, NULL) {
    this->tween = tween;
}
	
// Tween TweenEvent::getTween() {
//     return this->tween;
// }

