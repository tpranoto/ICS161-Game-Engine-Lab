//Timothy Pranoto
//38964311
//ICS161 HW4

#include "Texty.h"   // You can add or remove #include files as needed.
#include <iostream>
#include <sstream>
#include "Windows.h"
#include <string>

Texty::Texty(SDL_Renderer* ren, std::string fName, int fontSize, bool vis){
	renderer = ren;
	fontName = fName;
	size = fontSize;
	visible = vis;
}

Texty::~Texty(){

}

SDL_Texture * Texty::renderText(std::string text){
	TTF_Font* font = TTF_OpenFont(fontName.c_str(), size);
	if (font == nullptr){
		std::cout << "Error: TTF_OpenFont Failed!\n";
		exit(1);
	}
	color = { 0, 0, 0 };
	SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), color);
	if (surf == nullptr){
		TTF_CloseFont(font);
		std::cout << "Error: TTF_RenderText Failed!\n";
		exit(2);
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr){
		std::cout << "Error: TTF_CreateTexture Failed!\n";
		exit(3);
	}
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}

//Modified the if line to complete part2 of the assignment so you can call the method with default value for option
//and change the NEXT_LINE option to \n in the text itself.
void Texty::write(std::string text, writeOption_t option){

	size_t compare = text.find("\n");
	//check for either NEXT_LINE or \n
	if (option == Texty::NEXT_LINE||compare!=std::string::npos){
		currY += tempH;
		write(text, lastX, currY);
	}
	else{
		SDL_Texture * texture = renderText(text);
		int w, h;
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
		tempH = h;

		SDL_Rect dst;
		dst.x = currX;
		dst.y = currY;
		dst.w = w;
		dst.h = h;
		currX += w;
		if (visible)
			SDL_RenderCopy(renderer, texture, NULL, &dst);
	}
}

//\n doesn't do anything in this method because it have x and y coordinate, so if the text in this method have \n, 
//it will be removed from the text
void Texty::write(std::string text, int x, int y){
	lastX = x;
	currX = x;
	currY = y;

	//just checking if text have \n and removing it from the string.
	std::string nline = "\n";
	size_t index;
	std::string input = text;
	size_t compare = input.find("\n");
	if (compare != std::string::npos){
		while ((index = input.find_first_of(nline)) != std::string::npos)
			input = input.substr(0, index) + input.substr(index + nline.size());
	}

	SDL_Texture * texture = renderText(input);

	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	tempH = h;

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	currX += w;
	if (visible)
		SDL_RenderCopy(renderer, texture, NULL, &dst);
	
}