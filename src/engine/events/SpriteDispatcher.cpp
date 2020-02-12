#include "SpriteDispatcher.h"


SpriteDispatcher::SpriteDispatcher() : Sprite(), EventDispatcher() {
    this->type = "SpriteDispatcher";
}

SpriteDispatcher::SpriteDispatcher(string id, string filepath) : Sprite(id, filepath), EventDispatcher() {
    this->type = "SpriteDispatcher";
}

SpriteDispatcher::SpriteDispatcher(string id, int red, int green, int blue) : Sprite(id, red, green, blue), EventDispatcher() {
    this->type = "SpriteDispatcher";
}

void SpriteDispatcher::update(set<SDL_Scancode> pressedKeys) {
    Sprite::update(pressedKeys);
}

void SpriteDispatcher::draw(AffineTransform &at) {
    Sprite::draw(at);
}
