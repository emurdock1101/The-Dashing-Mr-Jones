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
};

