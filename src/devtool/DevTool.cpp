#include <iostream>
#include "DevTool.h"
#include <string>
#include <ctime>
#include "Game.h"
#include "Scene.h"
#include "Sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

DevTool::DevTool() : Game(1200, 1000) {
	scene = new Scene();
	selected = new Sprite("character","./resources/character/Idle_1.png");
	selected->position = {0, 0};
	selected->width = 200;
	selected->height = 200;
	selected->pivot = {selected->width/2, selected->height/2};
	scene->addChild(selected);

	Game::addChild(scene);
}

DevTool::~DevTool() {
}

void DevTool::start(){

	int ms_per_frame = (1.0/(double)this->frames_per_sec)*1000;
	std::clock_t start = std::clock();

	bool quit = false;
	SDL_Event event;

	while(!quit){
		std::clock_t end = std::clock();
		double duration = (( end - start ) / (double) CLOCKS_PER_SEC)*1000;
		if(duration > ms_per_frame){
			start = end;
			//this->update(pressedKeys);
			AffineTransform at;
			this->draw(at);
		}

		SDL_PollEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				dragging = true;
				break;
			case SDL_MOUSEBUTTONUP:
				dragging = false;
				selected->position.x -= selected->position.x % scene->gridPixels;
				selected->position.y -= selected->position.y % scene->gridPixels;
				break;
			case SDL_MOUSEMOTION:
				if (dragging) {
					cout << "MOVING" << endl;
					selected->position.x = event.motion.x;
					selected->position.y = event.motion.y;
				}
				break;
		}
	}
}

void DevTool::update(set<SDL_Scancode> pressedKeys){
	Game::update(pressedKeys);
}

void DevTool::draw(AffineTransform &at){
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	Game::draw(at);
}
