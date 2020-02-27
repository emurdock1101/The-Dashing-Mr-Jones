#include "Scene.h"
#include <iostream>
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Game.h"
#include "DisplayObjectContainer.h"
#include "AffineTransform.h"
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
        if(object.compare("DisplayObject") == 0){
            //id, imgpath, pos.x, pox.y, piv.x, piv.y, scaleX, scaleY, rotation, imgH, imgW, alpha, parents
            DisplayObject* temp = new DisplayObject(args[0],args[1]);
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
                    //cout << pch << endl;
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
    }
}

void Scene::saveScene(string sceneFilePath) {
    ofstream sceneFile;
    sceneFile.open(sceneFilePath, ofstream::out | ofstream::app);
	for (DisplayObject *child: children) {
		child->writeSceneData(sceneFile);
	}
	sceneFile.close();
}

void Scene::cleanScene(){
	inScene.clear();
	children.clear();
}
void Scene::update(set<SDL_Scancode> pressedKeys){
	DisplayObjectContainer::update(pressedKeys);
}
void Scene::draw(AffineTransform &at){
	at.scale(camera->scaleX, camera->scaleY);
	at.translate(camera->x, camera->y);
	DisplayObjectContainer::draw(at);
}
