#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "MyGame.h"
#include "Scene.h"
#include "Camera.h"


using namespace std;

MyGame::MyGame() : Game(1200, 600) {
	instance = this;

	cammy = new Camera();
	sc = new Scene();
	sc->loadScene("./resources/scenes/DemoScene.txt");
	instance->addChild(sc);
	this->pivot.x = this->windowWidth/2;
	this->pivot.y = this->windowHeight/2;
	player = sc->getObj("player");

}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys){
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		cammy->x -= 10;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		cammy->x += 10;
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		cammy->y -= 10;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		cammy->y += 10;
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		//player->position.y += 20;
	}
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		player->position.y -= 20;
	}
	if (pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end()) {
		player->position.y += 20;
	}
	if (pressedKeys.find(SDL_SCANCODE_Z) != pressedKeys.end()) {
		player->position.x -= 20;
	}
	if (pressedKeys.find(SDL_SCANCODE_C) != pressedKeys.end()) {
		player->position.x += 20;
	}
	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
		cammy->scaleX += .05;
		cammy->scaleY += .05;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		cammy->scaleX -= .05;
		cammy->scaleY -= .05;
	}
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
		if(t){
			sc->loadScene("./resources/scenes/Scene2.txt");
			t = false;
		}
		else{
			sc->loadScene("./resources/scenes/Scene1.txt");
			t = true;
		}
		
	}
	if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {
	
	}
	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	at.translate(this->pivot.x, this->pivot.y);
	at.scale(cammy->scaleX, cammy->scaleY);
	at.translate(cammy->x, cammy->y);
	Game::draw(at);
}
