#include "Player.h"
#include <limits.h>
using namespace std;
Player::Player() : AnimatedSprite() {
	
}
Player::Player(string id) : AnimatedSprite(id) {
	type = "player";
	
	spriteObject = new AnimatedSprite(id + "_Sprite", "./resources/player/player_sprites.png", "./resources/player/player_sprites.xml");
	DisplayObjectContainer::addChild(spriteObject);
	spriteObject->addAnimationFromSpriteSheet("./resources/player/player_sprites.png", "idle_right", 13, 20, true);
	spriteObject->addAnimationFromSpriteSheet("./resources/player/player_sprites.png", "run_right", 8, 6, true);
	spriteObject->addAnimationFromSpriteSheet("./resources/player/player_sprites.png", "dash_right", 10, 6, false);
	spriteObject->addAnimationFromSpriteSheet("./resources/player/player_sprites.png", "fall_right", 4, 12, true);
	spriteObject->play("idle_right");
	spriteObject->width = unitScale * 12;
	spriteObject->height = unitScale * 12;
	spriteObject->pivot = { 87, 126 };
	faceSprite(true);

	state = 1;
	

	// this is just to get the hitboxes aligned right
	AnimatedSprite::addAnimation("./resources/player/Adventurer Sprite Sheet v1/anim_slices-0/", "idle_right", 12, 12, true);
	AnimatedSprite::play("idle_right");
	DisplayObject::visible = false;

	// DisplayObject::loadTexture("./resources/player/basic_player.png");
	width = unitScale* 12;
	height = unitScale* 12;
	scaleX = 1;
	scaleY = 1;
	hitboxLeftOffset = 50;
	hitboxRightOffset = 78;
	hitboxDownOffset = 8;
	hitboxUpOffset = 68;
	// pivot = { 16,16 };
	showHitbox = false;

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
	// isGrounded = false;
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
	case PlayerState::NO_STATE:
		// null state
		break;
	case PlayerState::MOVEMENT:
		// ================================== general movement =========================

		// animation states
		if (isGrounded) {
			if (velX > 0.2 || velX < -0.2) {
				if (spriteObject->currentAnimName().compare("run_right") != 0) {
					spriteObject->play("run_right");
				}
			}
			else {
				if (spriteObject->currentAnimName().compare("idle_right") != 0) {
					spriteObject->play("idle_right");
				}
			}
		}
		else {
			if (spriteObject->currentAnimName().compare("fall_right") != 0) {
				spriteObject->play("fall_right");
			}
		}
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

		// detect if in air
		if (Game::frameCounter - lastGrounded > 6) {
			isGrounded = false;
			canJump = false;
		}

		// place rope code
		if (pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end() && lastKeys.find(SDL_SCANCODE_X) == lastKeys.end() && ropes > 0) {
			state = PlayerState::ROPE_DEPLOY;
			substate = Game::frameCounter;
			pointState.x = 0;
			velX = 0;
			velY = 0;
			break;
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
				handleDashInput(pressedKeys, controllerStates);
			}
		}

		// climb code
		if (touchingRope) {
			if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end() || pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
				state = PlayerState::CLIMBING;
			}
		}


		touchingRope = false;

		physicsUpdate();
		break;
	case PlayerState::DASHING:
		//  ========================= Dashing ============================

		// substate: stores the frame when the dash started
		// pointState: stores a vector of the direction we're dashing

		// if we're still dashing
		if (Game::frameCounter - substate < 3) {
			position.x += velX * delta * unitScale;
			position.y += velY * delta * unitScale;

			velX *= 0.8;
			velY *= 0.8;
			if (pointState.x == 0 || pointState.y == 0) {
				// if we're only handling one axis
				position.x += (int)((double)pointState.x * 32 * (Game::frameCounter - substate) / 3);
				position.y += (int)((double)pointState.y * 32 * (Game::frameCounter - substate) / 3);
			}
			else {
				position.x += (int)((double)pointState.x * 32 * (Game::frameCounter - substate) / 3 / 1.6);
				position.y += (int)((double)pointState.y * 32 * (Game::frameCounter - substate) / 3 / 1.6);
			}
		}
		else if (Game::frameCounter - substate < 20) {
			

			if (pointState.x == 0 || pointState.y == 0) {
				// if we're only handling one axis
				position.x += (int)((double)pointState.x * 32 * (28 + substate - Game::frameCounter) / 28);
				position.y += (int)((double)pointState.y * 32 * (28 + substate - Game::frameCounter) / 28);
			}
			else {
				position.x += (int)((double)pointState.x * 32 * (28 + substate - Game::frameCounter) / 28 / 1.6);
				position.y += (int)((double)pointState.y * 32 * (28 + substate - Game::frameCounter) / 28 / 1.6);
			}
		}
		else {
			state = PlayerState::MOVEMENT;

			velX = pointState.x * runSpeed;
			velY = pointState.y * runSpeed;
			if (pointState.x != 0 && pointState.y != 0) {
				velX /= 1.414;
				velY /= 1.414;
			}
		}
		touchingRope = false;

		break;
	case PlayerState::HITSTUN:
		// hitstun

		// not implemented
		break;
	case PlayerState::CLIMBING:
		// ===================================== rope climbing ====================================
		velX = 0.0;
		velY = 0.0;
		if (!touchingRope) {
			state = PlayerState::MOVEMENT;
			break;
		}
		else {
			lastGrounded = Game::frameCounter;
			canJump = true;
			canDash = true;
		}

		// movement code
		if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
			position.x -= (int)(climbSpeed * unitScale);
		}
		if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
			position.x += (int)(climbSpeed * unitScale);
		}
		if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
			position.y -= (int)(climbSpeed * unitScale);
		}
		if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
			position.y += (int)(climbSpeed * unitScale);
		}

		// jump code
		if (pressedKeys.find(SDL_SCANCODE_SPACE) != pressedKeys.end()) {
			if (lastKeys.find(SDL_SCANCODE_SPACE) == lastKeys.end() && canJump) {
				velY = -jumpPower;
				canJump = false;
				isGrounded = false;
				lastGrounded = Game::frameCounter;
				state = PlayerState::MOVEMENT;
			}
		} 
		
		// dash code
		if (pressedKeys.find(SDL_SCANCODE_C) != pressedKeys.end()) {
			if (lastKeys.find(SDL_SCANCODE_C) == lastKeys.end() && canDash) {
				handleDashInput(pressedKeys, controllerStates);
			}
		}

		touchingRope = false;
		break;
	case 5:
		// ================ rope deploy =======================

		if (Game::frameCounter - substate > 120) {
			ropes--;
			Event ropeEvent(EventParams::ROPE_DEPLOYED, this);
			EventDispatcher::dispatchEvent(&ropeEvent);
			state = PlayerState::MOVEMENT;
		}
		break;
	case 6:
		// death
		break;
	}

	
	lastKeys = pressedKeys;
	lastUpdate = SDL_GetTicks();
	AnimatedSprite::update(pressedKeys, controllerStates);
}

