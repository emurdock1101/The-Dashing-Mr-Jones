#ifndef DEVTOOL_H
#define DEVTOOL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "Game.h"
#include "Scene.h"
#include "Sprite.h"
#include <vector>
#include <set>

using namespace std;

class DevTool : public Game {

public:
	DevTool();
	virtual ~DevTool();
	virtual void start();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

private:
	Scene *scene;
	Sprite *selected;
	bool dragging = false;
};

#endif
