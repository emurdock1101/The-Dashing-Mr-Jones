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

	sound = new Sound();
	sc = new Scene();
	sc->camera->scaleX = 3;
	sc->camera->scaleY = 3;
	sc->camera->x = -50;
	sc->camera->y = -50;
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
				sc->camera->x -= 6;
			}
			else {
				sound->playSFX("./resources/sounds/TORYAH.wav");
				//player->position.x = 99;
				//sc->camera->x += 6;
			}
		}
		else {
			if (player->position.x < 500) {
				player->position.x += 6;
				sc->camera->x -= 6;
			}
			else {
				sound->playSFX("./resources/sounds/TORYAH.wav");
				//player->position.x = 99;
				//sc->camera->x += 6;
			}
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		if (player->position.x > -100) {
			player->position.x -= 6;
			sc->camera->x += 6;
		}
		else {
			sound->playSFX("./resources/sounds/TORYAH.wav");
			//player->position.x = -99;
			//sc->camera->x -= 6;
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		if (player->position.y < 800) {
			player->position.y += 6;
			sc->camera->y -= 6;
		}
		else {
			sound->playSFX("./resources/sounds/TORYAH.wav");
			//player->position.y = 1;
			//sc->camera->y += 6;
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		if (player->position.x < 150) {
			if (player->position.y > -200) {
				player->position.y -= 6;
				sc->camera->y += 6;
			}
			else {
				sound->playSFX("./resources/sounds/TORYAH.wav");
				//player->position.y = 499;
				//sc->camera->y -= 6;
			}
		}
		else {
			if (player->position.y > 700) {
				player->position.y -= 6;
				sc->camera->y += 6;
			}
			else {
				sound->playSFX("./resources/sounds/TORYAH.wav");
			}
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
		sc->camera->scaleX += .05;
		sc->camera->scaleY += .05;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		if (sc->camera->scaleX > 3 && sc->camera->scaleY > 3) {
			sc->camera->scaleX -= .05;
			sc->camera->scaleY -= .05;
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
		sc->camera->scaleX = 4;
		sc->camera->scaleY = 4;
	}
	if (player->position.y > 100) {
		sc->camera->scaleY = 3;
		sc->camera->scaleX = 3;
	}
	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	at.translate(this->pivot.x, this->pivot.y);
	Game::draw(at);
}
