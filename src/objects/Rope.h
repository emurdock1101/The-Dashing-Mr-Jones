#pragma once
#include "../engine/DisplayObjectContainer.h"
#include "RopeSegment.h"

// Rope is composed of RopeSegments starting at the top (0) and reaching down to index length-1.
class Rope :
	public DisplayObjectContainer
{
public:
	Rope(int length);
	Rope(string id, int length);
	Rope(string id, string imgPath, int length);
	void onCollision(DisplayObject* other, SDL_Point delta);

	void cutRope(int point); // removes the object at point and all lower ones
	vector<RopeSegment*> segments;
private:
	void createSegments(string imgPath, int length);
};

