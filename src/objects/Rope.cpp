#include "Rope.h"

Rope::Rope(int length) : DisplayObjectContainer("rope", 0, 0, 0) {
	type = "rope";
	visible = false;
	width = 100;
	height = 100;
	this->length = length;
	createSegments("./resources/objects/rope.png", length);
}
Rope::Rope(string id, int length) : DisplayObjectContainer(id, 0, 0, 0) {
	type = "rope";
	visible = false;
	width = 100;
	height = 100 * length;
	this->length = length;
	createSegments("./resources/objects/rope.png", length);
}

Rope::Rope(string id, string imgPath, int length) : DisplayObjectContainer(id, 0, 0, 0) {
	type = "rope";
	visible = false;
	width = 100;
	height = 100 * length;
	this->length = length;
	createSegments(imgPath, length);
}

void Rope::createSegments(string imgPath, int length) {
	for (int i = 0; i < length; i++) {
		segments.push_back(new RopeSegment(id+"_seg", imgPath, i));
		segments[i]->position = { 0, 100 * i };
		segments[i]->ropeParent = this;
		DisplayObjectContainer::addChild(segments[i]);
	}
}

void Rope::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates) {
	cutRope(length);
}

void Rope::queueCut(int point) {
	length = point;
}

void Rope::cutRope(int point) {
	// remove all object from the back until the object with point as its index
	for (int i = segments.size() - 1; i >= point; i--) {
		DisplayObjectContainer::removeImmediateChild(segments[i]);
		delete segments[i];
		segments.erase(segments.begin() + i);
	}
}

void Rope::onCollision(DisplayObject* other, SDL_Point delta) {
	DisplayObject::onCollision(other, delta);
}