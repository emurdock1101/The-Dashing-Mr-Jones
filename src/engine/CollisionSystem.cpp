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
					resolveCollision(object1, object2, 0, 0, 0, 0);
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
	bool collides = false;
	// TODO: do a better collision detection
	if (obj1->position.x == obj2->position.x) {
		return true;
	}
	return false;
}

//Resolves the collision that occurred between d and other
//xDelta1 and yDelta1 are the amount d moved before causing the collision.
//xDelta2 and yDelta2 are the amount other moved before causing the collision.
void CollisionSystem::resolveCollision(DisplayObject* d, DisplayObject* other,
		int xDelta1, int yDelta1, int xDelta2, int yDelta2) {
	// TODO: Implement resolve
	// Maybe find deltas through a custom Event with those parameters?
}

