#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "ControllerState.h"
#include <vector>
#include <map>
#include <set>

using namespace std;

class Game : public DisplayObjectContainer {

public:

	/* Singleton pattern */
	static Game* instance;

	int frames_per_sec = 60;
	int windowWidth, windowHeight;

	SDL_Window * window;
	static SDL_Renderer* renderer;

	//Global frame counter
	static unsigned int frameCounter;

	Game(int windowWidth, int windowHeight);
	virtual ~Game();
	void start();

	virtual void update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates);
	virtual void draw(AffineTransform &at);
	set<SDL_Scancode> pressedKeys;

	// Controller stuff
	const int JOYSTICK_DEAD_ZONE = 8000;
	vector<SDL_GameController *> controllers;
	vector<ControllerState *> controllerStates;
	bool addController(int controllerId);
	bool removeController(int controllerId);
	SDL_GameController* findController(int controllerId);
	ControllerState* findControllerState(int controllerId);
	bool isControllerRelatedToId(SDL_GameController *controller, int controllerId);

private:

	void initSDL();
	void quitSDL();
};

#endif
