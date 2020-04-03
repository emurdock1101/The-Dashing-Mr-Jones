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

	double camScale = 1;
	instance = this;
	sound = new Sound();
	sc = new Scene();
	cammy = sc->camera;
	cammy->scaleX = camScale;
	cammy->scaleY = camScale;
	cammy->x = -50;
	cammy->y = -50;
	sc->loadScene("./resources/scenes/UI_DEMO/DemoUI.txt");
	instance->addChild(sc);
	this->pivot.x = this->windowWidth/2;
	this->pivot.y = this->windowHeight/2;
	player = (DisplayObjectContainer *)sc->getChild("player");
	heart1 = (DisplayObjectContainer *)sc->getChild("heart1");
	heart1->scaleX = 0.25;
	heart1->scaleY = 0.25;
	heart2 = (DisplayObjectContainer *)sc->getChild("heart2");
	heart2->scaleX = 0.25;
	heart2->scaleY = 0.25;
	heart3 = (DisplayObjectContainer *)sc->getChild("heart3");
	heart3->scaleX = 0.25;
	heart3->scaleY = 0.25;
	//sound->playMusic("./resources/sounds/boss.ogg");
}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){

	juggler->nextFrame();

	double charSpeed = 5;
	double camSpeed = 5;

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

	// if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
	// 	cammy->scaleX += .05;
	// 	cammy->scaleY += .05;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {		
	// 		cammy->scaleX -= .05;
	// 		cammy->scaleY -= .05;
	// }

	// DisplayObjectContainer* end = sc->inScene.back();
	// if (player->position.x ==  end->position.x && player->position.y == end->position.y) {
	// 	sc->loadScene("./resources/scenes/area1_room2.txt");
	// 	player = (DisplayObjectContainer *)sc->getChild("player");
	// 	cammy->x = player->position.x;
	// 	cammy->y = player->position.y;
	// }

	//Simulates losing a heart
	if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
		if (heart3->alpha == 255) {
			heartOut3 = new Tween(heart3);
			heartOut3->animate(TweenableParams::ALPHA, 255, 110, 20);
			juggler->add(heartOut3);
		}
		else if (heart2->alpha == 255) {
			heartOut2 = new Tween(heart2);
			heartOut2->animate(TweenableParams::ALPHA, 255, 110, 20);
			juggler->add(heartOut2);
		}
		else if (heart1->alpha == 255){
			heartOut1 = new Tween(heart1);
			heartOut1->animate(TweenableParams::ALPHA, 255, 110, 20);
			juggler->add(heartOut1);
		}
	}
	//Simulates gaining a heart
	if (pressedKeys.find(SDL_SCANCODE_H) != pressedKeys.end()) {
		if (heart1->alpha < 255) {
			heartIn1 = new Tween(heart1);
			heartIn1->animate(TweenableParams::ALPHA, heart1->alpha, 255, 1);
			juggler->add(heartIn1);
		}
		else if (heart2->alpha < 255) {
			heartIn2 = new Tween(heart2);
			heartIn2->animate(TweenableParams::ALPHA, heart2->alpha, 255, 1);
			juggler->add(heartIn2);
		}
		else if (heart3->alpha < 255) {
			heartIn3 = new Tween(heart3);
			heartIn3->animate(TweenableParams::ALPHA, heart3->alpha, 255, 1);
			juggler->add(heartIn3);
		}
	}

	heart1->setPos(-cammy->x - 600, -cammy->y - 300);
	heart2->setPos(-cammy->x - 575, -cammy->y - 300);
	heart3->setPos(-cammy->x - 550, -cammy->y - 300);

	Game::update(pressedKeys, controllerStates);
}

void MyGame::draw(AffineTransform &at){
	at.translate(this->pivot.x, this->pivot.y);
	Game::draw(at);
}
