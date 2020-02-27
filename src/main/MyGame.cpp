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
	sc->loadScene("./resources/scenes/DemoScene.txt");
	instance->addChild(sc);
	this->pivot.x = this->windowWidth/2;
	this->pivot.y = this->windowHeight/2;
	player = (DisplayObjectContainer *)sc->getChild("player");
	sound->playMusic("./resources/sounds/boss.ogg");

}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys){
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		if (player->position.y < 600) {
			if (player->position.x < 100) {
				player->position.x += 6;
				cammy->x -= 6;
			}
			else {
				sound->playSFX("./resources/sounds/TORYAH.wav");
				//player->position.x = 99;
				//cammy->x += 6;
			}
		}
		else {
			if (player->position.x < 500) {
				player->position.x += 6;
				cammy->x -= 6;
			}
			else {
				sound->playSFX("./resources/sounds/TORYAH.wav");
				//player->position.x = 99;
				//cammy->x += 6;
			}
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		if (player->position.x > -100) {
			player->position.x -= 6;
			cammy->x += 6;
		}
		else {
			sound->playSFX("./resources/sounds/TORYAH.wav");
			//player->position.x = -99;
			//cammy->x -= 6;
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		if (player->position.y < 800) {
			player->position.y += 6;
			cammy->y -= 6;
		}
		else {
			sound->playSFX("./resources/sounds/TORYAH.wav");
			//player->position.y = 1;
			//cammy->y += 6;
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		if (player->position.x < 150) {
			if (player->position.y > -200) {
				player->position.y -= 6;
				cammy->y += 6;
			}
			else {
				sound->playSFX("./resources/sounds/TORYAH.wav");
				//player->position.y = 499;
				//cammy->y -= 6;
			}
		}
		else {
			if (player->position.y > 700) {
				player->position.y -= 6;
				cammy->y += 6;
			}
			else {
				sound->playSFX("./resources/sounds/TORYAH.wav");
			}
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
		cammy->scaleX += .05;
		cammy->scaleY += .05;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		if (cammy->scaleX > 3 && cammy->scaleY > 3) {
			cammy->scaleX -= .05;
			cammy->scaleY -= .05;
		}
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
	if (player->position.y <= 100) { 
		cammy->scaleX = 4;
		cammy->scaleY = 4;
	}
	if (player->position.y > 100) {
		cammy->scaleY = 3;
		cammy->scaleX = 3;
	}
	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	at.translate(this->pivot.x, this->pivot.y);
	at.scale(cammy->scaleX, cammy->scaleY);
	at.translate(cammy->x, cammy->y);
	Game::draw(at);
}
