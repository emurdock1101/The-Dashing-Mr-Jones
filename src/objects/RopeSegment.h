#pragma once
#include "../engine/DisplayObjectContainer.h"
class Rope;

class RopeSegment : public DisplayObjectContainer
{
public:
	RopeSegment(string id, string imgPath, int segmentNum);

	Rope* ropeParent;
	int segmentNum;

	void onCollision(DisplayObject* other, SDL_Point delta);
};