#include "Scorpion.h"
#include "../engine/DisplayObjectContainer.h"
#include <cstdlib>

using namespace std;

//need to adjust .png and .xml
Scorpion::Scorpion(string id) : AnimatedSprite(id, "./resources/player/player_sprites.png", "./resources/player/player_sprites.xml"){
	this->type = "Scorpion";
	this->id = id;
    this->alpha = 0;
	//this->width = 42; this->height = 40;
	this->pivot = {this->width/2, this->height/2};
}

void Scorpion::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){
	//Sprite::update(pressedKeys, vector<ControllerState *> controllerStates);

	
	if(this->hp == 0){
		this->state = 0;
	}
	//state 0 = one time state to kick things off
    //state 1 = hidden
	//state 2 = appeared
    //would be nice to have either a state for transitioning back and forth and/or a tween that does so
	
	switch (this->state){
        case 0:
            this->state = 1;
            break;
        
        case 1:
            hidden();
            break;
        case 2:
            appear();
            break;
    }
    this->hiddenCount++;
    this->appearCount++;
}

void Scorpion::hidden(){
    
    if (this->hiddenCount >= 60){
        this->state = 2;
    }
    else {
        this->alpha = 0;
        this->canCollide = false;
    }
    appearCount = 0;
}

void Scorpion::appear(){
    
    if (this->appearCount >= 60){
        this->state = 1;
    }
    else {
        this->alpha = 225;
        this->canCollide = true;
    }
    hiddenCount = 0;
}

void Scorpion::attack(){
    //requires venom class (subclass of projectile) to create
}

void Scorpion::onCollision(DisplayObject* other){
}

void Scorpion::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
	//this->drawHitbox();
}