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

using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	bool t = true;

private:
	
	AnimatedSprite* sun;
	Sprite* planet1;
	Sprite* planet2;
	Sprite* moon1_1;
	Scene* sc;
	Sound* sound;

	DisplayObjectContainer* p1container;
	DisplayObjectContainer* p2container;
	DisplayObjectContainer* allSprites;

	// DisplayObject* character;
};

#endif
