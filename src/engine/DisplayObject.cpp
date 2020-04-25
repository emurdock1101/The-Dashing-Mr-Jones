#include "DisplayObject.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include "Camera.h"
#include <algorithm>
#include <cmath>

#define PI 3.14159265

DisplayObject::DisplayObject(){
	image = NULL;
	texture = NULL;
	curTexture = NULL;

	cachedTransform = new AffineTransform();
}

DisplayObject::DisplayObject(string id, string filepath){
	this->id = id;
	this->imgPath = filepath;

	loadTexture(filepath);

	cachedTransform = new AffineTransform();
}

DisplayObject::DisplayObject(string id, int red, int green, int blue){
	isRGB = true;
	this->id = id;

	this->red = red;
	this->blue = blue;
	this->green = green;

	this->loadRGBTexture(red, green, blue);

	cachedTransform = new AffineTransform();
}

DisplayObject::~DisplayObject(){
	//TODO: Get this freeing working
	if(image != NULL) SDL_FreeSurface(image);
	if(texture != NULL && Game::renderer != NULL) SDL_DestroyTexture(texture);

	delete cachedTransform;
}

void DisplayObject::loadTexture(string filepath){
	image = IMG_Load(filepath.c_str());
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	setTexture(texture);
}

void DisplayObject::loadRGBTexture(int red, int green, int blue){
	image = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0x000000ff);
	SDL_FillRect(image, NULL, SDL_MapRGB(image->format, red, green, blue));
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
	setTexture(texture);
}

void DisplayObject::setTexture(SDL_Texture* t){
	this->curTexture = t;
}

void DisplayObject::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){

}

void DisplayObject::draw(AffineTransform &at){
	applyTransformations(at);
	if (showHitbox) {
		displayHitbox();
	}

	if(curTexture != NULL && visible) {
		SDL_Point origin = at.transformPoint(0, 0);
		SDL_Point upperRight = at.transformPoint(width, 0);
		SDL_Point lowerRight = at.transformPoint(width, height);
		SDL_Point corner = {0, 0};

		int w = (int)distance(origin, upperRight);
		
		int h = (int)distance(upperRight, lowerRight);

		SDL_Rect dstrect = { origin.x, origin.y, w, h };

		SDL_RendererFlip flip;
		if (facingRight) {
			flip = SDL_FLIP_NONE;
		}
		else {
			flip = SDL_FLIP_HORIZONTAL;
		}

		SDL_SetTextureAlphaMod(curTexture, alpha);
		SDL_RenderCopyEx(Game::renderer, curTexture, NULL, &dstrect, calculateRotation(origin, upperRight), &corner, flip);
	}

	reverseTransformations(at);
}

void DisplayObject::applyTransformations(AffineTransform &at) {
	at.translate(position.x, position.y);
	at.rotate(rotation);
	at.scale(scaleX, scaleY);
	at.translate(-pivot.x, -pivot.y);
}

void DisplayObject::reverseTransformations(AffineTransform &at) {
	at.translate(pivot.x, pivot.y);
	at.scale(1.0/scaleX, 1.0/scaleY);
	at.rotate(-rotation);
	at.translate(-position.x, -position.y);
}

