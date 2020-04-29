#ifndef TWEENPARAM_H
#define TWEENPARAM_H

#include "../DisplayObject.h"
#include "TweenableParams.h"
//#include "TweenTransitions.h"
#include <fstream>
#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

class TweenParam {

public:
    TweenParam(string paramToTween, double startVal, double endVal, double time);
    string getParam();
    double getCurFrame();
    double getStartVal();
    double getEndVal();
    double getTweenTime();
    double getFrameChangeAmt();
    bool isComplete();
    void updateParam(DisplayObject* object);
    //void updateParam(DisplayObject object, TweenTransitions* transitions);
private:
    string param;
    double startVal;
    double endVal;
    double time;
    double curFrame;
    bool complete;
};

#endif