#pragma once
#include "../engine/DisplayObjectContainer.h"
#include "../engine/Scene.h"

class RoomChangeBlock :
	public DisplayObjectContainer
{
public:
	RoomChangeBlock(string sceneFile);
	string sceneFile;
	void onCollision(DisplayObject * other, SDL_Point delta);
};

