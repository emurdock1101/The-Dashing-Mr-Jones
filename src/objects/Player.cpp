#include "Player.h"
using namespace std;
Player::Player() : AnimatedSprite() {
	state = 1;
	lastUpdate = SDL_GetTicks();
}
Player::Player(string id) : AnimatedSprite(id, "./resources/player/player_sprites.png", "./resources/player/player_sprites.xml") {
	state = 1;
	

	AnimatedSprite::addAnimation("./resources/player/Adventurer Sprite Sheet v1/anim_slices-0/idle_right", "idle", 13, 12, true);
	AnimatedSprite::play("idle");
	width = 32;
	height = 32;
	scaleX = 1;
	scaleY = 1;
	pivot = { 16,16 };

	lastUpdate = SDL_GetTicks();
}

// This method is a helper method - multiple states might want to abide by the same laws of physics
void Player::physicsUpdate() {
	double delta = SDL_GetTicks() - lastUpdate;
	

	DisplayObject::position.x += velocity.x * delta / 1000;
	DisplayObject::position.y += velocity.y * delta / 1000;
	double newVelY = velocity.y + gravity;
	if (newVelY < maxFallSpeed) {
		velocity.y = maxFallSpeed;
	}
	else {
		velocity.y = newVelY;
	}
}

void Player::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates) {
	DisplayObject::prevPos = position;
	// Remember to reference the state diagram. 
	// I've merged the general movement and jumping states.
	// Keep in mind that this function keeps firing for every frame that the state is active. If you want, you can create new states 
	// and class fields to wait out tweens/other stuff before transitioning to another state.
	switch (this->state) {
	case 0:
		// null state
		break;
	case 1:
		// general movement
		if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
			position.x += 6;
		}
		if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
			position.x -= 6;
		}
		if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
			position.y += 6;
		}
		if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
			position.y -= 6;
		}


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

	
	lastUpdate = SDL_GetTicks();
	AnimatedSprite::update(pressedKeys, controllerStates);
}

void Player::draw(AffineTransform &at) {
	AnimatedSprite::draw(at);
}