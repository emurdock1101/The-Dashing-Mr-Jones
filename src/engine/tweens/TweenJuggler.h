#ifndef TWEENJUGGLER_H
#define TWEENJUGGLER_H

#include "Tween.h"
#include <string>
#include <fstream>
#include <vector> 
#include <stdio.h>
#include <iostream>

using namespace std;

class TweenJuggler {

public:
    static TweenJuggler* getInstance();
    void add(Tween* tween);
    void nextFrame();
    
private:
    TweenJuggler();
    static TweenJuggler* instance;
    vector<Tween*> tweenList; 
};

#endif

