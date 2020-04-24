#pragma once
#include "../engine/AnimatedSprite.h"
class Mummy :
	public AnimatedSprite
{
public:
	Mummy();
	Mummy(string id);

	// movement stuff
	int state = 0; // 0 - instantiating stage, 1 - enemy stunned, 2 - enemy patrolling
	int substate = 0; // optional - if you want more state logic within one state
	double velX = 0;
	bool isGrounded = true;
	double lastGrounded;
	double runSpeed = 30;
	double runAccel = 300;
	double maxFallSpeed = 60;
	double gravity = 240;
	double unitScale = 16;

    SDL_Point originalPos = this->position;
    void patrol();
    void stunned();
    void onCollision(DisplayObject* other);
    int stunnedCount = 0;
    double patrolRange = 100;

	double PROTOTYPE_FLOOR_LEVEL = 800;

	double lastUpdate;

	void physicsUpdate();

	set<SDL_Scancode> lastKeys;
    
    AnimatedSprite* spriteObject;
    

	void update(set<SDL_Scancode> pressedKeys, vector<ControllerState*> controllerStates);
	void draw(AffineTransform &at);

    private:
	    void faceSprite(bool facingRight);
};