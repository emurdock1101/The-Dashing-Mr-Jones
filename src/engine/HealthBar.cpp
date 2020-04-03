#include "HealthBar.h"

using namespace std;

HealthBar::HealthBar() : DisplayObjectContainer() {
    this->type = "HealthBar";
}

HealthBar::HealthBar(string id) : DisplayObjectContainer(id, "") {
    this->scaleX = 10;
    this->position = {0, 1000};

    DisplayObjectContainer* heart1 = new DisplayObjectContainer("heart1", "./resources/scenes/UI_DEMO/heart1.png");
    DisplayObjectContainer* heart2 = new DisplayObjectContainer("heart2", "./resources/scenes/UI_DEMO/heart1.png");
    DisplayObjectContainer* heart3 = new DisplayObjectContainer("heart1", "./resources/scenes/UI_DEMO/heart1.png");
    
    heart1->position = {-600, 220};
    heart1->scaleX = .7;
    heart1->scaleY = .7;
    heart2->position = {-525, 220};
    heart2->scaleX = .7;
    heart2->scaleY = .7;
    heart3->position = {-449, 220};
    heart3->scaleX = .7;
    heart3->scaleY = .7;

    this->addChild(heart1);
    this->addChild(heart2);
    this->addChild(heart3);

}

void HealthBar::update(set<SDL_Scancode> pressedKeys, vector<ControllerState*> controllerStates) {

    DisplayObjectContainer::update(pressedKeys, controllerStates);
}

void HealthBar::draw(AffineTransform &at) {
	DisplayObjectContainer::draw(at);
}