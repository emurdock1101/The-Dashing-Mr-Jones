#ifndef CONTROLLERSTATE_H
#define CONTROLLERSTATE_H

#include <SDL2/SDL.h>

// Joystick state - positive, negative, or neutral meaning in deadzone
enum JoystickState {
	POSITIVE,
	NEGATIVE,
	NEUTRAL
};

// State of the entire controller
struct ControllerState {
	uint8_t id;
	// SDL_GameControllerButton
	set<uint8_t> pressedButtons;
	// The left and right joystick's state
	JoystickState joyLeftX;
	JoystickState joyLeftY;
	JoystickState joyRightX;
	JoystickState joyRightY;
};

#endif
