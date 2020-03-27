#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../engine/Game.h"
#include "../engine/Sprite.h"
#include "../engine/AnimatedSprite.h"
#include "../engine/Scene.h"
#include "../engine/Sound.h"
#include "../engine/Camera.h"

using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates);
	virtual void draw(AffineTransform &at);

private:
	AnimatedSprite* character;
};

#endif
