#include "CollisionSystem.h"
#include "DisplayObject.h"
#include "EventParams.h"
#include "Game.h"
#include <iostream>
#include <map>

using namespace std;

CollisionSystem::CollisionSystem() {
	Game::instance->addEventListener(this, EventParams::DISPLAY_OBJECT_ADDED);
}

CollisionSystem::~CollisionSystem() {
}

//checks collisions between pairs of DOs where the corresponding types have been requested
//to be checked (via a single call to watchForCollisions) below.
void CollisionSystem::update() {
	for (auto it = watchedIds.begin(); it != watchedIds.end(); it++) {
		// Get vector for first object in pair, or continue if none added
		auto object1It = knownIds.find(it->first);
		if (object1It == knownIds.end()) {
			// Continue if one of the ids has no known objects
			continue;
		}
		vector<DisplayObject *> *object1Vec = object1It->second;
		// Same for second
		auto object2It = knownIds.find(it->second);
		if (object2It == knownIds.end()) {
			// Continue if one of the ids has no known objects
			continue;
		}
		vector<DisplayObject *> *object2Vec = object2It->second;

		for (DisplayObject *object1 : *object1Vec) {
			for (DisplayObject *object2 : *object2Vec) {
				if (collidesWith(object1, object2)) {
					// TODO: Enter correct values
					//cout << "Collision Detected" << endl;
					double xDelta1 = object1->position.x - object1->prevPos.x;
					double xDelta2 = object2->position.x - object2->prevPos.x;
					double yDelta1 = object1->position.y - object1->prevPos.y;
					double yDelta2 = object2->position.y - object2->prevPos.y;
					resolveCollision(object1, object2, xDelta1, yDelta1, xDelta2, yDelta2);
				}
			}
		}

	}
}

//This system watches the game's display tree and is notified whenever a display object is placed onto
//or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
void CollisionSystem::handleEvent(Event* e) {
	string objectId = ((DisplayObject *)e->getSource())->id;
	auto it = knownIds.find(objectId);
	if (it == knownIds.end()) {
		knownIds.insert(pair<string, vector<DisplayObject *> *>(
					objectId, new vector<DisplayObject *>()));
		it = knownIds.find(objectId);
	}
	// Add event's object to the vector
	it->second->push_back((DisplayObject *)e->getSource());
}

//This function asks the collision system to start checking for collisions between all pairs
//of DOs of a given type (e.g., player vs platform). The system will begin to check all player objects
//against all platform objects that are in the current scene.
void CollisionSystem::watchForCollisions(string type1, string type2) {
	pair<string, string> watched = make_pair(type1, type2);
	watchedIds.push_back(watched);
}

