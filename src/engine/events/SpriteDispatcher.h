#ifndef SPRITEDISPATCHER_H
#define SPRITEDISPATCHER_H

#include "Sprite.h"
#include "EventDispatcher.h"

using namespace std;

class SpriteDispatcher : public Sprite, public EventDispatcher {

public:

	SpriteDispatcher();
	SpriteDispatcher(string id, string filepath);
	SpriteDispatcher(string id, int red, int green, int blue);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

private:
};

#endif
