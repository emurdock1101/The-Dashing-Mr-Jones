#include "Player.h"
using namespace std;
Player::Player() : AnimatedSprite() {

}


// This method is a helper method - multiple states might want to abide by the same laws of physics
void Player::physicsUpdate() {

}

void Player::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates) {
	// Remember to reference the state diagram.
	// Keep in mind that this function keeps firing for every frame that the state is active. If you want, you can create new states 
	// and class fields to wait out tweens/other stuff before transitioning to another state.
	switch (this->state) {
	case 0:
		// null state
		break;
	case 1:
		// general movement

		physicsUpdate();
		break;
	case 2:
		// dashing
		break;
	case 3:
		// hitstun
		break;
	case 4:
		// rope climbing
		break;
	case 5:
		// rope deploy
		break;
	case 6:
		// death
		break;
	}

	

	AnimatedSprite::update(pressedKeys, controllerStates);
}