bool DisplayObject::isColliding(Camera *camera, int x, int y) {
	int globalX = 0;
	int globalY = 0;
	DisplayObject *currentParent = parent;
	while (currentParent != NULL) {
		globalX += currentParent->position.x;
		globalY += currentParent->position.y;
		currentParent = currentParent->parent;
	}
	SDL_Point topLeft = getTopLeft();
	SDL_Point topRight = getTopRight();
	SDL_Point bottomLeft = getBottomLeft();
	SDL_Point bottomRight = getBottomRight();

	// Add the camera
	if (camera != NULL) {
		topLeft.x -= camera->x;
		topLeft.y -= camera->y;
		topRight.x -= camera->x;
		topRight.y -= camera->y;
		bottomLeft.x -= camera->x;
		bottomLeft.y -= camera->y;
		bottomRight.x -= camera->x;
		bottomRight.y -= camera->y;
	}

	/* Now calculate if point is in this rectangle or not.
	 * To deal with rotation etc. this uses the area method.
	 * Namely, the area of the 4 triangles that could be made with
	 * the point should add up to the area of the rectangle if it's
	 * within it. This is necessary because the rectangle
	 * could be rotated.
	 */

	double A = area(topLeft.x, topLeft.y, topRight.x, topRight.y,
					bottomRight.x, bottomRight.y) +
              area(topLeft.x, topLeft.y, bottomLeft.x, bottomLeft.y,
					  bottomRight.x, bottomRight.y);

    /* Calculate area of triangle PAB */
    double A1 = area(x, y, topLeft.x, topLeft.y, topRight.x, topRight.y);

    /* Calculate area of triangle PBC */
    double A2 = area(x, y, topRight.x, topRight.y, bottomRight.x, bottomRight.y);

    /* Calculate area of triangle PCD */
    double A3 = area(x, y, bottomRight.x, bottomRight.y, bottomLeft.x, bottomLeft.y);

    /* Calculate area of triangle PAD */
    double A4 = area(x, y, topLeft.x, topLeft.y, bottomLeft.x, bottomLeft.y);

	// Do float comparison just in case
	return (abs(A - (A1 + A2 + A3 + A4)) < 0.000005);
}

bool DisplayObject::isCollidingHitbox(Camera *camera, int x, int y) {
	int globalX = 0;
	int globalY = 0;
	DisplayObject *currentParent = parent;
	while (currentParent != NULL) {
		globalX += currentParent->position.x;
		globalY += currentParent->position.y;
		currentParent = currentParent->parent;
	}
	SDL_Point topLeft = getTopLeftHitbox();
	SDL_Point topRight = getTopRightHitbox();
	SDL_Point bottomLeft = getBottomLeftHitbox();
	SDL_Point bottomRight = getBottomRightHitbox();

	// Add the camera
	if (camera != NULL) {
		topLeft.x += camera->x;
		topLeft.y += camera->y;
		topRight.x += camera->x;
		topRight.y += camera->y;
		bottomLeft.x += camera->x;
		bottomLeft.y += camera->y;
		bottomRight.x += camera->x;
		bottomRight.y += camera->y;
	}

	/* Now calculate if point is in this rectangle or not.
	 * To deal with rotation etc. this uses the area method.
	 * Namely, the area of the 4 triangles that could be made with
	 * the point should add up to the area of the rectangle if it's
	 * within it. This is necessary because the rectangle
	 * could be rotated.
	 */

	double A = area(topLeft.x, topLeft.y, topRight.x, topRight.y,
					bottomRight.x, bottomRight.y) +
              area(topLeft.x, topLeft.y, bottomLeft.x, bottomLeft.y,
					  bottomRight.x, bottomRight.y);

    /* Calculate area of triangle PAB */
    double A1 = area(x, y, topLeft.x, topLeft.y, topRight.x, topRight.y);

    /* Calculate area of triangle PBC */
    double A2 = area(x, y, topRight.x, topRight.y, bottomRight.x, bottomRight.y);

    /* Calculate area of triangle PCD */
    double A3 = area(x, y, bottomRight.x, bottomRight.y, bottomLeft.x, bottomLeft.y);

    /* Calculate area of triangle PAD */
    double A4 = area(x, y, topLeft.x, topLeft.y, bottomLeft.x, bottomLeft.y);

	// Do float comparison just in case
	return (abs(A - (A1 + A2 + A3 + A4)) < 0.000005);
}


int DisplayObject::getWidth() {
	return this->image->w;
}

int DisplayObject::getHeight() {
	return this->image->h;
}

double DisplayObject::distance(SDL_Point &p1, SDL_Point &p2) {
	return sqrt(((p2.y - p1.y)*(p2.y - p1.y)) + ((p2.x - p1.x)*(p2.x - p1.x)));
}

