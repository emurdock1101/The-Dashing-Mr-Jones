#include "TweenParam.h"


TweenParam::TweenParam(string paramToTween, double startVal, double endVal, double time) {
    this->param = paramToTween;
    this->startVal = startVal;
    this->endVal = endVal;
    this->time = time;
    this->curFrame = 0;
    this->complete = false;
}

double TweenParam::getFrameChangeAmt() {
    return (this->endVal - this->startVal) / this->time;
}

void TweenParam::updateParam(DisplayObject* object) {

    if (this->curFrame == this->time) {
        this->complete = true;
        return;
    }

    //if param is X, change object's X position
    if (this->param.compare(TweenableParams::X) == 0) {
        object->position.x += this->getFrameChangeAmt();
    }

    //if param is Y, change object's Y position
    if (this->param.compare(TweenableParams::Y) == 0) {
        object->position.y += this->getFrameChangeAmt();
    }

    //if param is X_SCALE, change object's X scale
    if (this->param.compare(TweenableParams::X_SCALE) == 0) {
        object->scaleX += this->getFrameChangeAmt();
    }

    //if param is Y_SCALE, change object's Y scale
    if (this->param.compare(TweenableParams::Y_SCALE) == 0) {
        object->scaleY += this->getFrameChangeAmt();
    }

    //if param is ALPHA, change object's alpha level
    if (this->param.compare(TweenableParams::ALPHA) == 0) {
        object->alpha += this->getFrameChangeAmt();
    }

    this->curFrame++;
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
double TweenParam::getCurFrame() {return this->curFrame;}
bool TweenParam::isComplete() {return this->complete;}