void Player::handleDashInput(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates) {
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

	if (axis.x < 0) {
		faceSprite(false);
	}
	else if (axis.x > 0) {
		faceSprite(true);
	}
	spriteObject->play("dash_right");

	canDash = false;
	state = 2;
	substate = Game::frameCounter;
	pointState = axis;
}

void Player::onCollision(DisplayObject *other, SDL_Point delta) {
	if (other->type == "rope_seg") {
		// rope segment handling
		touchingRope = true;
	}
	else {
		// genertic entity handling:

		// if the thing pushed us up:
		if (delta.y < 0) {
			// a bit of a hacky way to stop bouncing off platforms: cover remaining distance assuming player is in global space

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
		if (delta.y > 0) { // remove upwards velocity when hitting a ceiling
			velY = -0.0001;
		}
	}

	DisplayObject::onCollision(other, delta);
}

Rope* Player::makeRope() {
	Rope* newRope = new Rope(ropeLength);
	return newRope;
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

void Player::faceSprite(bool facingRight) {
	DisplayObject::facingRight = facingRight;
	if (facingRight) {
		spriteObject->position = { 87, 126 };
		spriteObject->facingRight = true;
	}
	else {
		spriteObject->position = { 60, 126 };
		spriteObject->facingRight = false;
	}
}
