#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "DisplayObject.h"
#include "AffineTransform.h"
// #include "Event.h"
#include <string>
#include <fstream>

using namespace std;

class Scene : public DisplayObjectContainer {

public:
    Scene();
	virtual ~Scene();

    //void loadScene(string path);
    //void saveScene(string path);

	vector<DisplayObject*> children;
private:
};

#endif
