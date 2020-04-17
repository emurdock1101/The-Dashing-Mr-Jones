#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

struct Frame {
	SDL_Surface* image;
	SDL_Texture* texture;
};

struct Animation {
	Frame** frames;
	string basepath;
	string animName;
	int numFrames;
	int frameRate;
	bool loop;
	int curFrame;
};

class AnimatedSprite : public Sprite{

public:
	AnimatedSprite();
	AnimatedSprite(string id);
	AnimatedSprite(string id, string spritesheet, string xml);
	~AnimatedSprite();

	void addAnimation(string basepath, string animName, int numFrames, int frameRate, bool loop);
	void addAnimationFromSpriteSheet(string texture, string animName, int numFrames, int frameRate, bool loop);
	Animation* getAnimation(string animName);
	int getAnimationPosition(string animName);
	void loadSheet(string xml);

	void play(string animName);
	void replay();
	void stop();

	virtual void update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates);
	virtual void draw(AffineTransform &at);
	virtual void writeSceneData(ostream &stream);

	bool playing = false;

//private:
	Animation* current;
	vector<Animation*> animations;
	int frameCount;

	vector<vector<string>> split;
	
};

#endif