double DisplayObject::calculateRotation(SDL_Point &origin, SDL_Point &p) {
	double y = p.y - origin.y;
	double x = p.x - origin.x;
	return (atan2(y, x) * 180 / PI);
}
void DisplayObject::setDim(int a, int b){
	if (this->image != NULL) {
		this->image->w = a;
		this->image->h = b;
	}
	this->width = a;
	this->height = b;
}
void DisplayObject::setPos(int a, int b){
	this->position.x = a;
	this->position.y = b;
	this->prevPos.x = a;
	this->prevPos.y = b;
}
void DisplayObject::setPiv(int a, int b){
	this->pivot.x = a;
	this->pivot.y = b;
}

SDL_Point DisplayObject::getTopLeft() {
	return translatePoint(0, 0);
}

SDL_Point DisplayObject::getTopRight() {
	return translatePoint(width, 0);
}

SDL_Point DisplayObject::getBottomLeft() {
	return translatePoint(0, height);
}

SDL_Point DisplayObject::getBottomRight() {
	return translatePoint(width, height);
}

SDL_Point DisplayObject::getTopLeftHitbox() { 
	return translatePoint(hitboxLeftOffset, hitboxUpOffset);

	// Camera-dependent implementation

	// Camera *camera = Game::instance->cammy;
	// AffineTransform at;
	// at.scale(camera->scaleX, camera->scaleY);
	// at.translate(-camera->x, -camera->y);
	// at.concatenate(*getGlobalTransform());
	// // Only apply this one's pivot
	// at.translate(-pivot.x, -pivot.y);
	// return at.transformPoint(hitboxLeftOffset, hitboxUpOffset);
}

SDL_Point DisplayObject::getTopRightHitbox() {
	return translatePoint(width - hitboxRightOffset, hitboxUpOffset);

	// Camera-depedent:

	// Camera *camera = Game::instance->cammy;
	// AffineTransform at;
	// at.scale(camera->scaleX, camera->scaleY);
	// at.translate(-camera->x, -camera->y);
	// at.concatenate(*getGlobalTransform());
	// // Only apply this one's pivot
	// at.translate(-pivot.x, -pivot.y);
	// return at.transformPoint(width-hitboxRightOffset, hitboxUpOffset);
}

SDL_Point DisplayObject::getBottomLeftHitbox() {
	return translatePoint(hitboxLeftOffset, height - hitboxDownOffset);

	// Camera *camera = Game::instance->cammy;
	// AffineTransform at;
	// at.scale(camera->scaleX, camera->scaleY);
	// at.translate(-camera->x, -camera->y);
	// at.concatenate(*getGlobalTransform());
	// // Only apply this one's pivot
	// at.translate(-pivot.x, -pivot.y);
	// return at.transformPoint(hitboxLeftOffset, height-hitboxDownOffset);
}

SDL_Point DisplayObject::getBottomRightHitbox() {
	return translatePoint(width - hitboxRightOffset, height - hitboxDownOffset);

	// Camera *camera = Game::instance->cammy;
	// AffineTransform at;
	// at.scale(camera->scaleX, camera->scaleY);
	// at.translate(-camera->x, -camera->y);
	// at.concatenate(*getGlobalTransform());
	// // Only apply this one's pivot
	// at.translate(-pivot.x, -pivot.y);
	// return at.transformPoint(width-hitboxRightOffset, height-hitboxDownOffset);
}

int DisplayObject::getAbsoluteWidth() {
	AffineTransform at;
	at.concatenate(*getGlobalTransform());
	SDL_Point origin = at.transformPoint(0, 0);
	SDL_Point upperRight = at.transformPoint(width, 0);
	return (int)distance(origin, upperRight);
}

int DisplayObject::getAbsoluteHeight() {
	AffineTransform at;
	at.concatenate(*getGlobalTransform());
	SDL_Point origin = at.transformPoint(0, 0);
	SDL_Point bottomRight = at.transformPoint(0, height);
	return (int)distance(origin, bottomRight);
}

SDL_Point DisplayObject::translatePoint(int x, int y) {
	AffineTransform at;
	at.concatenate(*getGlobalTransform());
	// Only apply this one's pivot
	at.translate(-pivot.x, -pivot.y);
	return at.transformPoint(x, y);
}

