#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

	character = new AnimatedSprite("character");
	//character = new AnimatedSprite("character", spritesheet, xml);
	character->position = {100, 100};
	character->width = 200;
	character->height = 200;
	character->addAnimation("./resources/character/", "Idle", 16, 2, true);
	character->addAnimation("./resources/character/", "Dead", 30, 2, true);
	character->addAnimation("./resources/character/", "Jump", 30, 2, true);
	character->addAnimation("./resources/character/", "Run", 20, 2, true);
	character->addAnimation("./resources/character/", "Walk", 20, 2, true);
	character->pivot = {character->width/2, character->height/2};
	Game::addChild(character);
	character->play("Idle");

	character2 = new AnimatedSprite("test", "./resources/spritesheets/idle_run.png", "./resources/spritesheets/idle_run.xml");
	character2->position = {400, 400};
	character2->width = 200;
	character2->height = 200;
	character2->addAnimationFromSpriteSheet("./resources/spritesheets/idle_run.png", "Run", 20, 2, true);
	character2->addAnimationFromSpriteSheet("./resources/spritesheets/idle_run.png", "Idle", 16, 2, true);
	character2->facingRight = true;
	
	Game::addChild(character2);
	character2->play("Idle"); 
}

MyGame::~MyGame(){
	
}


void MyGame::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){
	for (int i=0; i < controllerStates.size(); i++) {
		ControllerState *controllerState = controllerStates.at(i);
		if (i == 0) {
			if (controllerState->joyLeftX == JoystickState::POSITIVE) {
				character->position.x += 6;
			}
			else if (controllerState->joyLeftX == JoystickState::NEGATIVE) {
				character->position.x -= 6;
			}
			if (controllerState->joyLeftY == JoystickState::POSITIVE) {
				character->position.y += 6;
			}
			else if (controllerState->joyLeftY == JoystickState::NEGATIVE) {
				character->position.y -= 6;
			}

			for (uint8_t button: controllerState->pressedButtons) {
				switch(button) {
					case SDL_CONTROLLER_BUTTON_A:
						character->play("Dead");
						break;
					case SDL_CONTROLLER_BUTTON_B:
						character->play("Jump");
						break;
					case SDL_CONTROLLER_BUTTON_X:
						character->play("Run");
						break;
					case SDL_CONTROLLER_BUTTON_Y:
						character->play("Walk");
						break;
					case SDL_CONTROLLER_BUTTON_START:
						character->play("Idle");
						break;
				}
			}
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		character2->position.x += 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		character2->position.x -= 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		character2->position.y += 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		character2->position.y -= 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()){
		if (idle == true){
			character2->play("Idle");
			idle = false;
		}
		else{
			character2->play("Run");
			idle = true;
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_O) != pressedKeys.end()){
		if (paused == false){
			character2->stop();
			paused = true;
		}
		else{
			character2->replay();
			paused=false;
		}
	}
	Game::update(pressedKeys, controllerStates);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}