//returns true iff obj1 hitbox and obj2 hitbox overlap. Uses the following method from DO:
//	SDL_Point* DisplayObject::getGlobalHitbox();
bool CollisionSystem::collidesWith(DisplayObject* obj1, DisplayObject* obj2) {
	// Get points for obj1
	SDL_Point topLeft1 = obj1->getTopLeftHitbox();
	SDL_Point topRight1 = obj1->getTopRightHitbox();
	SDL_Point bottomLeft1 = obj1->getBottomLeftHitbox();
	SDL_Point bottomRight1 = obj1->getBottomRightHitbox();

	// Get points for obj2
	SDL_Point topLeft2 = obj2->getTopLeftHitbox();
	SDL_Point topRight2 = obj2->getTopRightHitbox();
	SDL_Point bottomLeft2 = obj2->getBottomLeftHitbox();
	SDL_Point bottomRight2 = obj2->getBottomRightHitbox();

	// Test each possible line segment, not looping so here's to big blocks
	// 16 checks incoming!!

	// top left -> top right against obj2
	if (lineSegmentsIntersect(topLeft1, topRight1, topLeft2, topRight2)) {
		return true;
	}
	if (lineSegmentsIntersect(topLeft1, topRight1, topRight2, bottomRight2)) {
		return true;
	}
	if (lineSegmentsIntersect(topLeft1, topRight1, bottomRight2, bottomLeft2)) {
		return true;
	}
	if (lineSegmentsIntersect(topLeft1, topRight1, bottomLeft2, topLeft2)) {
		return true;
	}

	// top right -> bottom right against obj2
	if (lineSegmentsIntersect(topRight1, bottomRight1, topLeft2, topRight2)) {
		return true;
	}
	if (lineSegmentsIntersect(topRight1, bottomRight1, topRight2, bottomRight2)) {
		return true;
	}
	if (lineSegmentsIntersect(topRight1, bottomRight1, bottomRight2, bottomLeft2)) {
		return true;
	}
	if (lineSegmentsIntersect(topRight1, bottomRight1, bottomLeft2, topLeft2)) {
		return true;
	}

	// bottom right -> bottom left against obj2
	if (lineSegmentsIntersect(bottomRight1, bottomLeft1, topLeft2, topRight2)) {
		return true;
	}
	if (lineSegmentsIntersect(bottomRight1, bottomLeft1, topRight2, bottomRight2)) {
		return true;
	}
	if (lineSegmentsIntersect(bottomRight1, bottomLeft1, bottomRight2, bottomLeft2)) {
		return true;
	}
	if (lineSegmentsIntersect(bottomRight1, bottomLeft1, bottomLeft2, topLeft2)) {
		return true;
	}

	// bottom left -> top left against obj2
	if (lineSegmentsIntersect(bottomLeft1, topLeft1, topLeft2, topRight2)) {
		return true;
	}
	if (lineSegmentsIntersect(bottomLeft1, topLeft1, topRight2, bottomRight2)) {
		return true;
	}
	if (lineSegmentsIntersect(bottomLeft1, topLeft1, bottomRight2, bottomLeft2)) {
		return true;
	}
	if (lineSegmentsIntersect(bottomLeft1, topLeft1, bottomLeft2, topLeft2)) {
		return true;
	}

	// Edge case, object completely inside another
	if (obj1->isCollidingHitbox(NULL, topLeft2.x, topLeft2.y)) {
		return true;
	}
	if (obj2->isCollidingHitbox(NULL, topLeft1.x, topLeft1.y)) {
		return true;
	}

	// Else we gucci, no collision
	return false;
}

//Resolves the collision that occurred between d and other
//xDelta1 and yDelta1 are the amount d moved before causing the collision.
//xDelta2 and yDelta2 are the amount other moved before causing the collision.
void CollisionSystem::resolveCollision(DisplayObject* d, DisplayObject* other,
		int xDelta1, int yDelta1, int xDelta2, int yDelta2) {
	
	d->position.x -= xDelta1;
	other->position.x -= xDelta2;
	d->position.y -= yDelta1;
	other->position.y -= yDelta2;
	// TODO: Implement resolve
	// Maybe find deltas through a custom Event with those parameters	

	
}


bool CollisionSystem::lineSegmentsIntersect(SDL_Point a, SDL_Point b, SDL_Point c, SDL_Point d) {
	// Get orientations for each
	int o1 = getOrientation(a, b, c);
	int o2 = getOrientation(a, b, d);
	int o3 = getOrientation(c, d, a);
	int o4 = getOrientation(c, d, b);

	// Orientations not equal, they intersect
	if ((o1 != o2) && (o3 != o4)) {
		return true;
	}

	// Check special case (colinear)
	if (o1 == 0) {
		if ((b.x > c.x && a.x < c.x) || (b.x < c.x && a.x > c.x)) {
			return true;
		}
	}
	if (o2 == 0) {
		if ((b.x > d.x && a.x < d.x) || (b.x < d.x && a.x > d.x)) {
			return true;
		}
	}
	if (o3 == 0) {
		if ((d.x > a.x && c.x < a.x) || (d.x < a.x && c.x > a.x)) {
			return true;
		}
	}
	if (o4 == 0) {
		if ((d.x > b.x && c.x < b.x) || (d.x < b.x && c.x > b.x)) {
			return true;
		}
	}

	// Otherwise they don't collide
	return false;
}

int CollisionSystem::getOrientation(SDL_Point a, SDL_Point b, SDL_Point c) {
	// I have no idea why, but my slope calculation before must've been wrong
	// Got this from here and it worked great, must've been weird bug
	// https://www.geeksforgeeks.org/orientation-3-ordered-points/
	int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);

    if (val == 0) return 0;  // colinear

    return (val > 0)? 1: -1; // clock or counterclock wise
}
