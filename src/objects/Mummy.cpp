#include "Mummy.h"
#include "../engine/AnimatedSprite.h"
#include "../engine/DisplayObjectContainer.h"
#include <cstdlib>

using namespace std;


Mummy::Mummy(string id) : Enemy(id){
	this->type = "Mummy";
	this->id = id;
    this->spritesheet = "./resources/player/player_sprites.png";
    this->xml = "./resources/player/player_sprites.xml";
	//this->width = 42; this->height = 40;
	this->pivot = {this->width/2, this->height/2};
}