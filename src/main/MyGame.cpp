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

MyGame::MyGame() : Game(1200, 600) {
	instance = this;

	// MAKE SURE COLLISION SYSTEM DECLARED BEFORE ADDING ANYTHING TO TREE
	collisionSystem = new CollisionSystem();

	character1 = new Sprite("character1","./resources/sprites_unsorted/1 Old_man/Old_man.png");
	character1->position = {0, 0};
	character1->prevPos = {0, 0};
	character1->width = 200;
	character1->height = 200;
	character1->pivot = {character1->width/2, character1->height/2};
	character1->hitboxLeftOffset = 20;
	character1->hitboxUpOffset = 60;
	character1->hitboxRightOffset = 100;
	character1->hitboxDownOffset = 0;
	character1->showHitbox = true;
	Game::addChild(character1);

	character2 = new Sprite("character2","./resources/sprites_unsorted/5 Boy/Boy.png");
	character2->position = {0, 200};
	character2->prevPos = {0, 200};
	character2->width = 100;
	character2->height = 100;
	character2->pivot = {character2->width/2, character2->height/2};
	character2->showHitbox = true;
	character2->hitboxLeftOffset = 10;
	character2->hitboxUpOffset = 50;
	character2->hitboxRightOffset = 60;
	character2->hitboxDownOffset = 0;
	character1->addChild(character2);

	character3 = new Sprite("character3","./resources/sprites_unsorted/6 Girl/Girl.png");
	character3->position = {400, 200};
	character3->prevPos = {400, 200};
	character3->width = 100;
	character3->height = 100;
	character3->pivot = {character3->width/2, character3->height/2};
	character3->showHitbox = true;
	character3->hitboxLeftOffset = 10;
	character3->hitboxUpOffset = 50;
	character3->hitboxRightOffset = 60;
	character3->hitboxDownOffset = 0;
	character1->addChild(character3);

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

	gravity = new AnimatedSprite("gravity");
	gravity -> addAnimation("./resources/character/", "Run", 20, 2, true);
	gravity ->play("Run");
	gravity->position.x = 500;
	gravity->width = 75;
	gravity->height = 75;
	Game::addChild(gravity);

	collisionSystem->watchForCollisions("character1", "character3");
	collisionSystem->watchForCollisions("character2", "character3");
	collisionSystem->watchForCollisions("floor", "gravity");
	collisionSystem->watchForCollisions("floor", "player");

}

MyGame::~MyGame(){
	delete collisionSystem;
}

void MyGame::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){
	character1->prevPos = character1->position;
	character2->prevPos = character2->position;
	character3->prevPos = character3->position;
	gravity->prevPos = gravity->position;
	//cout << "Current Position: " << character2->position.x << endl;
	//cout << "Previous Position: " << character2->prevPos.x << endl;

	if (pressedKeys.find(SDL_SCANCODE_1) != pressedKeys.end()) {
		gravity->position.x -= 5;
	}
	if (pressedKeys.find(SDL_SCANCODE_2) != pressedKeys.end()) {
		gravity->position.x += 5;
	}

	if (pressedKeys.find(SDL_SCANCODE_SPACE) != pressedKeys.end()) {
		// gravity->position.y -= 25;
	}
	gravity->position.y += 3;
	collisionSystem->update();
	//cout << "Gravity Previous Position" << gravity->prevPos.y << endl;
	//cout << "Gravity  Position" << gravity->position.y << endl;

	Game::update(pressedKeys, controllerStates);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}
