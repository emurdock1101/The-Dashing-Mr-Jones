#include "Scene.h"
#include <iostream>
#include "Sprite.h"
#include "../objects/Mummy.h"
#include "AnimatedSprite.h"
#include "Game.h"
#include "DisplayObjectContainer.h"
#include "AffineTransform.h"
#include "../objects/Player.h"
#include "../objects/CollisionBlock.h"
#include "../objects/RoomChangeBlock.h"
#include <vector>
#include <string>



using namespace std;
//using namespace rapidjason;

Scene::Scene() : DisplayObjectContainer(){
  this->type = "Scene";
  this->camera = new Camera();
}

void Scene::loadScene(string sceneFilePath){
    this->cleanScene();
    ifstream sceneFile;
    sceneFile.open(sceneFilePath);
    string object;
    string line;
    char* pch;

    while(getline(sceneFile, line)){
        vector<string> args;
        object = strtok((char*)line.c_str(), " ");
        pch = strtok(NULL, " ");;
        while(pch != NULL){
            args.push_back(pch);
            pch = strtok(NULL, " ");
        }
		if (args[0].compare("player") == 0) {
			DisplayObjectContainer* temp = new DisplayObjectContainer("player_spawn", args[1]);
			temp->setPos(stoi(args[2]), stoi(args[3]));
			temp->prevPos = temp->position;
			temp->visible = false;
			if (args.size() > 12) {
				for (DisplayObjectContainer* x : inScene) {
					if (x->id.compare(args[12]) == 0)
						x->addChild(temp);
				}
			}
			else {
				addChild((DisplayObjectContainer*)temp);
			}
			inScene.push_back((DisplayObjectContainer*)temp);
		} else
		if (args[0].compare("0") == 0) {
			//id, imgpath, pos.x, pox.y, piv.x, piv.y, scaleX, scaleY, rotation, imgH, imgW, alpha, parents
			CollisionBlock* temp = new CollisionBlock();
			temp->type = object;
			temp->setPos(stoi(args[2]), stoi(args[3]));
			temp->setPiv(stoi(args[4]), stoi(args[5]));
			temp->scaleX = stoi(args[6]);
			temp->scaleY = stoi(args[7]);
			temp->rotation = stoi(args[8]);
			temp->setDim(stoi(args[9]), stoi(args[10]));
			temp->alpha = stoi(args[11]);
			if (args.size() > 13) {
				for (DisplayObjectContainer* x : inScene) {
					if (x->id.compare(args[13]) == 0)
						x->addChild(temp);
				}
			}
			else {
				addChild((DisplayObjectContainer*)temp);
			}
			inScene.push_back((DisplayObjectContainer*)temp);
		} else
		if (args[0].compare("mummy") == 0) {
			//id, pos.x, pox.y, patrolRange, parents
			Mummy* temp = new Mummy(stoi(args[1]), stoi(args[2]));
			temp->type = object;
			temp->patrolRange = stoi(args[3]);
			if (args.size() > 4) {
				for (DisplayObjectContainer* x : inScene) {
					if (x->id.compare(args[4]) == 0)
						x->addChild(temp);
				}
			}
			else {
				addChild((DisplayObjectContainer*)temp);
			}
			inScene.push_back((DisplayObjectContainer*)temp);
		} else
        if(object.compare("DisplayObject") == 0){
            //id, imgpath, pos.x, pox.y, piv.x, piv.y, scaleX, scaleY, rotation, imgH, imgW, alpha, parents
            DisplayObjectContainer* temp = new DisplayObjectContainer(args[0],args[1]);
            temp->type = object;
            temp->setPos(stoi(args[2]),stoi(args[3]));
            temp->setPiv(stoi(args[4]),stoi(args[5]));
            temp->scaleX = stoi(args[6]);
            temp->scaleY = stoi(args[7]);
            temp->rotation = stoi(args[8]);
            temp->setDim(stoi(args[9]),stoi(args[10]));
            temp->alpha = stoi(args[11]);
            if(args.size() > 12){
                for(DisplayObjectContainer* x: inScene){
                    if(x->id.compare(args[12])==0)
                        x->addChild(temp);
                }
            }
            else{
                addChild((DisplayObjectContainer*)temp);
            }
            inScene.push_back((DisplayObjectContainer*)temp);
        }
        else if(object.compare("DisplayObjectContainer") == 0){
            //id, imgpath, pos.x, pox.y, piv.x, piv.y, scaleX, scaleY, rotation, imgH, imgW, alpha, parents
            DisplayObjectContainer* temp = new DisplayObjectContainer(args[0],args[1]);
            temp->type = object;
            temp->setPos(stoi(args[2]),stoi(args[3]));
            temp->setPiv(stoi(args[4]),stoi(args[5]));
            temp->scaleX = stoi(args[6]);
            temp->scaleY = stoi(args[7]);
            temp->rotation = stoi(args[8]);
            temp->setDim(stoi(args[9]),stoi(args[10]));
            temp->alpha = stoi(args[11]);
            if(args.size() > 12){
                for(DisplayObjectContainer* x: inScene){
                    if(x->id.compare(args[12])==0)
                        x->addChild(temp);
                }
            }
            else{
                addChild(temp);
            }
            inScene.push_back(temp);
        }
        else if(object.compare("Sprite") == 0){
            //id, imgpath, pos.x, pox.y, piv.x, piv.y, scaleX, scaleY, rotation, imgH, imgW, alpha, parents
            Sprite* temp = new Sprite(args[0],args[1]);
            temp->type = object;
            temp->setPos(stoi(args[2]),stoi(args[3]));
            temp->setPiv(stoi(args[4]),stoi(args[5]));
            temp->scaleX = stoi(args[6]);
            temp->scaleY = stoi(args[7]);
            temp->rotation = stoi(args[8]);
            temp->setDim(stoi(args[9]),stoi(args[10]));
            temp->alpha = stoi(args[11]);
            if(args.size() > 12){
                for(DisplayObjectContainer* x: inScene){
                    if(x->id.compare(args[12])==0)
                        x->addChild(temp);
                }
            }
            else{
                addChild((DisplayObjectContainer*)temp);
            }
            inScene.push_back((DisplayObjectContainer*)temp);
        }
        else if(object.compare("AnimatedSprite") == 0){
            //id, pos.x, pox.y, piv.x, piv.y, scaleX, scaleY, rotation, imgH, imgW, alpha, numAnim, parent
            AnimatedSprite* temp = new AnimatedSprite(args[0]);
            temp->type = object;
            temp->setPos(stoi(args[1]),stoi(args[2]));
            temp->setPiv(stoi(args[3]),stoi(args[4]));
            temp->scaleX = stoi(args[5]);
            temp->scaleY = stoi(args[6]);
            temp->rotation = stoi(args[7]);
            temp->setDim(stoi(args[8]),stoi(args[9]));
            temp->alpha = stoi(args[10]);
            for(int i = 0; i < stoi(args[11]); i++){
                vector<string> animArgs;
                getline(sceneFile, line);
                pch = strtok((char*)line.c_str(), " ");;
                while(pch != NULL){
                    animArgs.push_back(pch);
                    cout << pch << endl;
                    pch = strtok(NULL, " ");
                }
                bool t = true;
                if(animArgs[4].compare("false")==0)
                    t = false;
                temp->addAnimation(animArgs[0],animArgs[1],stoi(animArgs[2]),stoi(animArgs[3]),t);
                temp->play(animArgs[1]);
            }
            if(args.size() > 12){
                for(DisplayObjectContainer* x: inScene){
                    if(x->id.compare(args[12])==0)
                        x->addChild(temp);
                }
            }
            else{
                addChild((DisplayObjectContainer*)temp);
            }
            inScene.push_back((DisplayObjectContainer*)temp);
        }
		else if (object.compare("RoomChangeBlock") == 0) {
			//id, imgpath, pos.x, pox.y, piv.x, piv.y, scaleX, scaleY, rotation, imgH, imgW, alpha, parents
			RoomChangeBlock* temp = new RoomChangeBlock(args[0]);
			temp->type = object;
			temp->setPos(stoi(args[2]), stoi(args[3]));
			temp->setPiv(stoi(args[4]), stoi(args[5]));
			temp->scaleX = stoi(args[6]);
			temp->scaleY = stoi(args[7]);
			temp->rotation = stoi(args[8]);
			temp->setDim(stoi(args[9]), stoi(args[10]));
			temp->alpha = stoi(args[11]);
			if (args.size() > 12) {
				for (DisplayObjectContainer* x : inScene) {
					if (x->id.compare(args[12]) == 0)
						x->addChild(temp);
				}
			}
			else {
				addChild((DisplayObjectContainer*)temp);
			}
			inScene.push_back((DisplayObjectContainer*)temp);
		}
    }
}

void Scene::saveScene(string sceneFilePath) {
    ofstream sceneFile;
    sceneFile.open(sceneFilePath, ofstream::out | ofstream::trunc);
	for (DisplayObject *child: children) {
		child->writeSceneData(sceneFile);
	}
	sceneFile.close();
}

void Scene::cleanScene(){
	inScene.clear();
	// TODO: Add a loop which deletes children objects
	for (DisplayObject *child : children) {
		Event newEvent(EventParams::DISPLAY_OBJECT_REMOVED, child);
		Game::instance->dispatchEvent(&newEvent);
		delete child;
	}
	children.clear();
}
void Scene::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates){
	DisplayObjectContainer::update(pressedKeys, controllerStates);
}
void Scene::draw(AffineTransform &at){
	at.scale(camera->scaleX, camera->scaleY);
	at.translate(-camera->x, -camera->y);
	// SDL_RenderDrawPoint(Game::renderer, at.transformPoint(0, 0).x, at.transformPoint(0, 0).y);
	DisplayObjectContainer::draw(at);
	at.translate(camera->x, camera->y);
	at.scale(1.0/camera->scaleX, 1.0/camera->scaleY);
}
