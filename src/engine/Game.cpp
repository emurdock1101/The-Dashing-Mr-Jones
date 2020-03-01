#include <iostream>
#include "Game.h"
#include <string>
#include <ctime>
#include "DisplayObject.h"
#include "ControllerState.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_gamecontroller.h>
#include <iostream>

using namespace std;

SDL_Renderer* Game::renderer;
Game* Game::instance;
unsigned int Game::frameCounter = 0;

Game::Game(int windowWidth, int windowHeight){
	Game::instance = this;
	
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	initSDL();
	TTF_Init();
}

Game::~Game(){
	quitSDL();
}

void Game::quitSDL(){
	cout << "Quitting sdl" << endl;
	SDL_DestroyRenderer(Game::renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();
}

void Game::initSDL(){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER);
	IMG_Init(IMG_INIT_PNG);
	SDL_JoystickEventState(SDL_ENABLE);
	if (SDL_GameControllerAddMappingsFromFile("./resources/gamecontrollerdb.txt") == -1) {
		std::cout << "COULD NOT LOAD MAPPINGS" << std::endl;
	}

	window = SDL_CreateWindow("myGame",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->windowWidth, this->windowHeight, 0);

	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );

	// Open all controllers and add to vector
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		addController(i);
	}

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	Game::renderer = renderer;

}

void Game::start(){

	int ms_per_frame = (1.0/(double)this->frames_per_sec)*1000;
	std::clock_t start = std::clock();

	bool quit = false;
	SDL_Event event;
	ControllerState *controllerState;
	JoystickState joyState;

	while(!quit){
		std::clock_t end = std::clock();
		double duration = (( end - start ) / (double) CLOCKS_PER_SEC)*1000;
		if(duration > ms_per_frame){
			start = end;
			this->update(pressedKeys, controllerStates);
			AffineTransform at;
			this->draw(at);
		}

		SDL_PollEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				pressedKeys.insert(event.key.keysym.scancode);
				break;
			case SDL_KEYUP:
				pressedKeys.erase(event.key.keysym.scancode);
				break;
			// Controller events
			// Adding/removing controllers
			case SDL_CONTROLLERDEVICEADDED:
				addController(event.cdevice.which);
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				removeController(event.cdevice.which);
				break;
			case SDL_CONTROLLERDEVICEREMAPPED:
				// Nothing - done by itself
				break;
			case SDL_CONTROLLERBUTTONDOWN:
				// type, timestamp, which, button, state
				controllerState = findControllerState(event.cbutton.which);
				if (controllerState != NULL) {
					controllerState->pressedButtons.insert(event.cbutton.button);
				}
				break;
			case SDL_CONTROLLERBUTTONUP:
				controllerState = findControllerState(event.cbutton.which);
				if (controllerState != NULL) {
					controllerState->pressedButtons.erase(event.cbutton.button);
				}
				break;
			case SDL_CONTROLLERAXISMOTION:
				controllerState = findControllerState(event.jaxis.which);
				if (controllerState != NULL) {
					if(event.jaxis.value < -JOYSTICK_DEAD_ZONE) {
						joyState = JoystickState::NEGATIVE;
						std::cout << "NEGATIVE" << std::endl;
					}
					else if(event.jaxis.value > JOYSTICK_DEAD_ZONE) {
						joyState = JoystickState::POSITIVE;
						std::cout << "POSITIVE" << std::endl;
					}
					else {
						joyState = JoystickState::NEUTRAL;
						std::cout << "NEUTRAL" << std::endl;
					}

					if(event.jaxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
						std::cout << "LEFT X" << std::endl;
						controllerState->joyLeftX = joyState;
					}
					else if(event.jaxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
						std::cout << "LEFT Y" << std::endl;
						controllerState->joyLeftY = joyState;
					}
					if(event.jaxis.axis == SDL_CONTROLLER_AXIS_RIGHTX) {
						std::cout << "RIGHT X" << std::endl;
						controllerState->joyRightX = joyState;
					}
					if(event.jaxis.axis == SDL_CONTROLLER_AXIS_RIGHTY) {
						std::cout << "RIGHT Y" << std::endl;
						controllerState->joyRightY = joyState;
					}
				}
				break;
		}
	}
}

void Game::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){
	frameCounter++;
	DisplayObjectContainer::update(pressedKeys, controllerStates);
}

void Game::draw(AffineTransform &at){
	SDL_RenderClear(Game::renderer);
	DisplayObjectContainer::draw(at);
	SDL_RenderPresent(Game::renderer);
}

bool Game::addController(int controllerId) {
	if (SDL_IsGameController(controllerId)) {
		SDL_GameController *controller =
			SDL_GameControllerOpen(controllerId);
		if (controller) {
			std::cout << "Added controller " << controller << std::endl;
			controllers.push_back(controller);
			controllerStates.push_back(new ControllerState);
			controllerStates.back()->id = controllerId;
			controllerStates.back()->joyLeftX = JoystickState::NEUTRAL;
			controllerStates.back()->joyLeftY = JoystickState::NEUTRAL;
			controllerStates.back()->joyRightX = JoystickState::NEUTRAL;
			controllerStates.back()->joyRightY = JoystickState::NEUTRAL;
			return true;
		} else {
			fprintf(stderr, "Could not open gamecontroller %i: %s\n", controllerId, SDL_GetError());
			return false;
		}
	}
	return false;
}

bool Game::removeController(int controllerId) {
	if (SDL_IsGameController(controllerId)) {
		SDL_GameController *controller = findController(controllerId);
		if (controller == NULL) {
			return false;
		}
		std::cout << "Removing controller " << controllerId << std::endl;
		SDL_GameControllerClose(controller);
		for (int i = 0; i < controllers.size(); i++) {
			if (isControllerRelatedToId(controller, controllerId)) {
				controllers.erase(controllers.begin() + i);
				controllerStates.erase(controllerStates.begin() + i);
				return true;
			}
		}
	}
	return false;
}

SDL_GameController* Game::findController(int controllerId) {
	for (SDL_GameController *controller: controllers) {
		if (isControllerRelatedToId(controller, controllerId)) {
			return controller;
		}
	}
	return NULL;
}

ControllerState* Game::findControllerState(int controllerId) {
	for (ControllerState *state: controllerStates) {
		if (state->id == controllerId) {
			return state;
		}
	}
	return NULL;
}

bool Game::isControllerRelatedToId(SDL_GameController *controller, int controllerId) {
	return controllerId == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller));
}
