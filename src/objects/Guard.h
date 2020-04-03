#ifndef GUARD_H
#define GUARD_H
#include "../engine/AnimatedSprite.h"
#include "Player.h"
class Guard :
	public AnimatedSprite
{
public:
	Guard();
	Guard(string id, Player* player);

	// movement stuff
	int state = 0; // 0 - instantiating stage, 1 - enemy stunned, 2 - enemy patrolling
	int substate = 0; // optional - if you want more state logic within one state
	double velX = 0;
	bool isGrounded = true;
	double lastGrounded;
	double runSpeed = 20;
	double runAccel = 300;
	double maxFallSpeed = 60;
	double gravity = 240;
	double unitScale = 16;

    SDL_Point originalPos = this->position;
    int targetX;
    void patrol();
    void stunned();
    void pursue();
    void onCollision(DisplayObject* other);
    int stunnedCount = 0;
    double patrolRange = 100;
    Player* player;

	double PROTOTYPE_FLOOR_LEVEL = 800;

	double lastUpdate;

	void physicsUpdate();

	set<SDL_Scancode> lastKeys;

	void update(set<SDL_Scancode> pressedKeys, vector<ControllerState*> controllerStates);
	void draw(AffineTransform &at);
};

#endif