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

MyGame::MyGame() : Game(1920, 1000), EventListener() {

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
	instance->addChild(sc);


	player = new Player("player");
	player->position.y = 0;
	player->position.x = 0;
	player->prevPos = player->position;
	player->addEventListener((EventListener*)this, EventParams::ROPE_DEPLOYED);

	//change to area1_room2.txt to view room 2 directly
	roomTransition("./resources/scenes/area1_room1.txt");

	Mummy* mummy = new Mummy("name");
	mummy -> position.x = 500;
	mummy -> position.y = 500;
	sc->addChild(mummy);

	this->pivot.x = this->windowWidth/2;
	this->pivot.y = this->windowHeight/2;
	//sound->playMusic("./resources/sounds/boss.ogg");

	collisionSystem->camera = cammy;
	collisionSystem->watchForCollisions("0", "player");
	collisionSystem->watchForCollisions("0", "rope_seg", false);
	collisionSystem->watchForCollisions("rope_seg", "player", false);
	collisionSystem->watchForCollisions("room_change", "player", false);
}

MyGame::~MyGame(){
	delete collisionSystem;
}

void MyGame::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){

	//juggler->nextFrame();

	//used for testing
	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
		cammy->scaleX += .05;
		cammy->scaleY += .05;
	}
	//used for testing
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		cammy->scaleX -= .05;
		cammy->scaleY -= .05;
	}

	double camDeadzoneX = 100;
	double camDeadzoneY = 100;

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

	Game::update(pressedKeys, controllerStates);
	collisionSystem->update();
}

void MyGame::draw(AffineTransform &at){
	at.translate(this->pivot.x, this->pivot.y);
	Game::draw(at);
}

void MyGame::handleEvent(Event* e) { // MyGame can listen to events.
	if (e->getSource() == player) {
		// player-specific event handling
		switch (e->getType()) {
		case EventParams::ROPE_DEPLOYED:
			ropePlaced();
		}
	}
	else {
		// any entity event handling
		switch (e->getType()) {
		case EventParams::ROOM_CHANGED:
			// roomChange: make MyGame dispatch an event, listened to by Scene
			dispatchEvent(e);
			roomTransition(((RoomChangeBlock*)e->getSource())->sceneFile);
		}
	}
}
void MyGame::ropePlaced() {
	if (player != NULL) {
		Rope* newRope = player->makeRope();
		newRope->position = player->position;
		if (player->facingRight) {
			newRope->position.x += 150;
		}
		else {
			newRope->position.x -= 150;
		}
		newRope->position.y += 100;
		sc->addChild(newRope);
	}
}

void MyGame::roomTransition(string sceneFile) {
	sc->removeImmediateChild(player);
	sc->loadScene(sceneFile);
	DisplayObject* playerSpawn = sc->getChild("player_spawn");
	if (playerSpawn != NULL) {
		player->position = playerSpawn->position;
		player->prevPos = playerSpawn->position;
	}
	sc->addChild(player);
}