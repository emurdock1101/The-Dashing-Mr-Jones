#include "TweenJuggler.h"
#include "Tween.h"

TweenJuggler* TweenJuggler::instance = NULL;

TweenJuggler::TweenJuggler() {}

TweenJuggler* TweenJuggler::getInstance()
{
    if (instance == NULL)
    {
        instance = new TweenJuggler();
    }
    return instance;
}

void TweenJuggler::add(Tween* tween) {
    tweenList.push(tween);
}

void TweenJuggler::nextFrame() {

}