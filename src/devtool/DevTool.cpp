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
#include <filesystem>
#include <vector> 

using namespace std;
namespace fs = std::__fs::filesystem;
DevTool::DevTool() : Game(1200, 1000) {
	scene = new Scene();
	selected = new Sprite("character","./resources/character/Idle_1.png");
	selected->position = {0, 0};
	selected->width = 200;
	selected->height = 200;
	selected->pivot = {selected->width/2, selected->height/2};
	scene->addChild(selected);

	Game::addChild(scene);

	vector<string> images = getImagesFromFolder("./resources");
	for (string image : images){
		cout << image << endl;
	}


}

DevTool::~DevTool() {
}

void DevTool::start(){
	//getImagesFromFolder("./resources/character");
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

////https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
vector<string>DevTool::getImagesFromFolder(string folderName){
	vector<string> images = {};
	for (const auto &file: fs::directory_iterator(folderName)){
		string temp = file.path();
		if (temp.find(".png") != std::string::npos){ //find each image in the main directory
			images.push_back(file.path());
		}
		//Go through each sub-directory and find those images
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
	Game::update(pressedKeys);
}

void DevTool::draw(AffineTransform &at){
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	Game::draw(at);
}
