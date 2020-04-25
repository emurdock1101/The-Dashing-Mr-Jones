#include "Mummy.h"
#include "Player.h"
#include "../engine/DisplayObjectContainer.h"
#include <cstdlib>
#include <climits>
#include <iostream>

using namespace std;

//need to adjust .png and .xml
Mummy::Mummy(string id, int x, int y) : AnimatedSprite(id, "./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy.xml"){
	this->type = "Mummy";
	this->id = id;
	//this->width = 42; this->height = 40;
	//this->pivot = {this->width/2, this->height/2};
	this->originalPos = {x, y};
	this->width = unitScale * 12;
	this->height = unitScale * 12;
	this->setPos(x, y);

	//spriteObject->type = "Mummy";
	AnimatedSprite::addAnimationFromSpriteSheet("./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "walk_right", 4, 16, true);
	AnimatedSprite::addAnimationFromSpriteSheet("./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "walk_left", 4, 16, true);
	AnimatedSprite::addAnimationFromSpriteSheet("./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "walk_forward", 4, 16, true);
	AnimatedSprite::addAnimationFromSpriteSheet("./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "walk_back", 4, 16, true);
	AnimatedSprite::addAnimationFromSpriteSheet("./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "turn_left", 3, 32, false);
	AnimatedSprite::addAnimationFromSpriteSheet("./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "turn_right", 3, 32, false);
	AnimatedSprite::play("walk_right");
	this->walkingRight = true;
	faceSprite(true);
}

void Mummy::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){
	AnimatedSprite::update(pressedKeys, controllerStates);

	
	//state 0 = one time state to kick things off
	//state 1 = patrolling
    //state 2 = stunned
	//state 3 = turning around
	
	switch (this->state){
        case 0:
			init();
            break;
        
        case 1:
            patrol();
            break;
        case 2:
            stunned();
            break;
        case 3:
            turn();
            break;
    }
}

void Mummy::onCollision(DisplayObject* other){
	
}

void Mummy::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
	//this->drawHitbox();
}

void Mummy::init() {
	// Fall until we hit floor
	this->setPos(this->position.x, this->position.y + velY);
}

void Mummy::patrol(){	
	//check for if been hit by player then
	if (false){
		this->state = 2;
	}
	else{
		//if outside of its patrol range OR at the edge of a platform, then turn around
		if(abs(this->position.x - this->originalPos.x) > this->patrolRange ){ //NEEED TO ADD the platform collison detection
			// Turn
			this->state = 3;
		}
		//regardless, move according to its velocity
		this->position.x += velX;
		this->setPos(this->position.x + velX, this->position.y);
	}

}

void Mummy::stunned(){
    this->stunnedCount++;
    if (this->stunnedCount > 60){
        this->state = 1;
        this->stunnedCount = 0;
    }
}

void Mummy::turn() {
	this->turnCount++;
	if (!startedTurn) {
		this->walkingRight = !this->walkingRight;
		this->velX = -this->velX;
		if (this->walkingRight) {
			this->play("turn_right");
		}
		else {
			this->play("turn_left");
		}
		this->startedTurn = true;
	}
    if (this->turnCount > 64){
		this->state = 1;
		this->startedTurn = false;
		this->turnCount = 0;
		if (this->walkingRight) {
			this->play("walk_right");
		}
		else {
			this->play("walk_left");
		}
		// And walk one step so it doesn't auto turn around again
		this->position.x += velX * 2;

	}
}

void Mummy::faceSprite(bool facingRight) {
	if (facingRight) {
		this->position = { 87, 126 };
		this->facingRight = true;
	}
	else {
		this->position = { 60, 126 };
		this->facingRight = false;
	}
}

void Mummy::onCollision(DisplayObject *other, SDL_Point delta) {
	cout << "COLLISION OMG" << endl;
	// a bit of a hacky way to stop bouncing off platforms: cover remaining distance assuming player is in global space

	// get the absolute top of the other entity
	SDL_Point topLeft1 = other->getTopLeftHitbox();
	SDL_Point topRight1 = other->getTopRightHitbox();
	SDL_Point bottomLeft1 = other->getBottomLeftHitbox();
	SDL_Point bottomRight1 = other->getBottomRightHitbox();

	vector<SDL_Point> obj1Points = { topLeft1, topRight1, bottomLeft1, bottomRight1 };
	int yH1 = INT_MAX;
	for (SDL_Point point : obj1Points) {
		if (point.y < yH1) {
			yH1 = point.y;
		}
	}

	// we cover the remaining distance to the top of that entity
	// we assume that the player in game logic always has a 1:1 scale with the global scale
	SDL_Point myBot = getBottomLeftHitbox();
	if (myBot.y < yH1) {
		int origY = position.y;
		position.y += yH1 - myBot.y;
		// just in case the player scale isn't 1:1 with global, we revert if something went wrong
		SDL_Point newBot = getBottomLeftHitbox();
		if (newBot.y > yH1) {
			position.y = origY;
		}
	}

	// state logic when hitting the ground
	isGrounded = true;
	velY = 0.002;
	this->state = 1;

	DisplayObject::onCollision(other, delta);
}
