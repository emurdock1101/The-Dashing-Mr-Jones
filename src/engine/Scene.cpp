#include "Scene.h"
#include <iostream>


using namespace std;
//using namespace rapidjason;

Scene::Scene() : DisplayObjectContainer(){

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
            //id, imgpath, pos.x, pox.y, piv.x, piv.y, scaleX, scaleY, rotation, imgH, imgW .... parents
            DisplayObject* temp = new DisplayObject(args[0],args[1]);
            temp->setPos(stoi(args[2]),stoi(args[3]));
            temp->setPiv(stoi(args[4]),stoi(args[5]));
            temp->scaleX = stoi(args[6]);
            temp->scaleY = stoi(args[7]);
            temp->rotation = stoi(args[8]);
            temp->setDim(stoi(args[9]),stoi(args[10]));
            // for(DisplayObjectContainer* x: allofmyshit){
            //     if(x->id.compare(args[11])==0)
            //         x->addChild(temp);
            // }
            inScene.push_back((DisplayObjectContainer*)temp);
        }
        else if(object.compare("DisplayObjectContainer") == 0){

        }
        else if(object.compare("Sprite") == 0){

        }
        else if(object.compare("AnimatedSprite") == 0){

        }
    }
}
void Scene::cleanScene(){
    for(int i = inScene.size()-1; i >= 0; i --){
        DisplayObjectContainer* temp = inScene[i];
        inScene.pop_back();
        delete temp;

    }
}
void Scene::update(set<SDL_Scancode> pressedKeys){

}
void Scene::draw(AffineTransform &at){
    for(DisplayObjectContainer* x: inScene){
        x->draw(at);
    }
}
