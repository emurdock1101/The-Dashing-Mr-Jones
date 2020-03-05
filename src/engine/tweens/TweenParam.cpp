#include "TweenParam.h"


TweenParam::TweenParam(string paramToTween, double startVal, double endVal, double time) {
    this->param = paramToTween;
    this->startVal = startVal;
    this->endVal = endVal;
    this->time = time;
    this->curVal = 0;
}

double TweenParam::getFrameChangeAmt() {
    return (this->startVal + this->endVal) / this->time;
}

bool TweenParam::updateParam(DisplayObject object) {

    if (this->curVal == this->endVal) {
        return true;
    }

    //if param is X, change object's X position
    if (this->param.compare(TweenableParams::X) == 0) {
        object.position.x += this->getFrameChangeAmt();
        this->curVal = object.position.x;
    }

    //if param is Y, change object's Y position
    if (this->param.compare(TweenableParams::Y) == 0) {
        object.position.y += this->getFrameChangeAmt();
        this->curVal = object.position.x;
    }

    return false;
}

// bool TweenParam::updateParam(DisplayObject object, TweenTransitions* transitions) {
//     //Calls one argument version if no transitions specified
//     if (transitions == NULL) {
//         return updateParam(object);
//     }

//     return false;
// }

string TweenParam::getParam() {return this->param;}
double TweenParam::getStartVal() {return this->startVal;}
double TweenParam::getEndVal() {return this->endVal;}
double TweenParam::getTweenTime() {return this->time;}
double TweenParam::getCurVal() {return this->curVal;}