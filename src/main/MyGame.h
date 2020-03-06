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
#include "./tweens/Tween.h"
#include "./tweens/TweenJuggler.h"
#include "./tweens/TweenParam.h"
#include "./tweens/TweenableParams.h"

using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	bool t = true;

private:
	
	Scene* sc;
	Sound* sound;
	Camera* cammy;
	DisplayObjectContainer* player;
	Tween* fadeIn;
	TweenJuggler* juggler = TweenJuggler::getInstance();
};

#endif
