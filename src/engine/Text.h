#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL_ttf.h>
#include "DisplayObject.h"

using namespace std;

class Text : public DisplayObject {

public:
	string fontPath = "./resources/OpenSans-Regular.ttf";
	int size = 24;
	SDL_Color color = {255, 255, 255};
	string text = "";

	Text();
	Text(string text, int x, int y);
	Text(string font, int size, SDL_Color color, string text, int x, int y);
	virtual ~Text();

	void setText(string text);
	void setTextFromInt(int intText);
	void setTextFromFloat(float floatText);
	void appendString(string toAppend);
	void appendChar(char toAppend);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	void loadTextTexture();

private:
	TTF_Font *font;
	SDL_Texture* texture = NULL;

	/* Texture currently being drawn. Equal to texture for normal DO */
	SDL_Texture* curTexture;
};

#endif
