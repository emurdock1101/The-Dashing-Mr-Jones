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
	cout << "pos: " << this->position.x << " y: " << this->position.y << endl;
	cout << "prev pos: " << this->prevPos.x << " y: " << this->prevPos.y << endl;

	//spriteObject->type = "Mummy";
	AnimatedSprite::addAnimationFromSpriteSheet("./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "walk_right", 4, 16, true);
	AnimatedSprite::addAnimationFromSpriteSheet("./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "walk_left", 4, 16, true);
	AnimatedSprite::addAnimationFromSpriteSheet("./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "walk_forward", 4, 16, true);
	AnimatedSprite::addAnimationFromSpriteSheet("./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "walk_back", 4, 16, true);
	AnimatedSprite::addAnimationFromSpriteSheet("./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "turn_left", 3, 32, false);
	AnimatedSprite::addAnimationFromSpriteSheet("./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "turn_right", 3, 32, false);
	AnimatedSprite::play("walk_right");
	this->walkingRight = true;
}

void Mummy::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){
	cout << "pos: " << this->position.x << " y: " << this->position.y << endl;

	
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
	AnimatedSprite::update(pressedKeys, controllerStates);
}

void Mummy::onCollision(DisplayObject* other){
	
}

void Mummy::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
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
		this->setPos(this->position.x + velX * 2, this->position.y);
		this->position.x += velX * 2;

	}
}

void Mummy::onCollision(DisplayObject *other, SDL_Point delta) {
	// genertic entity handling:

	cout << delta.y << endl;
	// if the thing pushed us up:
	if (delta.y < 0) {
		// state logic when hitting the ground
		isGrounded = true;
		this->state = 1;
	}
	if (delta.y > 0) { // remove upwards velocity when hitting a ceiling
		velY = -0.0001;
	}

	DisplayObject::onCollision(other, delta);
}
