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
#include "../engine/CollisionSystem.h"
#include "../objects/Player.h"

using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates);
	virtual void draw(AffineTransform &at);

private:
	Player* player;
	Sprite* character1;
	Sprite* character2;
	Sprite* character3;
	Sprite* floor;
	AnimatedSprite* gravity;
	CollisionSystem *collisionSystem;
};

#endif
