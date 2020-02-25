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
#include <experimental/filesystem>
#include <vector> 
#include <algorithm>

using namespace std;
namespace fs = std::experimental::filesystem;
DevTool::DevTool() : Game(1200, 1000) {
	scene = new Scene();
	selected = new Sprite();
	//selected->position = {50, 50};
	//selected->width = 100;
	//selected->height = 100;
	//selected->pivot = {selected->width/2, selected->height/2};
	//scene->addChild(selected);

	selectionArea = new Sprite("selection_area", 0, 0, 0);


	vector<string> images = getImagesFromFolder("./resources");
	sort(images.begin(), images.end());

	int count = 0;
	for (string image : images){
		//cout << image << endl;
		Sprite* temp = new Sprite(to_string(count), image);
		spritesToDisplay.push_back(temp);
		count++;
	}

	int x = 50;
	for (Sprite* sprite : spritesToDisplay){
		sprite->position = {x, 0};
		sprite->width = 100;
		sprite->height = 100;
		selectionArea->addChild(sprite);
		x += 100;
	}


	Game::addChild(selectionArea);
	Game::addChild(scene);

}


DevTool::~DevTool() {
	
}

void DevTool::start(){
	//getImagesFromFolder("./resources/character");
	int ms_per_frame = (1.0/(double)this->frames_per_sec)*10000;
	std::clock_t start = std::clock();

	bool quit = false;
	SDL_Event event;

	while(!quit){
		int count = 0;
		std::clock_t end = std::clock();
		double duration = (( end - start ) / (double) CLOCKS_PER_SEC)*100000;
		if(duration > ms_per_frame){
			start = end;
			this->update(pressedKeys);
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
			count = 0;
				for (Sprite* sprite : spritesToDisplay){
					
					if (event.motion.x - selectionArea->position.x <= sprite->position.x+100 && event.motion.x - selectionArea->position.x >= sprite->position.x && 
						event.motion.y <= sprite->position.y+100 && event.motion.y >= sprite->position.y){
						if (selectionArea->getChild(to_string(count)) != NULL){
							selected = sprite;
							scene->addChild(selected);
							selectionArea->removeImmediateChild(sprite);
							dragging = true;
						}
						else if (scene->getChild(to_string(count)) != NULL){
							dragging = true;
							selected = sprite;
						}
					}
				count++;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (dragging){
					
					selected->position.x -= selected->position.x % scene->gridPixels;
					selected->position.y -= selected->position.y % scene->gridPixels;
					selected->pivot = {0,0};
					dragging = false;
				}
				break;
			case SDL_MOUSEMOTION:
				if (dragging) {
					//cout << "MOVING" << endl
					selected->position.x = event.motion.x;
					selected->position.y = event.motion.y;
					selected->pivot = {selected->width/2, selected->height/2};
				}
			case SDL_KEYDOWN:
				pressedKeys.insert(event.key.keysym.scancode);
				break;
			case SDL_KEYUP:
				pressedKeys.erase(event.key.keysym.scancode);
				break;

		}
	}
}
////https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
vector<string>DevTool::getImagesFromFolder(string folderName){
	vector<string> images = {};
	for (const auto &file: fs::directory_iterator(folderName)){
		string temp = file.path();
		if (temp.find(".png") != std::string::npos){ //find each image in the main directory
			images.push_back(file.path());
		}
		//Go through each sub-directory and find those images too
		else if (!(temp.substr(1).find(".") != std::string::npos)){
			for (const auto &fileInSubFolder : fs::directory_iterator(temp)){
				string temp = fileInSubFolder.path();
				if (temp.find(".png") != std::string::npos){
					images.push_back(fileInSubFolder.path());
				}
			}
		}
	}
	return images;
}

void DevTool::update(set<SDL_Scancode> pressedKeys){
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		selectionArea->position.x -= 5;
	}

	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()&& selectionArea->position.x != 0) {
		selectionArea->position.x += 5;
	}
	Game::update(pressedKeys);
	
}

void DevTool::draw(AffineTransform &at){
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	Game::draw(at);
}
