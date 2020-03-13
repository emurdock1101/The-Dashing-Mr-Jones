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

using namespace std;
bool idle = false;
bool paused = false;

MyGame::MyGame() : Game(1200, 600) {
	instance = this;

	character1 = new Sprite("character1","./resources/sprites_unsorted/1 Old_man/Old_man.png");
	character1->position = {0, 0};
	character1->width = 200;
	character1->height = 200;
	character1->pivot = {character1->width/2, character1->height/2};
	Game::addChild(character1);

	character2 = new Sprite("character2","./resources/sprites_unsorted/5 Boy/Boy.png");
	character2->position = {200, 200};
	character2->width = 100;
	character2->height = 100;
	character2->pivot = {character2->width/2, character2->height/2};
	character1->addChild(character2);

	character3 = new Sprite("character3","./resources/sprites_unsorted/6 Girl/Girl.png");
	character3->position = {400, 200};
	character3->width = 100;
	character3->height = 100;
	character3->pivot = {character3->width/2, character3->height/2};
	character1->addChild(character3);
}

MyGame::~MyGame(){

}

void MyGame::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){
	if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
		character1->position.x += 6;
		character1->facingRight = true;
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		character1->position.x -= 6;
		character1->facingRight = false;
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
		character2->facingRight = true;
	}
	if (pressedKeys.find(SDL_SCANCODE_J) != pressedKeys.end()) {
		character2->position.x -= 6;
		character2->facingRight = false;
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
		character3->facingRight = true;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		character3->position.x -= 6;
		character3->facingRight = false;
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
	Game::update(pressedKeys, controllerStates);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
	character1->displayHitbox();
	character2->displayHitbox();
	character3->displayHitbox();
}
