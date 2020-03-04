#ifndef TWEENJUGGLER_H
#define TWEENJUGGLER_H

#include "Tween.h"
#include <string>
#include <fstream>

using namespace std;

class TweenJuggler {

public:
    TweenJuggler();
    void add(Tween tween);
    void nextFrame();
private:

};

#endif