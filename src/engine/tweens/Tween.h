#ifndef TWEEN_H
#define TWEEN_H

#include "TweenableParams.h"
#include "TweenParam.h"
#include "TweenTransitions.h"
#include "../DisplayObject.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Tween {

public:
    Tween(DisplayObject* Object);
    Tween(DisplayObject* Object, TweenTransitions* transitions);
    void animate(string fieldToAnimate, double startVal, double endVal, double time);
    void update();
    bool isComplete();
    void setValue(TweenableParams param, double value);
private:
    DisplayObject* object;
    TweenTransitions* transitions;
    vector<TweenParam*> paramList;
    bool complete;
};

#endif