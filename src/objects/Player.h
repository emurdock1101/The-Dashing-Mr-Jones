#pragma once
#include "../engine/AnimatedSprite.h"
class Player :
	public AnimatedSprite
{
public:
	// HUD-status type stuff
	int hp = 2;
	int lives = 3;
	int ropes = 0;

	// movement stuff
	int state = 0; // 0 - player disabled, 1 - general movement (+jumping), 2 - dash, 3 - hurt/stunned, 4 - rope climbing, 5-rope deploy, 6-death
	double velX = 0.0;
	double velY = 0.0;
	bool isGrounded = true;
	bool canJump = true;
	bool canDash = true;
	double lastJumpTime;

	void physicsUpdate();

	void update(set<SDL_Scancode> pressedKeys, vector<ControllerState*> controllerStates);
};

