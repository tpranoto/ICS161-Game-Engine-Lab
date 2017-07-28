#include "GE161int.h"

void fatalSDLError(std::string message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
		"SDL Error",
		message.c_str(),
		NULL);
}

void fatalSDLError(std::string message1, std::string message2)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
		"SDL Error",
		(message1 + " " + message2).c_str(),
		NULL);
}

// This is Windows and Visual Studio dependent.
void debugOut(std::string message)
{
	OutputDebugString((message + "\n").c_str());
}

