#include "Camera.h"

using namespace std;

Camera::Camera() {

}

Camera::~Camera() {
    
}

SDL_Point Camera::globalToViewportSpace(SDL_Point point) {
	SDL_Point pos = { x - point.x, y - point.y };

	pos.x = pos.x * (scaleX / (viewportWidth / 2) * 100);
	pos.y = pos.y * (scaleY / (viewportHeight / 2) * 100);

	return pos;
}