#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Scene.h"
#include "Sound.h"
#include "Camera.h"
#include "CollisionSystem.h"

using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates);
	virtual void draw(AffineTransform &at);

private:
	Sprite* character1;
	Sprite* character2;
	Sprite* character3;
	Sprite* floor;
	Sprite* gravity;
	CollisionSystem *collisionSystem;
};

#endif
