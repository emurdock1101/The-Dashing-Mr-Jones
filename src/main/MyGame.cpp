#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Event.h"
#include "Sprite.h"
#include "SpriteDispatcher.h"
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	character = new Sprite("character","./resources/character/Idle_1.png");
    character->position = {0, 0};
    Game::addChild(character);

	coin = new SpriteDispatcher("coin","./resources/character/Idle_5.png");
    coin->position = {100, 100};
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
