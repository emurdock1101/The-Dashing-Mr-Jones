#ifndef TWEENJUGGLER_H
#define TWEENJUGGLER_H

#include "Tween.h"
#include <string>
#include <fstream>
#include <vector> 

using namespace std;

class TweenJuggler {

public:
    TweenJuggler();
    static TweenJuggler* getInstance();
    void add(Tween* tween);
    void nextFrame();
    
private:
    static TweenJuggler* instance;
    vector<Tween*> tweenList; 
};

#endif

