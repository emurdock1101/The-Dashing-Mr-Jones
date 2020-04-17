#include "Player.h"
using namespace std;
Player::Player() : AnimatedSprite() {
	
}
Player::Player(string id) : AnimatedSprite(id, "./resources/player/player_sprites.png", "./resources/player/player_sprites.xml") {
	spriteObject = new AnimatedSprite(id + "_Sprite", "./resources/player/player_sprites.png", "./resources/player/player_sprites.xml");
	DisplayObjectContainer::addChild(spriteObject);
	spriteObject->addAnimation("./resources/player/Adventurer Sprite Sheet v1/anim_slices-0/", "idle_right", 12, 12, true);
	spriteObject->play("idle_right");
	spriteObject->width = unitScale * 12;
	spriteObject->height = unitScale * 12;
	spriteObject->pivot = { 87, 126 };
	faceSprite(true);

	state = 1;
	

	AnimatedSprite::addAnimation("./resources/player/Adventurer Sprite Sheet v1/anim_slices-0/", "idle_right", 12, 12, true);
	AnimatedSprite::play("idle_right");

	DisplayObject::visible = false;

	// DisplayObject::loadTexture("./resources/player/basic_player.png");
	width = unitScale* 12;
	height = unitScale* 12;
	scaleX = 1;
	scaleY = 1;
	hitboxLeftOffset = 50;
	hitboxRightOffset = 68;
	hitboxDownOffset = 8;
	hitboxUpOffset = 68;
	// pivot = { 16,16 };
	showHitbox = true;

	lastUpdate = Game::frameCounter;
}

// This method is a helper method - multiple states might want to abide by the same laws of physics
void Player::physicsUpdate() {
	// double delta = (SDL_GetTicks() - lastUpdate) / 1000;
	double delta = (double)1/Game::instance->frames_per_sec;
	
	/*if (DisplayObject::position.y > PROTOTYPE_FLOOR_LEVEL) {
		isGrounded = true;
		canDash = true;
		canJump = true;
		if (velY > 0) {
			velY = 0;
		}
	}
	else {
		isGrounded = false;
	}*/

	DisplayObject::position.x += velX * delta * unitScale;
	DisplayObject::position.y += velY * delta * unitScale;
	double newVelY = velY + (gravity * delta);
	if (newVelY > maxFallSpeed) {
		velY = maxFallSpeed;
	}
	else {
		velY = newVelY;
	}
	isGrounded = false;
}

void Player::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates) {
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
				faceSprite(true);
				double newVx = velX + (runAccel*delta);
				if (newVx > runSpeed) {
					velX = runSpeed;
				}
				else {
					velX = newVx;
				}
			}
			if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
				faceSprite(false);
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

		if (Game::frameCounter - lastGrounded > 6) {
			isGrounded = false;
			canJump = false;
		}

		// jump code
		if (pressedKeys.find(SDL_SCANCODE_SPACE) != pressedKeys.end()) {
			if (lastKeys.find(SDL_SCANCODE_SPACE) == lastKeys.end() && canJump) {
				velY = -jumpPower;
				canJump = false;
				isGrounded = false;
				lastGrounded = Game::frameCounter;
			}
		}
		// shorthopping code - reduce velocity if quick release
		else if (!isGrounded && Game::frameCounter - lastGrounded < 6 && velY < 0) {
			velY = -jumpPower * 0.6;
		}

		// dash code
		if (pressedKeys.find(SDL_SCANCODE_C) != pressedKeys.end()) {
			if (lastKeys.find(SDL_SCANCODE_C) == lastKeys.end() && canDash) {
				SDL_Point axis = { 0,0 };
				// get horizontal
				if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
					axis.x += 1;
				}
				if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
					axis.x -= 1;
				}
				if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
					axis.y -= 1;
				} 
				if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
					axis.y += 1;
				}

				if (axis.x == 0 && axis.y == 0) {
					if (spriteObject->facingRight) {
						axis.x = 1;
					}
					else {
						axis.x = -1;
					}
				}

				canDash = false;
				state = 2;
				substate = Game::frameCounter;
				pointState = axis;
			}
		}


		physicsUpdate();
		break;
	case 2:
		// dashing

		// substate: stores the frame when the dash started
		// pointState: stores a vector of the direction we're dashing

		// if we're still dashing
		if (Game::frameCounter - substate < 15) {
			if (pointState.x == 0 || pointState.y == 0) {
				// if we're only handling one axis
				position.x += (int)((double)pointState.x * 20 * (25 + substate - Game::frameCounter) / 25);
				position.y += (int)((double)pointState.y * 20 * (25 + substate - Game::frameCounter) / 25);
			}
		}
		else {
			state = 1;
			velX = pointState.x * runSpeed;
			velY = pointState.y * runSpeed;
		}
		
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

void Player::faceSprite(bool facingRight) {
	if (facingRight) {
		spriteObject->position = { 87, 126 };
		spriteObject->facingRight = true;
	}
	else {
		spriteObject->position = { 69, 126 };
		spriteObject->facingRight = false;
	}
}


void Player::onCollision(DisplayObject *other, SDL_Point delta) {
	// if the thing pushed us up:
	if (delta.y < 0) {
		// a bit of a hacky way to stop bouncing off platforms

		// get the absolute top of the other entity
		SDL_Point topLeft1 = other->getTopLeftHitbox();
		SDL_Point topRight1 = other->getTopRightHitbox();
		SDL_Point bottomLeft1 = other->getBottomLeftHitbox();
		SDL_Point bottomRight1 = other->getBottomRightHitbox();

		vector<SDL_Point> obj1Points = { topLeft1, topRight1, bottomLeft1, bottomRight1 };
		int yH1 = INT_MAX;
		for (SDL_Point point : obj1Points) {
			if (point.y < yH1) {
				yH1 = point.y;
			}
		}

		// we cover the remaining distance to the top of that entity
		// we assume that the player in game logic always has a 1:1 scale with the global scale
		SDL_Point myBot = getBottomLeftHitbox();
		if (myBot.y < yH1) {
			int origY = position.y;
			position.y += yH1 - myBot.y;
			// just in case the player scale isn't 1:1 with global, we revert if something went wrong
			SDL_Point newBot = getBottomLeftHitbox();
			if (newBot.y > yH1) {
				position.y = origY;
			}
		}


		// state logic when hitting the ground
		isGrounded = true;
		lastGrounded = Game::frameCounter;
		canDash = true;
		canJump = true;
		velY = 0.002;
	}
	if (delta.y > 0) {
		velY = -0.0001;
	}
	if (delta.x == 0 && delta.y == 0) {
		if (velX == 0.0) {
			// logic to get unstuck
		}
	}
	DisplayObject::onCollision(other, delta);
}
