#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Event.h"
#include "Sprite.h"
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	character = new Sprite("character","./resources/character/Idle_1.png");
    character->position = {0, 0};
    character->width = 200;
    character->height = 200;
    character->pivot = {character->width/2, character->height/2};
    Game::addChild(character);

	coin = new Sprite("coin","./resources/Coin.png");
    coin->position = {500, 500};
    coin->width = 20;
    coin->height = 20;
    coin->pivot = {coin->width/2, coin->height/2};
    
    Game::addChild(coin);

    questManager = new QuestManager();
    coin->addEventListener(questManager, Event::COIN_PICKED_UP);
}

MyGame::~MyGame(){
}

void MyGame::update(set<SDL_Scancode> pressedKeys){
	character->update(pressedKeys);
	Game::update(pressedKeys);
    if (Game::getChild(coin->id) != NULL
            && abs(character->position.x - coin->position.x) < 50
            && abs(character->position.y - coin->position.y) < 50) {
        Event *coinPickedUp = new Event(Event::COIN_PICKED_UP, coin);
        coin->dispatchEvent(coinPickedUp);
        coin->removeThis();
    }
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		character->position.x++;
		character->facingRight = true;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		character->position.x--;
		character->facingRight = false;
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		character->position.y++;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		character->position.y--;
	}
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}
