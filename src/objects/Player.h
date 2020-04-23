#pragma once
#include "../engine/AnimatedSprite.h"
#include "../engine/Game.h"
class Player :
	public AnimatedSprite
{
public:
	Player();
	Player(string id);

	AnimatedSprite* spriteObject;

	// HUD-status type stuff
	int hp = 2;
	int lives = 3;
	int ropes = 0;
	bool dashUnlocked = true;

	// movement stuff
	int state = 0; // 0 - player disabled, 1 - general movement (+jumping), 2 - dash, 3 - hurt/stunned, 4 - rope climbing, 5-rope deploy, 6-death
	int substate = 0; // optional - if you want more state logic within one state
	SDL_Point pointState = { 0,0 }; // also optional, for state logic
	double velX = 0;
	double velY = 0;
	bool isGrounded = true;
	bool canJump = true;
	bool canDash = true;
	int lastGrounded;
	double runSpeed = 32;
	double runAccel = 600;
	double jumpPower = 80;
	double maxFallSpeed = 120;
	double gravity = 180;
	double unitScale = 16;

	double PROTOTYPE_FLOOR_LEVEL = 1200;

	int lastUpdate;

	void physicsUpdate();

	set<SDL_Scancode> lastKeys;

	virtual void writeSceneData(ostream &stream);

	void update(set<SDL_Scancode> pressedKeys, vector<ControllerState*> controllerStates);
	void draw(AffineTransform &at);
	void onCollision(DisplayObject *other, SDL_Point delta);

private:
	void faceSprite(bool facingRight);
};

