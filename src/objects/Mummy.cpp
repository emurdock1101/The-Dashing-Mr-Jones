#include "Mummy.h"
#include "Player.h"
#include "../engine/DisplayObjectContainer.h"
#include <cstdlib>

using namespace std;

//need to adjust .png and .xml
Mummy::Mummy(string id) : AnimatedSprite(id){
	this->type = "Mummy";
	this->id = id;
	//this->width = 42; this->height = 40;
	this->pivot = {this->width/2, this->height/2};

	spriteObject = new AnimatedSprite(id + "_Sprite", "./resources/player/player_sprites.png", "./resources/player/player_sprites.xml");
	DisplayObjectContainer::addChild(spriteObject);
	spriteObject->addAnimationFromSpriteSheet("./resources/player/player_sprites.png", "idle_right", 13, 20, true);
	spriteObject->addAnimationFromSpriteSheet("./resources/player/player_sprites.png", "run_right", 8, 6, true);
	spriteObject->addAnimationFromSpriteSheet("./resources/player/player_sprites.png", "dash_right", 10, 6, false);
	spriteObject->addAnimationFromSpriteSheet("./resources/player/player_sprites.png", "fall_right", 4, 12, true);
	spriteObject->play("idle_right");
	spriteObject->width = unitScale * 12;
	spriteObject->height = unitScale * 12;
	spriteObject->pivot = { 87, 126 };
	faceSprite(true);
}

void Mummy::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){
	//Sprite::update(pressedKeys, vector<ControllerState *> controllerStates);

	
	//state 0 = one time state to kick things off
    //state 1 = stunned
	//state 2 = patrolling
	
	switch (this->state){
        case 0:
            this->state = 1;
            break;
        
        case 1:
            patrol();
            break;
        case 2:
            stunned();
            break;
    }
}

void Mummy::onCollision(DisplayObject* other){
	
}

void Mummy::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
	//this->drawHitbox();
}


void Mummy::patrol(){	
	//check for if been hit by player then
	if (false){
		this->state = 2;
	}
	else{
		
		//if outside of it's patrol range OR at the edge of a platform, then turn around
		if(abs(this->position.x - this->originalPos.x) > this->patrolRange ){ //NEEED TO ADD the platform collison detection
			this->velX = - this->velX;
			this->facingRight = !this->facingRight;
		}
		//regardless, move according to its velocity
		double delta = (SDL_GetTicks() - lastUpdate) / 1000;
		DisplayObject::position.x += velX * delta * unitScale;
	}

}

void Mummy::stunned(){
    this->stunnedCount++;
    double delta = (SDL_GetTicks() - lastUpdate) / 1000;
	this->position.x += 0 * delta * unitScale; //0 instead of velX so don't have to worry about saving this value somewhere
    if (this->stunnedCount > 60){
        this->state = 1;
        this->stunnedCount = 0;
    }
}

void Mummy::faceSprite(bool facingRight) {
	if (facingRight) {
		spriteObject->position = { 87, 126 };
		spriteObject->facingRight = true;
	}
	else {
		spriteObject->position = { 60, 126 };
		spriteObject->facingRight = false;
	}
}