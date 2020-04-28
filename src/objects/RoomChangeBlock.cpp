#include "RoomChangeBlock.h"

#include "../main/MyGame.h"
#include "../engine/events/EventParams.h"
RoomChangeBlock::RoomChangeBlock(string sceneFile) : DisplayObjectContainer("room_change", 0,0,0) {
	this->width = 100;
	this->height = 100;
	this->sceneFile = sceneFile;
	this->visible = false;
}

void RoomChangeBlock::onCollision(DisplayObject* other, SDL_Point delta) {
	if (other->type == "player") {
		Event newEvent(EventParams::ROOM_CHANGED, this);
		((MyGame*)Game::instance)->handleEvent(&newEvent);
	}
}