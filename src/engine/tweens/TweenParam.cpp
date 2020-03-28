#include "TweenParam.h"


TweenParam::TweenParam(string paramToTween, double startVal, double endVal, double time) {
    this->param = paramToTween;
    this->startVal = startVal;
    this->endVal = endVal;
    this->time = time;
    this->curVal = 0;
    this->complete = false;
}

double TweenParam::getFrameChangeAmt() {
    return (this->startVal + this->endVal) / this->time;
}

void TweenParam::updateParam(DisplayObject object) {

    if (this->curVal == this->endVal) {
        this->complete = true;
        return;
    }

    //if param is X, change object's X position
    if (this->param.compare(TweenableParams::X) == 0) {
        object.position.x += this->getFrameChangeAmt();
        this->curVal = object.position.x;
    }

    //if param is Y, change object's Y position
    if (this->param.compare(TweenableParams::Y) == 0) {
        object.position.y += this->getFrameChangeAmt();
        this->curVal = object.position.y;
    }

    //if param is X_SCALE, change object's X scale
    if (this->param.compare(TweenableParams::X_SCALE) == 0) {
        object.scaleX += this->getFrameChangeAmt();
        this->curVal = object.scaleX;
    }

    //if param is Y_SCALE, change object's Y scale
    if (this->param.compare(TweenableParams::Y_SCALE) == 0) {
        object.scaleY += this->getFrameChangeAmt();
        this->curVal = object.scaleY;
    }

    //if param is ALPHA, change object's alpha level
    if (this->param.compare(TweenableParams::ALPHA) == 0) {
        object.alpha += this->getFrameChangeAmt();
        this->curVal = object.alpha;
    }
}

// bool TweenParam::updateParam(DisplayObject object, TweenTransitions* transitions) {
//     //Calls one argument version if no transitions specified
//     if (transitions == NULL) {
//         updateParam(object);
//     }
//
// }

string TweenParam::getParam() {return this->param;}
double TweenParam::getStartVal() {return this->startVal;}
double TweenParam::getEndVal() {return this->endVal;}
double TweenParam::getTweenTime() {return this->time;}
double TweenParam::getCurVal() {return this->curVal;}
bool TweenParam::isComplete() {return this->complete;}