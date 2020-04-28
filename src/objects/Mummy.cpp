#include "Mummy.h"
#include "Player.h"
#include "../engine/DisplayObjectContainer.h"
#include <cstdlib>
#include <climits>
#include <iostream>

using namespace std;

Mummy::Mummy(int x, int y) : AnimatedSprite("mummy", "./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy.xml"){
	this->type = "mummy";
	this->id = id;
	this->originalPos = {x, y};
	this->width = unitScale * 12;
	this->height = unitScale * 12;
	this->setPos(x, y);

	AnimatedSprite::addAnimationFromSpriteSheet("./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "walk_right", 4, 16, true);
	AnimatedSprite::addAnimationFromSpriteSheet("./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "walk_left", 4, 16, true);
	AnimatedSprite::addAnimationFromSpriteSheet("./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "walk_forward", 4, 16, true);
	AnimatedSprite::addAnimationFromSpriteSheet("./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "walk_back", 4, 16, true);
	AnimatedSprite::addAnimationFromSpriteSheet("./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "turn_left", 3, 32, false);
	AnimatedSprite::addAnimationFromSpriteSheet("./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "turn_right", 3, 32, false);
	AnimatedSprite::play("walk_right");
	this->walkingRight = true;
}

//need to adjust .png and .xml
Mummy::Mummy(string id, int x, int y) : AnimatedSprite(id, "./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy-01.png", "./resources/sprites_unsorted/mummy-1.2/PNG/48x64/mummy.xml"){
	this->type = "Mummy";
	this->id = id;
	this->originalPos = {x, y};
	this->width = unitScale * 12;
	this->height = unitScale * 12;
	this->setPos(x, y);

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
	if (inDevtool) {
		AnimatedSprite::update(pressedKeys, controllerStates);
		return;
	}

	//state 0 = one time state to kick things off, mummy falls until it collides
	//	with floor
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

void Mummy::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

void Mummy::init() {
	// Fall until we hit floor
	this->setPos(this->position.x, this->position.y + velY);
}

void Mummy::patrol() {
	// TODO: check if hit by player, maybe better in onCollision
	if (false) {
		// Stun
		this->state = 2;
	}
	else {
		// if outside of its patrol range
		// Not implemented: hits platform/edge
		if(abs(this->position.x - this->originalPos.x) > this->patrolRange ) {
			// Turn
			this->state = 3;
		}
		// Regardless, move according to its velocity
		this->setPos(this->position.x + velX, this->position.y);
	}

}

void Mummy::stunned(){
	this->stop();
    this->stunnedCount++;
    if (this->stunnedCount > 60){
		this->replay();
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
	// Collides with player
	// TODO: reduce player's health with event or something?
	if (other->type == "player") {
		this->state = 2;
		this->stunnedCount = 0;
	}

	// Collision block/generic entities
	// if the thing pushed us up:
	else {
		if (delta.y < 0) {
			// state logic when hitting the ground
			isGrounded = true;
			this->state = 1;
		}
		if (delta.y > 0) { // remove upwards velocity when hitting a ceiling
			velY = -0.0001;
		}
	}

	DisplayObject::onCollision(other, delta);
}

void Mummy::writeSceneData(ostream &stream) {
	stream << "mummy" << " ";
	stream << id << " ";
	stream << position.x << " ";
	stream << position.y << " ";
	stream << patrolRange << endl;
}

