#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "../engine/Sprite.h"
#include "../engine/ControllerState.h"
#include "MyGame.h"
#include "../engine/Scene.h"
#include "../engine/Camera.h"
#include "../engine/Sound.h"

using namespace std;
bool idle = false;
bool paused = false;

MyGame::MyGame() : Game(1200, 600) {
	instance = this;

	character = new AnimatedSprite("test", "./resources/spritesheets/sayu.png", "./resources/spritesheets/sayu.xml");
	character->position = {400, 400};
	character->width = 200;
	character->height = 200;
	//character2->addAnimationFromSpriteSheet("./resources/spritesheets/test.png", "Run", 20, 2, true);
	character->addAnimationFromSpriteSheet("./resources/spritesheets/sayu.png", "Idle", 10, 2, true);
	character->addAnimationFromSpriteSheet("./resources/spritesheets/sayu.png", "Dead", 10, 2, true);
	character->addAnimationFromSpriteSheet("./resources/spritesheets/sayu.png", "Jump", 10, 2, true);
	character->addAnimationFromSpriteSheet("./resources/spritesheets/sayu.png", "Walk", 10, 2, true);
	character->addAnimationFromSpriteSheet("./resources/spritesheets/sayu.png", "Run", 10, 2, true);
	character->facingRight = true;

	Game::addChild(character);
	character->play("Idle");
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
					case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
						character->play("Idle");
						break;
					case SDL_CONTROLLER_BUTTON_START:
						if (paused == false){
							character->stop();
							paused = true;
						}
						else{
							character->replay();
							paused=false;
						}
				}
			}
		}
	}
	Game::update(pressedKeys, controllerStates);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}
