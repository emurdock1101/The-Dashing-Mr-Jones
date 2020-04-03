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
#include "Text.h"
#include "Menu.h"
#include "HealthBar.h"
#include "../objects/Player.h"
#include "./tweens/Tween.h"
#include "./tweens/TweenJuggler.h"
#include "./tweens/TweenParam.h"
#include "./tweens/TweenableParams.h"

using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates);
	virtual void draw(AffineTransform &at);

private:
	Scene* sc;
	Sound* sound;
	Camera* cammy;
	DisplayObjectContainer* heart1;
	DisplayObjectContainer* heart2;
	DisplayObjectContainer* heart3;
	Tween* heartOut1;
	Tween* heartOut2;
	Tween* heartOut3;
	Tween* heartIn1;
	Tween* heartIn2;
	Tween* heartIn3;
	DisplayObjectContainer* player;
	Tween* fadeIn;
	Tween* fadeInMenu;
	Tween* fadeOutMenu;
	Tween* fadeOutHeart;
	Menu* textBox;
	Text* bubble;
	HealthBar* health;
	TweenJuggler* juggler = TweenJuggler::getInstance();
};

#endif
