#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "MyGame.h"
#include "Scene.h"
#include "Camera.h"
#include "Sound.h"

using namespace std;

MyGame::MyGame() : Game(1200, 600) {

	double camScale = 0.2;

	instance = this;

	sound = new Sound();
	sc = new Scene();
	cammy = sc->camera;
	cammy->scaleX = camScale;
	cammy->scaleY = camScale;
	cammy->x = -50;
	cammy->y = -50;
	sc->loadScene("./resources/scenes/area1_room1.txt");
	instance->addChild(sc);
	this->pivot.x = this->windowWidth/2;
	this->pivot.y = this->windowHeight/2;
	player = (DisplayObjectContainer *)sc->getChild("player");
	//sound->playMusic("./resources/sounds/boss.ogg");

	//Commented out code for Tween demo -- causing seg fault
	//player->alpha = 0;
	//fadeIn = new Tween(*player);
	//fadeIn->animate(TweenableParams::ALPHA, player->alpha, 255, 180);
	//juggler->add(fadeIn);
}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){

	//juggler->nextFrame();

	double charSpeed = 25;
	double camSpeed = 25;

	if (pressedKeys.find(SDL_SCANCODE_K) != pressedKeys.end()) {
		player->alpha +=5;
	}

	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		player->position.x += charSpeed;
		cammy->x -= camSpeed;
	}

	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		player->position.x -= charSpeed;
		cammy->x += camSpeed;	
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		player->position.y += charSpeed;
		cammy->y -= camSpeed;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		player->position.y -= charSpeed;
		cammy->y += camSpeed;
	}

	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
		cammy->scaleX += .05;
		cammy->scaleY += .05;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {		
			cammy->scaleX -= .05;
			cammy->scaleY -= .05;
	}

	Game::update(pressedKeys, controllerStates);
}

void MyGame::draw(AffineTransform &at){
	at.translate(this->pivot.x, this->pivot.y);
	Game::draw(at);
}
