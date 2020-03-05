#ifndef TWEENPARAM_H
#define TWEENPARAM_H

#include "../DisplayObject.h"
#include "TweenableParams.h"
//#include "TweenTransitions.h"
#include <string>
#include <fstream>
#include <string>

using namespace std;

class TweenParam {

public:
    TweenParam(string paramToTween, double startVal, double endVal, double time);
    string getParam();
    double getCurVal();
    double getStartVal();
    double getEndVal();
    double getTweenTime();
    double getFrameChangeAmt();
    bool updateParam(DisplayObject object);
    //bool updateParam(DisplayObject object, TweenTransitions* transitions);
private:
    string param;
    double startVal;
    double endVal;
    double time;
    double curVal;
};

#endif