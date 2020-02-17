#include "DisplayObjectContainer.h"
#include "Scene.h"
#include "AffineTransform.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Scene::Scene() : DisplayObjectContainer() {
    this->type = "Scene";
}

Scene::~Scene() {
}
