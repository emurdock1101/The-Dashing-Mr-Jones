#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "Sprite.h"
#include "MyGame.h"
#include "Sound.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	instance = this;

	allSprites = new DisplayObjectContainer();
	// move that point to the middle
	allSprites->position = {600, 500};
	//instance->addChild(allSprites);
	
	//loads DisplayObjects from scene text files
	sc = new Scene();
	sc->loadScene("./resources/scenes/Scene1.txt");
	instance->addChild(sc);

	//plays background music upon launch
	sound = new Sound();
	sound->playMusic("./resources/sounds/boss.ogg");
}

MyGame::~MyGame(){
}

void MyGame::update(set<SDL_Scancode> pressedKeys){
	
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {//press P to switch scene
		if(t){
			sc->loadScene("./resources/scenes/Scene2.txt");
			t = false;
		}
		else{
			sc->loadScene("./resources/scenes/Scene1.txt");
			t = true;
		}
	}

	if (pressedKeys.find(SDL_SCANCODE_G) != pressedKeys.end()) {//press G to play sound
		sound->playSFX("./resources/sounds/TORYAH.wav");
	}

	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}
