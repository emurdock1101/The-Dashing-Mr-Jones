#include "Guard.h"
#include "Player.h"
#include "../engine/DisplayObjectContainer.h"
#include <cstdlib>

using namespace std;

//need to adjust .png and .xml
Guard::Guard(string id, Player* player) : AnimatedSprite(id, "./resources/player/player_sprites.png", "./resources/player/player_sprites.xml"){
	this->type = "Guard";
	this->id = id;
    this->player = player;
	//this->width = 42; this->height = 40;
	this->pivot = {this->width/2, this->height/2};
}

void Guard::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){
	//Sprite::update(pressedKeys, vector<ControllerState *> controllerStates);


	//state 0 = one time state to kick things off
    //state 1 = stunned
	//state 2 = patrolling
    //state 3 = pursuing
	
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
        case 3:
            pursue();
            break;
    }
}

void Guard::onCollision(DisplayObject* other){
	
}

void Guard::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
	//this->drawHitbox();
}


void Guard::patrol(){	
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

        //check for if player is within range -- need to fiddle with/think about y-range more
        if (this->facingRight == true && this->player->position.x >= this->position.x && abs(this->player->position.y - this->position.x) <= 100){
            this->state = 3;
        }
        else if (this->facingRight == false && this->player->position.x <= this->position.x && abs(this->player->position.y - this->position.x) <= 100){
            this->state = 3;
        }

		//regardless, move according to its velocity
		double delta = (SDL_GetTicks() - lastUpdate) / 1000;
		DisplayObject::position.x += velX * delta * unitScale;
	}

}

void Guard::stunned(){
    this->stunnedCount++;
    double delta = (SDL_GetTicks() - lastUpdate) / 1000;
	this->position.x += 0 * delta * unitScale; //0 instead of velX so don't have to worry about saving this value somewhere
    if (this->stunnedCount > 60){
        this->state = 1;
        this->stunnedCount = 0;
    }
}

void Guard::pursue(){
    //if guard is to the left of the player
    if (this->player->position.x > this->position.x){
        this->position.x += this->runSpeed;
    }
    //if guard is to the right of the player
    else{
        this->position.x -= this->runSpeed;
    }

}