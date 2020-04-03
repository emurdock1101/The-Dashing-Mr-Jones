#ifndef SCORPION_H
#define SCORPION_H
#include "../engine/AnimatedSprite.h"
class Scorpion :
	public AnimatedSprite
{
public:
	Scorpion();
	Scorpion(string id);
	// HUD-status type stuff
	int hp = 1;

	// movement stuff
	int state = 0; // 0 - instantiating stage, 1 - enemy stunned, 2 - enemy patrolling
	int substate = 0; // optional - if you want more state logic within one state

    void onCollision(DisplayObject* other);
    int hiddenCount = 0;
    int appearCount = 0;
    bool canCollide = false;
    void hidden();
    void appear();
    void attack();
    /*
	string spritesheet = "./resources/player/player_sprites.png";
	string xml = "./resources/player/player_sprites.xml";
    */

	double PROTOTYPE_FLOOR_LEVEL = 800;

	double lastUpdate;

	//void physicsUpdate();

	set<SDL_Scancode> lastKeys;

	void update(set<SDL_Scancode> pressedKeys, vector<ControllerState*> controllerStates);
	void draw(AffineTransform &at);
};
#endif