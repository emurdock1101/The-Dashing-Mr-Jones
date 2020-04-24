#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include "./events/EventListener.h"
#include "./events/Event.h"
#include <map>
#include <vector>
#include "./Camera.h"
#include <climits>

using namespace std;

class CollisionSystem : public EventListener{

public:
	struct CollisionRegistration {
		string type1;
		string type2;
		bool resolve;
	};

	CollisionSystem();
	~CollisionSystem();

	//checks collisions between pairs of DOs where the corresponding types have been requested
	//to be checked (via a single call to watchForCollisions) below.
	void update();

	//This system watches the game's display tree and is notified whenever a display object is placed onto
	//or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
	void handleEvent(Event* e);

	//This function asks the collision system to start checking for collisions between all pairs
	//of DOs of a given type (e.g., player vs platform). The system will begin to check all player objects
	//against all platform objects that are in the current scene.
	void watchForCollisions(string type1, string type2);
	void watchForCollisions(string type1, string type2, bool resolve);

	//returns true iff obj1 hitbox and obj2 hitbox overlap. Uses the following method from DO:
	//	SDL_Point* DisplayObject::getGlobalHitbox();
	bool collidesWith(DisplayObject* obj1, DisplayObject* obj2);

	//Resolves the collision that occurred between d and other
	//xDelta1 and yDelta1 are the amount d moved before causing the collision.
	//xDelta2 and yDelta2 are the amount other moved before causing the collision.
	void resolveCollision(DisplayObject* d, DisplayObject* other, int xDelta1, int yDelta1, int xDelta2, int yDelta2);
	void notifyCollision(DisplayObject* d, DisplayObject* other, SDL_Point deltaD, SDL_Point deltaO);

	Camera *camera;
private:
	bool lineSegmentsIntersect(SDL_Point a, SDL_Point b, SDL_Point c, SDL_Point d);
	// 1 means clockwise (1st slope larger)
	// 0 means colinear
	// -1 means counterclockwise (2nd slope larger)
	int getOrientation(SDL_Point a, SDL_Point b, SDL_Point c);

	// Id to vector of DisplayObjects with that id
	map<string, vector<DisplayObject *> *> knownIds;
	// Pairs of ids that are watched for collisions
	// Does not check for double adds - so may trigger twice if not careful
	vector<CollisionRegistration> watchedIds;

	bool triggeredByX = false;
	bool triggeredByY = false;

	// Camera, if set, will only run collision checks for things within 1.5x range of the camera

};

#endif
