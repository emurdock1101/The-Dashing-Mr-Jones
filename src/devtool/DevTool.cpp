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
	blueBar->width = 1400;

	vector<string> images = getImagesFromFolder("./resources");
	sort(images.begin(), images.end());

	int count = 0;
	for (string image : images){
		DisplayObjectContainer* temp = new DisplayObjectContainer(to_string(count), image);
		spritesToDisplay.push_back(temp);
		count++;
	}

	int x = 50;
	for (DisplayObjectContainer* sprite : spritesToDisplay){
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
					for (DisplayObjectContainer *sprite: selectionArea->children) {
						if (isHovered(sprite, event)) {
							DisplayObjectContainer *tmp = new DisplayObjectContainer();
							*tmp = *sprite;
							selected = tmp;
							scene->addChild(selected);
							onScreen.push_back(selected);
							dragging = true;
							break;
						}
					}
					for (DisplayObjectContainer *sprite: this->onScreen) {
						if (isHovered(sprite, event) && makeChild == true){
							cout << sprite->imgPath << " is now a child of " << selected->imgPath << endl;
							selected->addChild(sprite);
							scene->removeImmediateChild(sprite);
							makeChild = false;
						}
						if (isHovered(sprite, event)) {
							dragging = true;
							selected = sprite;
							// Remove/add child so it's top of display tree (if it's a direct child of scene)
							if (find(scene->children.begin(), scene->children.end(), sprite) != scene->children.end()){
								scene->removeImmediateChild(selected);
								scene->addChild(selected);
							}
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
					//selected->pivot = {0,0};
					dragging = false;
				}
				break;
			case SDL_MOUSEMOTION:
				if (dragging) {
					selected->position.x = event.motion.x;
					selected->position.y = event.motion.y;
					//selected->pivot = {selected->width/2, selected->height/2};
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
			case SDL_SCANCODE_UP:
				scene->camera->y -= 6;
				break;
			case SDL_SCANCODE_DOWN:
				scene->camera->y += 6;
				break;
			case SDL_SCANCODE_LEFT:
				scene->camera->x -= 6;
				break;
			case SDL_SCANCODE_RIGHT:
				scene->camera->x += 6;
				break;
			case SDL_SCANCODE_Q:
				selectionArea->position.x -= 5;
				break;
			case SDL_SCANCODE_W:
				if (selectionArea->position.x != 0) {
					selectionArea->position.x += 5;
				}
				break;
		}
	}
	for (SDL_Scancode scancode: singleUseKeys) {
		switch(scancode) {
			case SDL_SCANCODE_LCTRL:
				makeChild = true;
				break;
			case SDL_SCANCODE_L:
				cout << "Please enter a filepath to load a scene:" << endl;
				cin >> filename;
				cout << "Loading scene " << filename << endl;
				scene->loadScene(filename);
				selected = NULL;
				copied = NULL;
				cout << "Loaded scene " << filename << endl;
				break;
			case SDL_SCANCODE_S:
				cout << "Please enter a filepath to save the scene:" << endl;
				cin >> filename;
				cout << "Saving scene to " << filename << endl;
				scene->saveScene(filename);
				cout << "Saved scene to " << filename << endl;
				break;
			case SDL_SCANCODE_E:
				if (selected != NULL) {
					editPrompt();
				}
				break;
			case SDL_SCANCODE_C:
				// Copy
				copied = new DisplayObjectContainer;
				*copied = *selected;
				break;
			case SDL_SCANCODE_V:
				// Paste
				DisplayObjectContainer *tmp = new DisplayObjectContainer;
				*tmp = *copied;
				tmp->position.x += 50;
				tmp->position.y += 50;
				scene->addChild(tmp);
				onScreen.push_back(tmp);
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
		SDL_RenderDrawLine(Game::renderer, 0, y, windowWidth, y);
	}
	for (int x = 0; x < 1200; x += gridPixels) {
		SDL_RenderDrawLine(Game::renderer, x, 0, x, windowHeight);
	}
	// Draw red rectangle around selected sprite
	// TODO: Draw box based on AffineTransform instead
    SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	if (selected != NULL) {
		SDL_RenderDrawLine(Game::renderer,
				selected->position.x,
				selected->position.y,
				selected->position.x + selected->getAbsoluteWidth(),
				selected->position.y);
		SDL_RenderDrawLine(Game::renderer,
				selected->position.x,
				selected->position.y,
				selected->position.x,
				selected->position.y + selected->getAbsoluteHeight());
		SDL_RenderDrawLine(Game::renderer,
				selected->position.x,
				selected->position.y + selected->getAbsoluteHeight(),
				selected->position.x + selected->getAbsoluteWidth(),
				selected->position.y + selected->getAbsoluteHeight());
		SDL_RenderDrawLine(Game::renderer,
				selected->position.x + selected->getAbsoluteWidth(),
				selected->position.y,
				selected->position.x + selected->getAbsoluteWidth(),
				selected->position.y + selected->getAbsoluteHeight());
	}
	SDL_RenderPresent(Game::renderer);
}

bool DevTool::isHovered(DisplayObject *obj, SDL_Event event) {
	return obj->isColliding(event.motion.x, event.motion.y);
}

void DevTool::editPrompt() {
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
}
