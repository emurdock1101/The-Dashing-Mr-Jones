#include <iostream>
#include <algorithm>
#include "DevTool.h"
#include <string>
#include "../objects/Player.h"
#include "../objects/CollisionBlock.h"
#include <ctime>
#include "../engine/Game.h"
#include "../engine/Scene.h"
#include "../engine/Sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <dirent.h> 
#endif
#include <vector>
#include <algorithm>
#include "../engine/AnimatedSprite.h"

using namespace std;
vector<string> images;

DevTool::DevTool() : Game(1200, 1000) {
	scene = new Scene();

	selectionArea = new Sprite("selection_area", 0, 0, 0);
	blueBar = new Sprite("blue_bar", 0,0,255);
	blueBar->height = 100;
	blueBar->width = 1400;

	images = getImagesFromFolder("./resources");
	
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

	Game::addChild(scene);
	Game::addChild(blueBar);
	Game::addChild(menus);
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
			this->update(pressedKeys, controllerStates);
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
						if (isHoveredSelectBar(sprite, event)) {
							DisplayObjectContainer *tmp = new DisplayObjectContainer();
							sprite->cachedTransform = NULL;
							sprite->invalidateCache = true;
							*tmp = *sprite;
							selected = tmp;
							selected->loadTexture(selected->imgPath);
							scene->addChild(selected);
							onScreen.push_back(selected);
							dragging = true;
							lastMousePos = { event.motion.x, event.motion.y };
							break;
						}
					}
					
					for (int i = this->onScreen.size() - 1; i >= 0; i--) { // go backwards so things drawn on top get selected first
						DisplayObjectContainer* sprite = onScreen[i];
						if (isHoveredScene(sprite, event) && makeChild == true){
							cout << sprite->imgPath << " is now a child of " << selected->imgPath << endl;
							selected->addChild(sprite);
							sprite->position.x -= selected->position.x;
							sprite->position.y -= selected->position.y;
							scene->removeImmediateChild(sprite);
							makeChild = false;
							break;
						}
						if (isHoveredScene(sprite, event)) {
							dragging = true;
							lastMousePos = { event.motion.x, event.motion.y };
							selected = sprite;
							// Remove/add child so it's top of display tree (if it's a direct child of scene)
							if (find(scene->children.begin(), scene->children.end(), sprite) != scene->children.end()){
								// scene->removeImmediateChild(selected);
								// scene->addChild(selected);
							}
							break;
						}
			
					}
				}
				
				count++;
				break;
			case SDL_MOUSEBUTTONUP:
				if (dragging){
					if (selected->position.x > 0) {
						selected->position.x = (selected->position.x + gridPixels / 2) / gridPixels * gridPixels;
					}
					else {
						selected->position.x = (selected->position.x - gridPixels / 2) / gridPixels * gridPixels;
					}
					if (selected->position.y > 0) {
						selected->position.y = (selected->position.y + gridPixels / 2) / gridPixels * gridPixels;
					}
					else {
						selected->position.y = (selected->position.y - gridPixels / 2) / gridPixels * gridPixels;
					}
					
					//selected->pivot = {0,0};
					dragging = false;
				}
				break;
			case SDL_MOUSEMOTION:
				if (dragging) {
					// SDL_Point absolutePos = selected->getTopLeft();
					selected->position.x = (event.motion.x- lastMousePos.x) + selected->position.x;
					selected->position.y = (event.motion.y- lastMousePos.y) + selected->position.y;
					lastMousePos.x = event.motion.x;
					lastMousePos.y = event.motion.y;
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
//Helpful source: 
//http://www.martinbroadhurst.com/list-the-files-in-a-directory-in-c.html
vector<string>DevTool::getImagesFromFolder(string folderName){
	vector<string> temp; 
	
	struct dirent *directory;
#ifdef _WIN32
	std::string pattern(folderName);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			string file = string(data.cFileName);
			if ((file.find(".png") != std::string::npos)) {
				//cout << directory->d_name << endl;
				temp.push_back(folderName + "/" + data.cFileName);
			}
			if (!((file.find(".") != std::string::npos))) {
				//cout << directory -> d_name << endl;
				getImagesFromFolder(folderName + "/" + data.cFileName);
			}
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
#else
	DIR* dirp;
	dirp = opendir(folderName.c_str());

	   if (dirp) {
        while ((directory = readdir(dirp)) != NULL){
          //cout << directory->d_name << endl;
          string file = string(directory->d_name);
          if ((file.find(".png") != std::string::npos)){
          	//cout << directory->d_name << endl;
          	temp.push_back(folderName + "/" + directory->d_name);
          }
          if (!((file.find(".") != std::string::npos))){
            //cout << directory -> d_name << endl;
          	getImagesFromFolder(folderName + "/" + directory->d_name);
		}
       }
        closedir(dirp);
    }
#endif

    for (string image: temp){
    	images.push_back(image);
    }


    return images;
}

void DevTool::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){
	string filename;
	for (SDL_Scancode scancode: pressedKeys) {
		switch(scancode) {
			case SDL_SCANCODE_UP:
				scene->camera->y -= 3;
				break;
			case SDL_SCANCODE_DOWN:
				scene->camera->y += 3;
				break;
			case SDL_SCANCODE_LEFT:
				scene->camera->x -= 3;
				break;
			case SDL_SCANCODE_RIGHT:
				scene->camera->x += 3;
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
				for (DisplayObjectContainer* child : scene->children){
					if (child->id == "player"){
						child->inDevtool = true;
					}
					onScreen.push_back(child);
				}
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
			case SDL_SCANCODE_O: {
				cout << "Add an object" << endl;
				cout << "Be sure to use all lowercase or only first letter upper" << endl;
				cout << "Press n to refuse" << endl;
				string objectType;
				cin >> objectType;
				// To add an object:
				// Add another else if statement with what you want to type
				// Set parameters like Player
				// Be sure to set inDevtool and make sure the object
				// does not update physics if that's true!
				// Add to scene and to onScreen
				// Be sure to add capabilities in the object for saving scene
				// with a writeSceneData method and for loading scene in Scene.cpp
				if (objectType == "player" || objectType == "Player") {
					Player* temp = new Player("player");
					temp->position = {100, 100};
					// TODO: fix pivot
					temp->pivot = {0, 0};
					temp->inDevtool = true;
					temp->showHitbox = false;
					scene->addChild(temp);
					onScreen.push_back(temp);
				}
				else if (objectType == "n") {
					cout << "Aborting" << endl;
					break;
				}
				else {
					cout << "Object type not found!" << endl;
					cout << "Aborting" << endl;
				}
				break;
			}
			case SDL_SCANCODE_A:
			{

				cout << "Animated Sprite Creator:" << endl << "Fill out the following fields:" << endl;
				cout << "Enter the id: ";
				string id;
				cin >> id; 
				AnimatedSprite* temp = new AnimatedSprite(id);
				temp->position.x = 100;
				temp->position.y = 100;
				scene->addChild(temp);
				onScreen.push_back(temp);

				//Add animations
				cout << "Add Your Animations:" << endl;
				bool animationAdder = true;
				while(animationAdder == true){
					cout << "Enter the basepath: ";
					string basepath;
					cin >> basepath;
					cout << "Enter the name of the Animation: ";
					string animName;
					cin >> animName;
					cout << "Enter the number of frames: ";
					string numFrames;
					cin >> numFrames;
					cout << "Enter the framerate: ";
					string frameRate;
					cin >> frameRate;
					temp->addAnimation(basepath, animName, stoi(numFrames), stoi(frameRate), true); 
					temp->position.x = 100;
					temp->position.y = 100;
					temp->play(animName);
					cout << "Would you like to add another animation? y/n" << endl;
					string yesno;
					cin >> yesno;
					if (yesno == "n"){
						animationAdder = false;
					}
				}
				
				/*AnimatedSprite* temp = new AnimatedSprite("test");
				temp->addAnimation("./resources/character/", "Idle", 20, 100, true);
				temp->play("Idle");
				temp->position.x = 100;
				temp->position.y = 100;
				scene->addChild(temp);
				onScreen.push_back(temp);*/
				break;
			}
			/*
			// Gridpixels changing code
			case SDL_SCANCODE_H:
				gridPixels += 5;
				scene->camera->scaleX += 0.1;
				scene->camera->scaleY += 0.1;
				if (selected != NULL) {
					selected->position.x -= selected->position.x % gridPixels;
					selected->position.y -= selected->position.y % gridPixels;
				}
				break;
			case SDL_SCANCODE_J:
				gridPixels -= 5;
				scene->camera->scaleX -= 0.1;
				scene->camera->scaleY -= 0.1;
				if (selected != NULL) {
					selected->position.x = selected->position.x - (selected->position.x % gridPixels) + gridPixels;
					selected->position.y = selected->position.y - (selected->position.y % gridPixels) + gridPixels;
				}
				break;*/
			// Delete
			case SDL_SCANCODE_BACKSPACE:
				// Delete
				if (selected != NULL) {
					cout << "Deleting " << selected->id << endl;
					cout << "Parent " << selected->parent->id << endl;
					selected->removeThis();
					// Delete from onScreen
					for (int i = 0; i < onScreen.size(); i++) {
						if (onScreen[i] == selected) {
							cout << "DELETING from on screen" << selected->id << endl;
							onScreen.erase(onScreen.begin() + i);
							cout << "Deleted from on screen" << selected->id << endl;
							break;
						}
					}
					delete selected;
					cout << "SETTING NULL" << endl;
					selected = NULL;
					cout << "BREAKING" << endl;
					
				}
				break;
			case SDL_SCANCODE_C:
				// Copy
				if (selected != NULL) {
					copied = new DisplayObjectContainer;
					*copied = *selected;
				}
				break;
			case SDL_SCANCODE_V:
			{
				// Paste
				DisplayObjectContainer *tmp = new DisplayObjectContainer;
				*tmp = *copied;
				tmp->cachedTransform = NULL;
				tmp->invalidateCache = true;
				tmp->position.x += 50;
				tmp->position.y += 50;
				scene->addChild(tmp);
				onScreen.push_back(tmp);
				spritesToDisplay.push_back(tmp);
				break;
			}
			case SDL_SCANCODE_B:
			{
				DisplayObjectContainer *tmp = new CollisionBlock;

				tmp->cachedTransform = NULL;
				tmp->invalidateCache = true;
				tmp->position.x = lastMousePos.x + scene->camera->x;
				tmp->position.y = lastMousePos.y + scene->camera->y;
				scene->addChild(tmp);
				onScreen.push_back(tmp);
				spritesToDisplay.push_back(tmp);
				break;
			}
		}
	}
	singleUseKeys.clear();
	Game::update(pressedKeys, controllerStates);
}

