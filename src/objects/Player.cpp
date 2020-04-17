#include "Player.h"
using namespace std;
Player::Player() : AnimatedSprite() {
	
}
Player::Player(string id) : AnimatedSprite(id, "./resources/player/player_sprites.png", "./resources/player/player_sprites.xml") {
	state = 1;
	

	AnimatedSprite::addAnimationFromSpriteSheet("./resources/player/player_sprites.png", "idle_right", 12, 12, true);
	AnimatedSprite::play("idle_right");

	// DisplayObject::loadTexture("./resources/player/basic_player.png");
	width = unitScale* 12;
	height = unitScale* 12;
	scaleX = 1;
	scaleY = 1;
	hitboxLeftOffset = 12;
	hitboxRightOffset = 12;
	hitboxDownOffset = 0;
	hitboxUpOffset = 12;
	pivot = { 16,16 };
	showHitbox = true;

	lastUpdate = SDL_GetTicks();
}

// This method is a helper method - multiple states might want to abide by the same laws of physics
void Player::physicsUpdate() {
	// double delta = (SDL_GetTicks() - lastUpdate) / 1000;
	double delta = (double)1/Game::instance->frames_per_sec;
	
	if (DisplayObject::position.y > PROTOTYPE_FLOOR_LEVEL) {
		isGrounded = true;
		canDash = true;
		canJump = true;
		if (velY > 0) {
			velY = 0;
		}
	}
	else {
		isGrounded = false;
	}

	DisplayObject::position.x += velX * delta * unitScale;
	DisplayObject::position.y += velY * delta * unitScale;
	double newVelY = velY + (gravity * delta);
	if (newVelY > maxFallSpeed) {
		velY = maxFallSpeed;
	}
	else {
		velY = newVelY;
	}
}

void Player::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates) {
	if (inDevtool) {
		AnimatedSprite::update(pressedKeys, controllerStates);
		return;
	}
	DisplayObject::prevPos = position;
	// double delta = (SDL_GetTicks() - lastUpdate) / 1000;
	double delta = (double)1 / Game::instance->frames_per_sec;
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

		// horizontal input
		if ((pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) ^ (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end())) {
			if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
				double newVx = velX + (runAccel*delta);
				if (newVx > runSpeed) {
					velX = runSpeed;
				}
				else {
					velX = newVx;
				}
			}
			if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
				double newVx = velX - (runAccel*delta);
				if (newVx < -runSpeed) {
					velX = -runSpeed;
				}
				else {
					velX = newVx;
				}
			}
		}
		else { // no horizontal input
			if (velX > 0) {
				double newVx = velX - (runAccel*delta);
				if (newVx < 0) {
					velX = 0;
				}
				else {
					velX = newVx;
				}
			}
			else {
				double newVx = velX + (runAccel*delta);
				if (newVx > 0) {
					velX = 0;
				}
				else {
					velX = newVx;
				}
			}
			
		}
		
		if (pressedKeys.find(SDL_SCANCODE_SPACE) != pressedKeys.end()) {
			if (lastKeys.find(SDL_SCANCODE_SPACE) == lastKeys.end() && canJump) {
				velY = -jumpPower;
				canJump = false;
				lastGrounded = SDL_GetTicks();
			}
			else if (SDL_GetTicks() - lastGrounded < 100) {
				velY = -jumpPower;
			}
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

	
	lastKeys = pressedKeys;
	lastUpdate = SDL_GetTicks();
	AnimatedSprite::update(pressedKeys, controllerStates);
}

void Player::draw(AffineTransform &at) {
	AnimatedSprite::draw(at);
}


void Player::writeSceneData(ostream &stream) {
	stream << "AnimatedSprite" << " ";
	stream << id << " ";
	stream << position.x << " ";
	stream << position.y << " ";
	stream << pivot.x << " ";
	stream << pivot.y << " ";
	stream << scaleX << " ";
	stream << scaleY << " ";
	stream << rotation << " ";
	stream << height << " ";
	stream << width << " ";
	stream << alpha << " ";
	stream << this->animations.size();
	// Animation args
	if (parent != NULL && parent->type != "Scene") {
		stream << " " << parent->id;
	}
	stream << endl;
	for (Animation * animation : animations) {
		stream << animation->basepath << " ";
		stream << animation->animName << " ";
		stream << animation->numFrames << " ";
		stream << animation->frameRate << " ";
		stream << animation->loop << endl;
	}
}
