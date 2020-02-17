#include "DisplayObjectContainer.h"
#include "Scene.h"
#include "AffineTransform.h"
#include "Game.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Scene::Scene() : DisplayObjectContainer() {
	this->type = "Scene";
}

Scene::~Scene() {
}

void Scene::draw(AffineTransform &at) {
	DisplayObjectContainer::draw(at);
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (int y = 0; y < 1000; y += gridPixels) {
		SDL_RenderDrawLine(Game::renderer, 0, y, 1200, y);
	}
	for (int x = 0; x < 1200; x += gridPixels) {
		SDL_RenderDrawLine(Game::renderer, x, 0, x, 1000);
	}
}
