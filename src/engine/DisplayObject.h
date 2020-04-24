#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <set>
#include "AffineTransform.h"
#include "./events/EventDispatcher.h"
#include "Camera.h"
#include "ControllerState.h"
#include <string>
#include <fstream>

using namespace std;

class DisplayObject : public EventDispatcher {

public:
	string id = "DEFAULT_ID";
	string imgPath = "";
	int red, green, blue;
	string type = "DisplayObject";

	DisplayObject* parent = NULL;

	bool isRGB = false;

	DisplayObject();
	DisplayObject(string id, string path);
	DisplayObject(string id, int red, int green, int blue);
	virtual ~DisplayObject();

	virtual void update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates);
	virtual void draw(AffineTransform &at);

	void loadTexture(string filepath);
	void loadRGBTexture(int red, int green, int blue);
	void setTexture(SDL_Texture* t);

	void applyTransformations(AffineTransform &at);
	void reverseTransformations(AffineTransform &at);

	int getWidth();
	int getHeight();

	bool visible = true;
	SDL_Point position = {0, 0};
	SDL_Point prevPos = {0,0};
	int width = 100;
	int height = 100;
	SDL_Point pivot = {0, 0};
	double scaleX = 1.0;
	double scaleY = 1.0;
	double rotation = 0.0; // in radians
	int alpha = 255;
	bool facingRight = true;
	bool showHitbox = false;
	bool inDevtool = false;
	bool invalidateCache = false;


	// Hitbox offsets are the amount to cut off the edge of the image
	// eg hitboxRightOffset of 50 will make the hitbox 50 pixels skinnier
	// from the right side. Negative will make hitbox larger than image.
	// Undefined behavior if offsets sum larger than width or height.
	int hitboxRightOffset = 0;
	int hitboxLeftOffset = 0;
	int hitboxUpOffset = 0;
	int hitboxDownOffset = 0;
	
	void setPos(int x, int y);
	void setDim(int x, int y);
	void setPiv(int x, int y);

	bool isColliding(Camera *camera, int x, int y);
	bool isCollidingHitbox(Camera *camera, int x, int y);


	virtual void writeSceneData(ostream &stream);

	SDL_Point getTopLeft();
	SDL_Point getTopRight();
	SDL_Point getBottomLeft();
	SDL_Point getBottomRight();

	// Same for absolute positions, but with hitbox offsets off
	SDL_Point getTopLeftHitbox();
	SDL_Point getTopRightHitbox();
	SDL_Point getBottomLeftHitbox();
	SDL_Point getBottomRightHitbox();

	int getAbsoluteWidth();
	int getAbsoluteHeight();
	void displayHitbox();
	void applyParentTransformationsThenSelf(AffineTransform &at);

	AffineTransform *cachedTransform;
	int cacheFrame = 0;
	SDL_Point cachePosition;
	int cacheRotation;
	double cacheScaleX;
	double cacheScaleY;
	bool isCacheValid();
	const AffineTransform *getGlobalTransform();

	/* Called by the CollisionSystem whenever a collision occurs. 
	   Don't destroy objects in this method! CollisionSystem will keep iterating through them, so wait until the next update cycle. 
	   */
	virtual void onCollision(DisplayObject *other, SDL_Point delta); 

	
protected:
	double distance(SDL_Point &p1, SDL_Point &p2);
private:
	
	double calculateRotation(SDL_Point &origin, SDL_Point &p);
	SDL_Point translatePoint(int x, int y);
	float area(int x1, int y1, int x2, int y2, int x3, int y3);

	SDL_Texture* texture = NULL;
	SDL_Surface* image = NULL;

	/* Texture currently being drawn. Equal to texture for normal DO */
	SDL_Texture* curTexture;
};

#endif
