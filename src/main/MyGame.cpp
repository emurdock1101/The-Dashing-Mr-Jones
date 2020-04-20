#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../engine/Sprite.h"
#include "../engine/ControllerState.h"
#include "MyGame.h"
#include "../engine/Scene.h"
#include "../engine/Camera.h"
#include "../engine/Sound.h"
#include "../engine/CollisionSystem.h"

using namespace std;

MyGame::MyGame() : Game(1920, 1000) {

	// MAKE SURE COLLISION SYSTEM DECLARED BEFORE ADDING ANYTHING TO TREE
	collisionSystem = new CollisionSystem();

	double camScale = 0.6;

	instance = this;

	sound = new Sound();
	sc = new Scene();
	cammy = sc->camera;
	cammy->scaleX = camScale;
	cammy->scaleY = camScale;
	cammy->x = -this->windowWidth;
	cammy->y = -this->windowHeight;
	sc->loadScene("./resources/scenes/area1_room1.txt");
	instance->addChild(sc);
	this->pivot.x = this->windowWidth/2;
	this->pivot.y = this->windowHeight/2;
	player = (Player*)sc->getChild("player");
	sound->playMusic("./resources/sounds/boss.ogg");

	//Commented out code for Tween demo -- causing seg fault
	//player->alpha = 0;
	//fadeIn = new Tween(*player);
	//fadeIn->animate(TweenableParams::ALPHA, player->alpha, 255, 180);
	//juggler->add(fadeIn);
	




	// Sprite *background = new Sprite("background", "./resources/tilesets/rooms/a1rm1.png");
	// background->position = { 0,0 };
	// background->width = 902;
	// background->height = 385;
	// background->scaleX = 1;
	// background->scaleY = 1;
	// Game::addChild(background);

	// floor = new Sprite("floor", "./resources/floor.png");
	// floor->position.y = 500;
	// floor->prevPos = floor->position;
	// floor->width = 1200;
	// floor->height = 200;
	// Game::addChild(floor);

	// player = new Player("player");
	// player->position.y = 0;
	// player->position.x = 0;
	// player->prevPos = player->position;
	// player->showHitbox = true;
	// Game::addChild(player);

	collisionSystem->camera = cammy;
	collisionSystem->watchForCollisions("0", "player");

}

MyGame::~MyGame(){
	delete collisionSystem;
}


void MyGame::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){

	//juggler->nextFrame();

	double charSpeed = 25;
	double camSpeed = 25;

	double camDeadzoneX = 100;
	double camDeadzoneY = 100;
	// if (pressedKeys.find(SDL_SCANCODE_K) != pressedKeys.end()) {
	// 	player->alpha +=5;
	// }
	// 
	// if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
	// 	player->position.x += charSpeed;
	// 	cammy->x -= camSpeed;
	// }
	// 
	// if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
	// 	player->position.x -= charSpeed;
	// 	cammy->x += camSpeed;	
	// }
	// if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
	// 	player->position.y += charSpeed;
	// 	cammy->y -= camSpeed;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
	// 	player->position.y -= charSpeed;
	// 	cammy->y += camSpeed;
	// }

	if (player->position.x - cammy->x > camDeadzoneX) {
		cammy->x = player->position.x - camDeadzoneX;
	}
	else if (player->position.x - cammy->x < -camDeadzoneX) {
		cammy->x = player->position.x + camDeadzoneX;
	}
	if (player->position.y - cammy->y > camDeadzoneY) {
		cammy->y = player->position.y - camDeadzoneY;
	}
	else if (player->position.y - cammy->y < -camDeadzoneY) {
		cammy->y = player->position.y + camDeadzoneY;
	}

	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
		cammy->scaleX += .05;
		cammy->scaleY += .05;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {		
			cammy->scaleX -= .05;
			cammy->scaleY -= .05;
	}

	DisplayObjectContainer* end = sc->inScene.back();
	if (player->position.x ==  end->position.x && player->position.y == end->position.y) {
		sc->loadScene("./resources/scenes/area1_room2.txt");
		player = (Player*)sc->getChild("player");
		cammy->x = player->position.x;
		cammy->y = player->position.y;
	}

	Game::update(pressedKeys, controllerStates);
	collisionSystem->update();
}

void MyGame::draw(AffineTransform &at){
	at.translate(this->pivot.x, this->pivot.y);
	Game::draw(at);
}