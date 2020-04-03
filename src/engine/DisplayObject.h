#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <set>
#include "AffineTransform.h"
#include "EventDispatcher.h"
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
	int width = 100;
	int height = 100;
	SDL_Point pivot = {0, 0};
	double scaleX = 1.0;
	double scaleY = 1.0;
	double rotation = 0.0; // in radians
	double alpha = 255;
	bool facingRight = true;
	
	void setPos(int x, int y);
	void setDim(int x, int y);
	void setPiv(int x, int y);

	bool isColliding(Camera *camera, int x, int y);

	virtual void writeSceneData(ostream &stream);

	// Top left conter - use width/height for others
	SDL_Point getTopLeft();
	SDL_Point getTopRight();
	SDL_Point getBottomLeft();
	SDL_Point getBottomRight();
	int getAbsoluteWidth();
	int getAbsoluteHeight();
	void applyParentTransformationsThenSelf(AffineTransform &at);

private:
	double distance(SDL_Point &p1, SDL_Point &p2);
	double calculateRotation(SDL_Point &origin, SDL_Point &p);
	SDL_Point translatePoint(int x, int y);
	float area(int x1, int y1, int x2, int y2, int x3, int y3);

	SDL_Texture* texture = NULL;
	SDL_Surface* image = NULL;

	/* Texture currently being drawn. Equal to texture for normal DO */
	SDL_Texture* curTexture;
};

#endif
