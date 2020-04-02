#include "Enemy.h"
#include "Player.h"
#include "../engine/DisplayObjectContainer.h"
#include <cstdlib>

using namespace std;

//need to adjust .png and .xml
Enemy::Enemy(string id) : AnimatedSprite(id, "./resources/player/player_sprites.png", "./resources/player/player_sprites.xml"){
	this->type = "Enemy";
	this->id = id;
	//this->width = 42; this->height = 40;
	this->pivot = {this->width/2, this->height/2};
}

void Enemy::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){
	//Sprite::update(pressedKeys, vector<ControllerState *> controllerStates);

	
	//enemy is dead so clean it up
	if(this->hp == 0){
		this->state = 0; //scene will clean it up
	}
    /* //Don't currently clean our enemies since they're just stunned
	//do the actual cleaning if necessary
	if(this->clean){
		this->removeThis();
		delete this;
	}*/

	//everything else controlled by state machine
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
	Sprite::draw(at);
	//this->drawHitbox();
}


void Enemy::patrol(){
	//if close to target, set a new one
	/*
	if(isTargetReached() && pauseCount == 119){
		this->targX = std::rand()%(this->maxPatX-this->minPatX) + this->minPatX;
		this->targY = std::rand()%(this->maxPatY-this->minPatY) + this->minPatY;
		this->vel = 0;
		this->maxVel = 4;
		this->pauseCount = 0;
	}

	if(pauseCount < 119){
		pauseCount = (pauseCount+1) % 120;
	}
	else{
		moveToTarget();
	}*/
}

void Enemy::stunned(){
    this->stunnedCount++;
    this->velX = 0;
    if (this->stunnedCount > 60){
        this->state = 1;
        this->stunnedCount = 0;
    }
}