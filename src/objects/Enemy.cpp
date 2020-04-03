#include "Enemy.h"
#include "Player.h"
#include "../engine/DisplayObjectContainer.h"
#include <cstdlib>

using namespace std;

//need to adjust .png and .xml
Enemy::Enemy(string id) : AnimatedSprite(id, spritesheet, xml){
	this->type = "Enemy";
	this->id = id;
	this->spritesheet = "./resources/player/player_sprites.png";
	this->xml = "./resources/player/player_sprites.xml";
	//this->width = 42; this->height = 40;
	this->pivot = {this->width/2, this->height/2};
}

void Enemy::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){
	//Sprite::update(pressedKeys, vector<ControllerState *> controllerStates);

	
	if(this->hp == 0){
		this->state = 0;
	}
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

void Enemy::onCollision(DisplayObject* other){
	
}

void Enemy::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
	//this->drawHitbox();
}


void Enemy::patrol(){	
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

void Enemy::stunned(){
    this->stunnedCount++;
    double delta = (SDL_GetTicks() - lastUpdate) / 1000;
	this->position.x += 0 * delta * unitScale; //0 instead of velX so don't have to worry about saving this value somewhere
    if (this->stunnedCount > 60){
        this->state = 1;
        this->stunnedCount = 0;
    }
}