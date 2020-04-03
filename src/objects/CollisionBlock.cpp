#include "CollisionBlock.h"
CollisionBlock::CollisionBlock() : DisplayObjectContainer() {
	this->id = "0";
}

void CollisionBlock::draw(AffineTransform &at) {
	DisplayObject::applyTransformations(at);

	if (DisplayObject::showHitbox) {
		DisplayObject::displayHitbox();
	}

	SDL_Point origin = at.transformPoint(0, 0);
	SDL_Point upperRight = at.transformPoint(width, 0);
	SDL_Point lowerRight = at.transformPoint(width, height);
	SDL_Point lowerLeft = at.transformPoint(0, height);

	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 0, 255);
	SDL_Point points[] = { origin, upperRight, lowerRight, lowerLeft, origin };
	SDL_RenderDrawLines(Game::renderer, points, 5);
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);


	DisplayObject::reverseTransformations(at);
}