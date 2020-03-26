#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "Sprite.h"
#include "ControllerState.h"
#include "MyGame.h"
#include "Scene.h"
#include "Camera.h"
#include "Sound.h"
#include "CollisionSystem.h"

using namespace std;
bool idle = false;
bool paused = false;

MyGame::MyGame() : Game(1200, 600) {
	instance = this;

	// MAKE SURE COLLISION SYSTEM DECLARED BEFORE ADDING ANYTHING TO TREE
	collisionSystem = new CollisionSystem();

	character1 = new Sprite("character1","./resources/sprites_unsorted/1 Old_man/Old_man.png");
	character1->position = {0, 0};
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
	character3->width = 100;
	character3->height = 100;
	character3->pivot = {character3->width/2, character3->height/2};
	character3->showHitbox = true;
	character3->hitboxLeftOffset = 10;
	character3->hitboxUpOffset = 50;
	character3->hitboxRightOffset = 60;
	character3->hitboxDownOffset = 0;
	character1->addChild(character3);

	collisionSystem->watchForCollisions("character1", "character3");
}

MyGame::~MyGame(){
	delete collisionSystem;
}

void MyGame::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){
	if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
		character1->position.x += 6;
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		character1->position.x -= 6;
	}
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		character1->position.y += 6;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		character1->position.y -= 6;
	}
	if (pressedKeys.find(SDL_SCANCODE_E) != pressedKeys.end()) {
		character1->rotation += 0.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_R) != pressedKeys.end()) {
		character1->rotation -= 0.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_F) != pressedKeys.end()) {
		character1->scaleX += 0.05;
		character1->scaleY += 0.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_G) != pressedKeys.end()) {
		character1->scaleX -= 0.05;
		character1->scaleY -= 0.05;
	}

	if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {
		character2->position.x += 6;
	}
	if (pressedKeys.find(SDL_SCANCODE_J) != pressedKeys.end()) {
		character2->position.x -= 6;
	}
	if (pressedKeys.find(SDL_SCANCODE_K) != pressedKeys.end()) {
		character2->position.y += 6;
	}
	if (pressedKeys.find(SDL_SCANCODE_I) != pressedKeys.end()) {
		character2->position.y -= 6;
	}
	if (pressedKeys.find(SDL_SCANCODE_O) != pressedKeys.end()) {
		character2->rotation += 0.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
		character2->rotation -= 0.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_N) != pressedKeys.end()) {
		character2->scaleX += 0.05;
		character2->scaleY += 0.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_M) != pressedKeys.end()) {
		character2->scaleX -= 0.05;
		character2->scaleY -= 0.05;
	}

	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		character3->position.x += 6;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		character3->position.x -= 6;
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		character3->position.y += 6;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		character3->position.y -= 6;
	}
	if (pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end()) {
		character3->rotation += 0.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_C) != pressedKeys.end()) {
		character3->rotation -= 0.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_V) != pressedKeys.end()) {
		character3->scaleX += 0.05;
		character3->scaleY += 0.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_B) != pressedKeys.end()) {
		character3->scaleX -= 0.05;
		character3->scaleY -= 0.05;
	}
	collisionSystem->update();
	Game::update(pressedKeys, controllerStates);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}
