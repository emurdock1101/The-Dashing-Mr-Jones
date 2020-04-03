#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "MyGame.h"
#include "Scene.h"
#include "Camera.h"
#include "Sound.h"
#include "Text.h"

using namespace std;

MyGame::MyGame() : Game(1200, 600) {

	double camScale = .5;

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
	player = (Player*)sc->getChild("player");
	sound->playMusic("./resources/sounds/boss.ogg");

	textBox = new Menu("box1");
	instance->addChild(textBox);
	
	instance->getChild("box1")->position = {-600,-300};
	instance->getChild("box1")->scaleX = 5;
	instance->getChild("box1")->scaleY = 3;
	instance->getChild("box1")->alpha = 0;

	health = new HealthBar("health");
	instance->addChild(health);

	//Commented out code for Tween demo -- causing seg fault
	player->alpha = 0;
	fadeIn = new Tween(player);
	fadeIn->animate(TweenableParams::ALPHA, player->alpha, 255, 180);
	juggler->add(fadeIn);
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

	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
		cammy->scaleX += .05;
		cammy->scaleY += .05;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {		
		cammy->scaleX -= .05;
		cammy->scaleY -= .05;
	}

	if (pressedKeys.find(SDL_SCANCODE_M) != pressedKeys.end()) {
		//if (instance->getChild("box1")->alpha == 0) {
		fadeInMenu = new Tween(instance->getChild("box1"));
		fadeInMenu->animate(TweenableParams::ALPHA, instance->getChild("box1")->alpha, 255, 180);
		juggler->add(fadeInMenu);
		//}
		//else {
		fadeOutMenu = new Tween(instance->getChild("box1"));
		fadeOutMenu->animate(TweenableParams::ALPHA, instance->getChild("box1")->alpha, 0, 180);
		juggler->add(fadeOutMenu);
		//}
	}

	// DisplayObjectContainer* end = sc->inScene.back();
	// if (player->position.x ==  end->position.x && player->position.y == end->position.y) {
	// 	sc->loadScene("./resources/scenes/area1_room2.txt");
	// 	player = (DisplayObjectContainer *)sc->getChild("player");
	// 	cammy->x = player->position.x;
	// 	cammy->y = player->position.y;
	// }

	if (player->position.x > 50) {
		bubble = new Text("./resources/OpenSans-Regular.ttf", 15, {255,255,255}, "Press 'm' to open the menu!", 650, 300);
		instance->addChild((DisplayObjectContainer*) bubble);
		if (player->position.x > 290) {
			bubble->setText("");
		}
	}

	if (player->position.x > 500) {
		health->removeChild(2);
		health->addChild(new DisplayObjectContainer("heart3", "./resources/objects/heart2.png"));
		instance->addChild((DisplayObjectContainer*) new Text("./resources/OpenSans-Regular.ttf", 15, {255,255,255}, "Uh oh, you lost health!", 100, 500));
	}

	Game::update(pressedKeys, controllerStates);
}

void MyGame::draw(AffineTransform &at){
	at.translate(this->pivot.x, this->pivot.y);
	Game::draw(at);
}
