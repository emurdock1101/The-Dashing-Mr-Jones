#pragma once
#include "DisplayObjectContainer.h"

class Menu : public DisplayObjectContainer {

    public:
        Menu();
        Menu(string id);

        int scaleX;
        int scaleY;
        int alpha;
        SDL_Point position;

        DisplayObjectContainer* outline;

        void update(set<SDL_Scancode> pressedKeys, vector<ControllerState*> controllerStates);
	    void draw(AffineTransform &at);
        
};