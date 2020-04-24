#include "RopeSegment.h"
#include "Rope.h"

RopeSegment::RopeSegment(string id, string imgPath, int segmentNum) : DisplayObjectContainer(id, imgPath) {
	showHitbox = true;
	this->segmentNum = segmentNum;
	this->type = "rope_seg";
}

void RopeSegment::onCollision(DisplayObject* other, SDL_Point delta) {
	if (other->type.compare("cb") == 0 || other->id == "0") {
		if (ropeParent != NULL) {
			ropeParent->queueCut(segmentNum);
		}
	}
}