void DevTool::draw(AffineTransform &at){
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::renderer);
	DisplayObjectContainer::draw(at);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (int y = -scene->camera->y % gridPixels; y < 1000; y += gridPixels) {
		SDL_RenderDrawLine(Game::renderer, 0, y, windowWidth, y);
	}
	for (int x = -scene->camera->x % gridPixels; x < 1200; x += gridPixels) {
		SDL_RenderDrawLine(Game::renderer, x, 0, x, windowHeight);
	}
	// Draw red rectangle around selected sprite
    SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	if (selected != NULL) {
		SDL_Point topLeft = selected->getTopLeft();
		SDL_Point topRight = selected->getTopRight();
		SDL_Point bottomLeft = selected->getBottomLeft();
		SDL_Point bottomRight = selected->getBottomRight();
		topLeft.x -= scene->camera->x;
		topLeft.y -= scene->camera->y;
		topRight.x -= scene->camera->x;
		topRight.y -= scene->camera->y;
		bottomLeft.x -= scene->camera->x;
		bottomLeft.y -= scene->camera->y;
		bottomRight.x -= scene->camera->x;
		bottomRight.y -= scene->camera->y;
		SDL_RenderDrawLine(Game::renderer,
				topLeft.x,
				topLeft.y,
				topRight.x,
				topRight.y);
		SDL_RenderDrawLine(Game::renderer,
				topLeft.x,
				topLeft.y,
				bottomLeft.x,
				bottomLeft.y);
		SDL_RenderDrawLine(Game::renderer,
				topRight.x,
				topRight.y,
				bottomRight.x,
				bottomRight.y);
		SDL_RenderDrawLine(Game::renderer,
				bottomLeft.x,
				bottomLeft.y,
				bottomRight.x,
				bottomRight.y);
	}
	SDL_RenderPresent(Game::renderer);
}

