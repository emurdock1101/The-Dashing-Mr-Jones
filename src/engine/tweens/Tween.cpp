#include "Tween.h"


Tween::Tween(DisplayObject* object) {
    this->object = object;
    this->transitions = NULL;
}
	
Tween::Tween(DisplayObject* object, TweenTransitions* transitions) {
    this->object = object;
    this->transitions = transitions;
}

void Tween::animate(string fieldToAnimate, double startVal, double endVal, double time) {
    this->paramList.push_back(new TweenParam(fieldToAnimate, startVal, endVal, time));
}

//Updates each individual param. Also sets Tween.complete to true
//if all of the Tween's params have finished updating.
void Tween::update() {
    
    for (int i = 0; i < paramList.size(); i++) {
       paramList[i]->updateParam(this->object);
    }
}

bool Tween::isComplete() {
    bool check = true;
    for (int i = 0; i < paramList.size(); i++) {
       check = check && paramList[i]->isComplete();
    }
    return check;
}

void Tween::setValue(TweenableParams param, double value) {

}