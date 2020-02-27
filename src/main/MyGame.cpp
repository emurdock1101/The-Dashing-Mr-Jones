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
	instance = this;

	cammy = new Camera();
	cammy->scaleX = 3;
	cammy->scaleY = 3;
	cammy->x = -50;
	cammy->y = -50;
	sound = new Sound();
	sc = new Scene();
	sc->loadScene("./resources/scenes/Demo2.txt");
	instance->addChild(sc);
	this->pivot.x = this->windowWidth/2;
	this->pivot.y = this->windowHeight/2;
	player = sc->getObj("player");
	sound->playMusic("./resources/sounds/boss.ogg");
}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys){
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		player->position.x += 6;
		cammy->x -= 6;
	}

	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		player->position.x -= 6;
		cammy->x += 6;	
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		player->position.y += 6;
		cammy->y -= 6;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		player->position.y -= 6;
		cammy->y += 6;
	}

	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
		cammy->scaleX += .05;
		cammy->scaleY += .05;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {		
			cammy->scaleX -= .05;
			cammy->scaleY -= .05;
	}

	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	at.translate(this->pivot.x, this->pivot.y);
	at.scale(cammy->scaleX, cammy->scaleY);
	at.translate(cammy->x, cammy->y);
	Game::draw(at);
}
