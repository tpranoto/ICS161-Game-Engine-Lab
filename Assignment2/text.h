//Timothy Pranoto
//38964311
//ICS161 - HW2

#include <iostream>
#include <SDL.h>
#include <res_path.h>
#include <cleanup.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Text
{
private:
	std::string font;//the type of the font
	int fontsize;//the size of the font
	SDL_Color color;//the color of the font
	bool output;//bool true for turn on text output and bool false for turn off on text output
	int x,y;//location of the text x & y axis
	bool location;//if bool true then continue from the end of the previous text and if false then start on the next line
public:
	//constructor with everything on default but the text to display itself
	Text(std::string text);
	//constructor with all variable as parameter
	Text(std::string text, std::string fontstyle, int size, SDL_Color color, bool output, int x, int y, bool location);

	//Accessor methods
	std::string getFontStyle();
	int getFontSize();
	std::string getFontColor();
	bool getOutputDisplay();
	int[] getFontAxis();
	bool getTextLocation();

	//Mutator methods
	void chgFontStyle(std::string style);
	void chgFontSize(int size);
	void chgFontColor(std::string color);
	void chgOutputDisplay(bool value);

	void handleError(std::ostream &os, const std::string &msg);

	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

	SDL_Texture* renderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer);
	//destructor
	~Text(void);
};