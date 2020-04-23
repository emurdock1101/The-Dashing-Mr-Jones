#pragma once
#include <SDL2/SDL.h>
#include "../engine/Game.h"
#include "../engine/DisplayObjectContainer.h"
class CollisionBlock :
	public DisplayObjectContainer
{
public:
	CollisionBlock();

	void draw(AffineTransform &at);
	// DisplayObject::visible gets set in the constructor, you can change it there
};

