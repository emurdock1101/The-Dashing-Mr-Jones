#include "CollisionBlock.h"
CollisionBlock::CollisionBlock() : DisplayObjectContainer("0", 0, 0, 0) {
	type = "cb";
	visible = true;
}

void CollisionBlock::draw(AffineTransform &at) {
	

	if (DisplayObject::showHitbox) {
		DisplayObject::displayHitbox();
	}

	if (visible) {
		DisplayObject::applyTransformations(at);

		SDL_Point origin = at.transformPoint(0, 0);
		SDL_Point upperRight = at.transformPoint(width, 0);
		SDL_Point lowerRight = at.transformPoint(width, height);
		SDL_Point lowerLeft = at.transformPoint(0, height);

		origin.x += 1;
		origin.y += 1;
		upperRight.x -= 1;
		upperRight.y += 1; 
		lowerRight.x -= 1;
		lowerRight.y -= 1;
		lowerLeft.x += 1;
		lowerLeft.y -= 1;

		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 0, 255);
		SDL_Point points[] = { origin, upperRight, lowerRight, lowerLeft, origin };
		SDL_RenderDrawLines(Game::renderer, points, 5);
		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);


		DisplayObject::reverseTransformations(at);
	}
}