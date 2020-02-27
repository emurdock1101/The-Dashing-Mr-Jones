#ifndef SCENE_H
#define SCENE_H

#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include <string>
#include <vector>
#include <fstream>


using namespace std;

class Scene : public DisplayObjectContainer{

public:
	Scene();

	/* Load scene from a file */
	void loadScene(string sceneFilePath);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	void cleanScene();
	vector<DisplayObjectContainer*> inScene;
	vector<DisplayObjectContainer*> drawable;
	DisplayObjectContainer* getObj(string id);

	int gridPixels = 50;



private:

};

#endif
