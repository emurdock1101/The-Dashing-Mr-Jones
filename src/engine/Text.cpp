#include "Text.h"
#include "Game.h"
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

Text::Text(){
	id = "Text";
	position = {0, 0};
	font = TTF_OpenFont(fontPath.c_str(), size);
	texture = NULL;
	curTexture = NULL;
}

Text::Text(string text, int x, int y) {
	id = "Text";
	position = {x, y};
	this->text = text;
	font = TTF_OpenFont(fontPath.c_str(), size);

	loadTextTexture();
}

Text::Text(string fontPath, int size, SDL_Color color, string text, int x, int y) {
	id = "Text";
	position = {x, y};
	this->fontPath = fontPath;
	this->size = size;
	this->color = color;
	this->text = text;
	font = TTF_OpenFont(fontPath.c_str(), size);

	loadTextTexture();
}

Text::~Text() {
}

void Text::setText(string text) {
	this->text = text;
	loadTextTexture();
}

void Text::setTextFromInt(int intText) {
	this->text = std::to_string(intText);
	loadTextTexture();
}

void Text::setTextFromFloat(float floatText) {
	this->text = std::to_string(floatText);
	loadTextTexture();
}

void Text::appendString(string toAppend) {
	text += toAppend;
	loadTextTexture();
}

void Text::appendChar(char toAppend) {
	text += toAppend;
	loadTextTexture();
}

void Text::loadTextTexture() {
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), color);
	curTexture = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);
}

void Text::update(set<SDL_Scancode> pressedKeys) {
}

void Text::draw(AffineTransform &at) {
	if (curTexture != NULL) {
		int width, height;
		TTF_SizeText(font, text.c_str(), &width, &height);
		SDL_Rect rect = {position.x, position.y, width, height};
		SDL_RenderCopy(Game::renderer, curTexture, NULL, &rect);
	}
}
