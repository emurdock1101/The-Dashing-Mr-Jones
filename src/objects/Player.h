#pragma once
#include "../engine/AnimatedSprite.h"
class Player :
	public AnimatedSprite
{
public:
	Player();
	Player(string id);
	// HUD-status type stuff
	int hp = 2;
	int lives = 3;
	int ropes = 0;

	// movement stuff
	int state = 0; // 0 - player disabled, 1 - general movement (+jumping), 2 - dash, 3 - hurt/stunned, 4 - rope climbing, 5-rope deploy, 6-death
	int substate = 0; // optional - if you want more state logic within one state
	SDL_Point velocity = { 0,0 };
	bool isGrounded = true;
	bool canJump = true;
	bool canDash = true;
	double lastJumpTime;
	double runSpeed = 4;
	double runAccel = 8;
	double jumpAccel = 4;
	double maxFallSpeed = 8;
	double gravity = 4;

	double lastUpdate;

	void physicsUpdate();

	void update(set<SDL_Scancode> pressedKeys, vector<ControllerState*> controllerStates);
	void draw(AffineTransform &at);
};

