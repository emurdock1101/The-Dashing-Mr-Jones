#ifndef DEVTOOL_H
#define DEVTOOL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../engine/DisplayObjectContainer.h"
#include "../engine/Game.h"
#include "../engine/Camera.h"
#include "../engine/Scene.h"
#include "../engine/Sprite.h"
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

	bool isHoveredSelectBar(DisplayObject *obj, SDL_Event event);
	bool isHoveredScene(DisplayObject *obj, SDL_Event event);
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
