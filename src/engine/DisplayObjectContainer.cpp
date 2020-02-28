#include "DisplayObjectContainer.h"
#include "AffineTransform.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;


DisplayObjectContainer::DisplayObjectContainer() : DisplayObject() {
    this->type = "DisplayObjectContainer";
}

DisplayObjectContainer::DisplayObjectContainer(string id, string filepath) : DisplayObject(id, filepath) {
    this->type = "DisplayObjectContainer";
}

DisplayObjectContainer::DisplayObjectContainer(string id, int red, int green, int blue) : DisplayObject(id, red, green, blue) {
    this->type = "DisplayObjectContainer";
}

DisplayObjectContainer::~DisplayObjectContainer() {
    for (int i = 0; i < children.size(); i++ ) {
        delete children[i];
    }
}

void DisplayObjectContainer::addChild(DisplayObjectContainer* child) {
    children.push_back(child);
    child->parent = this; // make sure to include reverse reference also
}

void DisplayObjectContainer::removeImmediateChild(DisplayObjectContainer* child) {
    for (int i = 0; i < children.size(); i++) {
        if (children[i] == child) {
            children.erase(children.begin() + i);
        }
    }
}

void DisplayObjectContainer::removeImmediateChild(string id) {
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->id == id) {
            children.erase(children.begin() + i);
        }
    }
}

void DisplayObjectContainer::removeChild(int index) {
    if (index < children.size()) {
        children.erase(children.begin() + index);
    }
}

void DisplayObjectContainer::removeThis() {
    if (this->parent != NULL) {
        ((DisplayObjectContainer*)this->parent)->removeImmediateChild(this);
    }
}

int DisplayObjectContainer::numChildren() {
    return this->children.size();
}

DisplayObject* DisplayObjectContainer::getChild(int index) {
    if (index < 0 || index > numChildren()) {
        return NULL;
    }
    else return children[index];
}

DisplayObject* DisplayObjectContainer::getChild(string id) {
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->id == id) {
            return children[i];
        }
        // check recursively?
    }
    return NULL;
}

DisplayObjectContainer* DisplayObjectContainer::copy() {
	DisplayObjectContainer *tmp;
	return tmp;
}

void DisplayObjectContainer::update(set<SDL_Scancode> pressedKeys) {
    DisplayObject::update(pressedKeys);
    for (int i = 0; i < children.size(); i++) {
        children[i]->update(pressedKeys);
    }
}

void DisplayObjectContainer::draw(AffineTransform &at) {
    DisplayObject::draw(at);
    applyTransformations(at);
    // undo the parent's pivot
    at.translate(pivot.x, pivot.y);
    for (int i = 0; i < children.size(); i++) {
        children[i]->draw(at);
    }
    // redo the parent's pivot
    at.translate(-pivot.x, -pivot.y);
    reverseTransformations(at);
}

void DisplayObjectContainer::writeSceneData(ostream &stream) {
	DisplayObject::writeSceneData(stream);
	for (DisplayObject *child : children) {
		child->writeSceneData(stream);
	}
}