bool DevTool::isHoveredSelectBar(DisplayObject *obj, SDL_Event event) {
	return obj->isColliding(NULL, event.motion.x, event.motion.y);
}

bool DevTool::isHoveredScene(DisplayObject *obj, SDL_Event event) {
	return obj->isColliding(scene->camera, event.motion.x, event.motion.y);
}

void DevTool::editPrompt() {
	cout << "Welcome to the Sprite Editor" << endl;
	//id, imgpath, pos.x, pox.y, piv.x, piv.y, scaleX, scaleY, rotation, imgH, imgW, alpha, parents
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

	cout << "Change id from " << selected->id << " to: ";
	string id;
	cin >> id;
	if (!(id == "n")){
		selected->id = id;
	}
	cout << "Rotation is now " << selected->id << endl;

	cout << "__________________________________________________" << endl;

	if (selected->type == "AnimatedSprite"){
		cout << "Change sprite animation to: ";
		string newAnim; 
		cin >> newAnim; 
		if (newAnim != "n"){
			((AnimatedSprite*)selected)->play(newAnim);
		}
		
		cout << "Play or Stop animation? (Enter p or s)" << endl;
		string playstop;
		cin >> playstop;
		if (playstop != "n"){
			if (playstop == "p"){
				((AnimatedSprite*)selected)->playing = true;
				((AnimatedSprite*)selected)->replay();
			}
			if (playstop == "s"){
				((AnimatedSprite*)selected)->playing = false;
				((AnimatedSprite*)selected)->stop();
			}
		}
	}
}
		


