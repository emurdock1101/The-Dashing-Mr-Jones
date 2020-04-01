#include "TweenJuggler.h"
#include "Tween.h"


TweenJuggler* TweenJuggler::instance = NULL;

TweenJuggler::TweenJuggler() {}

//Singleton Pattern
TweenJuggler* TweenJuggler::getInstance()
{
    if (instance == NULL)
    {
        instance = new TweenJuggler();
    }
    return instance;
}

void TweenJuggler::add(Tween* tween) {
    tweenList.push_back(tween);
}

//Called each update frame in myGame
void TweenJuggler::nextFrame() {
    for (int i = 0; i < tweenList.size(); i++) {
        if (tweenList[i]->isComplete()) {
            tweenList.erase(tweenList.begin() + i);
        }
        else {
            tweenList[i]->update();
        }
    }
}