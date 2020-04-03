#include "Menu.h"
#include "Text.h"

using namespace std;

Menu::Menu() : DisplayObjectContainer() { 
    this->type = "Menu";
}

Menu::Menu(string id) : DisplayObjectContainer(id, "./resources/objects/rectangle.png") {
    this->scaleX = 5;
    this->scaleY = 3;
    this->alpha = 255;
    this->position = {-600,-300};

    outline = new DisplayObjectContainer("select", "./resources/objects/outline.png");
    outline->scaleY = .5;
    outline->position.y = 10; 

    this->addChild((DisplayObjectContainer*) new Text("./resources/Carnevalee Freakshow.ttf", 50, {0,0,0}, "Menu", 200, 0));
	this->addChild((DisplayObjectContainer*) new Text("./resources/Carnevalee Freakshow.ttf", 30, {0,0,0}, "Settings", 200, 100));
	this->addChild((DisplayObjectContainer*) new Text("./resources/Carnevalee Freakshow.ttf", 30, {0,0,0}, "Exit", 200, 200));
    this->addChild(outline);

}

void Menu::update(set<SDL_Scancode> pressedKeys, vector<ControllerState*> controllerStates) {

    if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
        outline->position.y = 10;
    }
    if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
        outline->position.y = 50;
    }
    if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
        if (outline->position.y == 10) {
            
        }
        if (outline->position.y == 50) {
            
        }
    }

    DisplayObjectContainer::update(pressedKeys, controllerStates);
}

void Menu::draw(AffineTransform &at) {
	DisplayObjectContainer::draw(at);
}