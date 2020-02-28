#ifndef DEVTOOL_H
#define DEVTOOL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "Game.h"
#include "Camera.h"
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
	vector<string> getImagesFromFolder(string folderName);

private:

	bool isHovered(DisplayObject *obj, SDL_Event event);
	void editPrompt();

	int gridPixels = 50;
	Scene *scene;

	DisplayObjectContainer *menus;
	DisplayObjectContainer *selected;
	DisplayObjectContainer *copied;
	Sprite *selectionArea;
	Sprite* blueBar;
	bool dragging = false;
	bool makeChild = false;

	vector<DisplayObjectContainer*> spritesToDisplay;
	vector<DisplayObjectContainer*> onScreen;
	set<SDL_Scancode> singleUseKeys;

};

#endif
