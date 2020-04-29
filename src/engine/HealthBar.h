#pragma once
#include "DisplayObjectContainer.h"

class HealthBar : public DisplayObjectContainer {

    public:
        HealthBar();
        HealthBar(string id);

        int scaleX;
        int scaleY;
        SDL_Point position;

        void update(set<SDL_Scancode> pressedKeys, vector<ControllerState*> controllerStates);
	    void draw(AffineTransform &at);

};