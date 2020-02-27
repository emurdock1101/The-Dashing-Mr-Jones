#include <iostream>
#include <algorithm>
#include "DevTool.h"
#include <string>
#include <ctime>
#include "Game.h"
#include "Scene.h"
#include "Sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <experimental/filesystem>
#include <vector>
#include <algorithm>

using namespace std;
namespace fs = std::experimental::filesystem;

DevTool::DevTool() : Game(1200, 1000) {
	scene = new Scene();

	selectionArea = new Sprite("selection_area", 0, 0, 0);
	blueBar = new Sprite("blue_bar", 0,0,255);
	blueBar->height = 100;
	blueBar->width = 1200;

	vector<string> images = getImagesFromFolder("./resources");
	sort(images.begin(), images.end());

	int count = 0;
	for (string image : images){
		DisplayObject* temp = new DisplayObject(to_string(count), image);
		spritesToDisplay.push_back(temp);
		count++;
	}

	int x = 50;
	for (DisplayObject* sprite : spritesToDisplay){
		sprite->position = {x, 0};
		sprite->width = 100;
		sprite->height = 100;
		selectionArea->addChild(sprite);
		x += 100;
	}

	menus = new DisplayObjectContainer();
	menus->addChild(selectionArea);

	Game::addChild(blueBar);
	Game::addChild(menus);
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
				if (!dragging) {
					for (DisplayObject *sprite: selectionArea->children) {
						if (isHovered(sprite, event)) {
							DisplayObject *tmp = new DisplayObject();
							*tmp = *sprite;
							selected = tmp;
							scene->addChild(selected);
							dragging = true;
							break;
						}
					}
					for (DisplayObject *sprite: scene->children) {
						if (isHovered(sprite, event)) {
							dragging = true;
							selected = sprite;
							// Remove/add child so it's top of display tree
							scene->removeImmediateChild(selected);
							scene->addChild(selected);
							break;
						}
					}
				}

				count++;
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
					selected->position.x = event.motion.x;
					selected->position.y = event.motion.y;
					selected->pivot = {selected->width/2, selected->height/2};
				}
				break;
			case SDL_KEYDOWN:
				pressedKeys.insert(event.key.keysym.scancode);
				singleUseKeys.insert(event.key.keysym.scancode);
				break;
			case SDL_KEYUP:
				pressedKeys.erase(event.key.keysym.scancode);
				singleUseKeys.erase(event.key.keysym.scancode);
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
	string filename;
	for (SDL_Scancode scancode: pressedKeys) {
		switch(scancode) {
			case SDL_SCANCODE_LEFT:
				selectionArea->position.x -= 5;
				break;
			case SDL_SCANCODE_RIGHT:
				if (selectionArea->position.x != 0) {
					selectionArea->position.x += 5;
				}
				break;
		}
	}
	for (SDL_Scancode scancode: singleUseKeys) {
		switch(scancode) {
			case SDL_SCANCODE_L:
				cout << "Please enter a filepath to load a scene:" << endl;
				cin >> filename;
				scene->loadScene(filename);
				for (DisplayObject* sprite: scene->drawable){
					scene->addChild(sprite);
				}
				break;
			case SDL_SCANCODE_E:
				cout << "Welcome to the Sprite Editor" << endl;
				//id, imgpath, pos.x, pox.y, piv.x, piv.y, scaleX, scaleY, rotation, imgH, imgW, alpha, parents
				if (selected->type == "DisplayObject" || selected->type == "DisplayObjectContainer" || selected->type == "Sprite"){
					cout << "Editing " << selected->imgPath << endl;
					cout << "Change Scale X from " << selected->scaleX << " to: ";
					string scaleX;
					cin >> scaleX;
					if (!(scaleX == "n")){
						selected->scaleX = stoi(scaleX);
					}
					cout << "Scale X is now " << selected->scaleX << endl;

					cout << "__________________________________________________" << endl;

					cout << "Change Scale Y from " << selected->scaleY << " to: ";
					string scaleY;
					cin >> scaleY;
					if (!(scaleY == "n")){
						selected->scaleY = stoi(scaleY);
					}
					cout << "Scale Y is now " << selected->scaleY << endl;

					cout << "__________________________________________________" << endl;
					cout << "Change Pivot X from " << selected->pivot.x << " to: ";
					string pivX;
					cin >> pivX;
					if (!(pivX == "n")){
						selected->pivot.x = stoi(pivX);
					}
					cout << "Pivot X is now " << selected->pivot.x << endl;

					cout << "__________________________________________________" << endl;

					cout << "Change Pivot Y from " << selected->pivot.y << " to: ";
					string pivY;
					cin >> pivY;
					if (!(pivY == "n")){
						selected->pivot.y = stoi(pivY);
					}
					cout << "Pivot Y is now " << selected->pivot.y << endl;

					cout << "__________________________________________________" << endl;

					cout << "Change Rotation from " << selected->rotation << " to: ";
					string rot;
					cin >> rot;
					if (!(rot == "n")){
						selected->rotation = stoi(rot);
					}
					cout << "Rotation is now " << selected->rotation << endl;

					cout << "__________________________________________________" << endl;

					
				}
				break;
			case SDL_SCANCODE_C:
				// Copy
				copied = new DisplayObject;
				*copied = *selected;
				break;
			case SDL_SCANCODE_V:
				// Paste
				DisplayObject *tmp = new DisplayObject;
				*tmp = *copied;
				tmp->position.x += 50;
				tmp->position.y += 50;
				scene->addChild(tmp);
				spritesToDisplay.push_back(tmp);
				break;
		}
	}
	singleUseKeys.clear();
	Game::update(pressedKeys);
}

void DevTool::draw(AffineTransform &at){
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::renderer);
	DisplayObjectContainer::draw(at);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (int y = 0; y < 1000; y += gridPixels) {
		SDL_RenderDrawLine(Game::renderer, 0, y, 1200, y);
	}
	for (int x = 0; x < 1200; x += gridPixels) {
		SDL_RenderDrawLine(Game::renderer, x, 0, x, 1000);
	}
	SDL_RenderPresent(Game::renderer);
}
bool DevTool::isHovered(DisplayObject *obj, SDL_Event event) {
	return obj->isColliding(event.motion.x, event.motion.y);
}
