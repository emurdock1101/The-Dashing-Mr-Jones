#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "../engine/Sprite.h"
#include "../engine/ControllerState.h"
#include "MyGame.h"
#include "../engine/Scene.h"
#include "../engine/Camera.h"
#include "../engine/Sound.h"
#include "../engine/CollisionSystem.h"

using namespace std;
bool idle = false;
bool paused = false;

MyGame::MyGame() : Game(1920, 1000) {
	instance = this;

	// MAKE SURE COLLISION SYSTEM DECLARED BEFORE ADDING ANYTHING TO TREE
	collisionSystem = new CollisionSystem();


	Sprite *background = new Sprite("background", "./resources/tilesets/rooms/a1rm1.png");
	background->position = { 0,0 };
	background->width = 902;
	background->height = 385;
	background->scaleX = 1;
	background->scaleY = 1;
	Game::addChild(background);

	floor = new Sprite("floor", "./resources/floor.png");
	floor->position.y = 500;
	floor->prevPos = floor->position;
	floor->width = 1200;
	floor->height = 200;
	Game::addChild(floor);

	player = new Player("player");
	player->position.y = 0;
	player->position.x = 0;
	player->prevPos = player->position;
	player->showHitbox = true;
	Game::addChild(player);

	collisionSystem->watchForCollisions("floor", "player");

}

MyGame::~MyGame(){
	delete collisionSystem;
}

void MyGame::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){



	Game::update(pressedKeys, controllerStates);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}