void DisplayObject::applyParentTransformationsThenSelf(AffineTransform &at) {
	if (parent != NULL) {
		parent->applyParentTransformationsThenSelf(at);
	}
	applyTransformations(at);
	// Unapply pivot
	at.translate(pivot.x, pivot.y);

}

bool DisplayObject::isCacheValid() {
	if (cacheFrame != Game::frameCounter) {
		return false;
	}
	if (cachePosition.x != position.x || cachePosition.y != position.y) {
		return false;
	}
	if (cacheRotation != rotation) {
		return false;
	}
	if (cacheScaleX != scaleX || cacheScaleY != scaleY) {
		return false;
	}
	return !invalidateCache;
}

/* 
	Returns the cached global space transform. Don't transform it. 
*/
const AffineTransform *DisplayObject::getGlobalTransform() {
	if (!isCacheValid()) {
		if (cachedTransform != NULL) {
			delete cachedTransform;
		}
		cachedTransform = new AffineTransform();
		cacheFrame = Game::frameCounter;
		cachePosition = position;
		cacheRotation = rotation;
		cacheScaleX = scaleX;
		cacheScaleY = scaleY;
		if (parent != NULL) {
			cachedTransform->concatenate(*(parent->getGlobalTransform()));
		}
		applyTransformations(*cachedTransform);
		// Unapply pivot
		cachedTransform->translate(pivot.x, pivot.y);
		invalidateCache = false;
	}
	return cachedTransform;
}

void DisplayObject::writeSceneData(ostream &stream) {
	stream << type << " ";
	stream << id << " ";
	stream << imgPath << " ";
	stream << position.x << " ";
	stream << position.y << " ";
	stream << pivot.x << " ";
	stream << pivot.y << " ";
	stream << scaleX << " ";
	stream << scaleY << " ";
	stream << rotation << " ";
	stream << height << " ";
	stream << width << " ";
	stream << alpha;
	if (parent != NULL && parent->type != "Scene") {
		stream << " " << parent->id;
	}
	stream << endl;
}

void DisplayObject::displayHitbox() {
	Camera *camera = Game::instance->cammy;
	AffineTransform at;
	if (camera != NULL) {
		at.translate(Game::instance->pivot.x, Game::instance->pivot.y);
		at.scale(camera->scaleX, camera->scaleY);
		at.translate(-camera->x, -camera->y);
	}

    SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_Point topLeftH = getTopLeftHitbox();
	SDL_Point topRightH = getTopRightHitbox();
	SDL_Point bottomLeftH = getBottomLeftHitbox();
	SDL_Point bottomRightH = getBottomRightHitbox();

	SDL_Point topLeft = at.transformPoint(topLeftH.x, topLeftH.y);
	SDL_Point topRight = at.transformPoint(topRightH.x, topRightH.y);
	SDL_Point bottomLeft = at.transformPoint(bottomLeftH.x, bottomLeftH.y);
	SDL_Point bottomRight = at.transformPoint(bottomRightH.x, bottomRightH.y);
	SDL_RenderDrawLine(Game::renderer,
			topLeft.x,
			topLeft.y,
			topRight.x,
			topRight.y);
	SDL_RenderDrawLine(Game::renderer,
			topLeft.x,
			topLeft.y,
			bottomLeft.x,
			bottomLeft.y);
	SDL_RenderDrawLine(Game::renderer,
			topRight.x,
			topRight.y,
			bottomRight.x,
			bottomRight.y);
	SDL_RenderDrawLine(Game::renderer,
			bottomLeft.x,
			bottomLeft.y,
			bottomRight.x,
			bottomRight.y);
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

/* Used for area in area selection detection */
float DisplayObject::area(int x1, int y1, int x2, int y2, int x3, int y3) {
    return abs((x1 * (y2 - y3) + x2 * (y3 - y1) +
                x3 * (y1 - y2)) / 2.0);
}


void DisplayObject::onCollision(DisplayObject *other, SDL_Point delta) {

}
