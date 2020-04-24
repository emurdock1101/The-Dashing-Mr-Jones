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
#include "../engine/tweens/Tween.h"
#include "../engine/tweens/TweenJuggler.h"
#include "../engine/tweens/TweenParam.h"
#include "../engine/tweens/TweenableParams.h"
#include "../engine/events/EventListener.h"

#include "../objects/Rope.h"

using namespace std;

class MyGame : public Game, EventListener{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates);
	virtual void draw(AffineTransform &at);

	void roomTransition(string newSceneFile);

	void handleEvent(Event* e);
	void ropePlaced();
private:
	
	Scene* sc;
	Sound* sound;
	Tween* fadeIn;
	TweenJuggler* juggler = TweenJuggler::getInstance();
	Player* player;
	Sprite* floor;
	CollisionSystem *collisionSystem;
};

#endif
