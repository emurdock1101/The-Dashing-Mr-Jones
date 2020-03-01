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

MyGame::MyGame() : Game(1200, 600) {
	instance = this;

	character = new AnimatedSprite("character");
	character->position = {0, 0};
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
}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){
	for (ControllerState *controllerState: controllerStates) {
		// Saying controller id 0 == player 1
		if (controllerState->id == 0) {
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
	Game::update(pressedKeys, controllerStates);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}
