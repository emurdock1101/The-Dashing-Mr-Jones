  
#ifndef SCENE_H
#define SCENE_H

#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include "Camera.h"
#include <string>
#include <vector>
#include <fstream>


using namespace std;

class Scene : public DisplayObjectContainer{

public:
	Camera *camera;
	Scene();

	/* Load scene from a file */
	void loadScene(string sceneFilePath);
	void saveScene(string sceneFilePath);

	virtual void update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates);
	virtual void draw(AffineTransform &at);
	void cleanScene();
	vector<DisplayObjectContainer*> inScene;

	int gridPixels = 50;



private:

};

#endif