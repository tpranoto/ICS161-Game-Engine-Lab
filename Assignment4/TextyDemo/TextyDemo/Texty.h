//Timothy Pranoto
//38964311
//ICS161 HW4

#pragma once

#include <iostream>
#include <SDL.h>
#include "SDL_ttf.h"

class Texty
{

public:
	Texty(SDL_Renderer* renderer, std::string fontName, int fontSize = 10, bool visible = true);
	~Texty();

	enum writeOption_t { CONTINUE, NEXT_LINE };

	void write(std::string text, writeOption_t option = Texty::CONTINUE);

	void write(std::string text, int x, int y);


private:
	/* To be coded for Homework 4. */
	SDL_Renderer* renderer;
	SDL_Color color;
	int currX, currY;
	int lastX;
	int tempH;
	std::string fontName;
	int size;
	bool visible;
	SDL_Texture * renderText(std::string text);

};
