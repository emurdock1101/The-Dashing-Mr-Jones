#include "Tween.h"
#include "../DisplayObject.h"

Tween::Tween(DisplayObject object) {
    this->object = object;
}
	
Tween::Tween(DisplayObject object, TweenTransitions transitions) {
    this->object = object;
    this->transitions = transitions;
}

void Tween::animate(TweenableParams fieldToAnimate, double startVal, double endVal, double time) {

}

void Tween::update() {

}

bool Tween::isComplete() {

}

void Tween::setValue(TweenableParams param, double value) {

}