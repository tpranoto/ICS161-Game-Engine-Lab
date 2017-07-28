#include "Game.h"

const std::string GE161::Game::START_GAME = "*STARTGAME*";
const std::string GE161::Game::EXIT_GAME = "*EXITGAME*";

//The linker wants this static variable defined here; it will get
// its actual value in main().
GE161::Game* GE161::Game::theGame = nullptr; 

int lowest_user_event_code = SDL_RegisterEvents(1000);    /// hw 8


GE161::Game::Game()
	: LOWEST_USER_EVENT_CODE(lowest_user_event_code)  // trickiness because it's const
{
	// Store a pointer to the game in a static variable for access by main().
	if (theGame == nullptr)
	{
		theGame = this;
	}
	else
	{
		fatalSDLError("More than one game object has been created.");
	}
}


GE161::Game::~Game()
{
}

void GE161::Game::addScene(std::string name, Scene* scene)
{
	sceneMap[name] = scene;

}

GE161::Scene* GE161::Game::lookUpScene(std::string name)
{
	if (sceneMap.count(name) == 1)
		return sceneMap[name];

	fatalSDLError("in Game::lookUpScene, scene name not found:", name);

	return nullptr;
}

SDL_Renderer* GE161::Game::getRenderer()
{
	return window_->sdl_renderer;
}

void GE161::Game::delay(int milliseconds)
{
	if (milliseconds <= 0)
		return;
	SDL_Delay(static_cast<unsigned int>(milliseconds));
}

std::string GE161::Game::pathSlash()
{
#ifdef _WIN32
	return std::string("\\");
#else
	return std::string("/");
#endif
}

int GE161::Game::getTicks()
{
	return static_cast<int>(SDL_GetTicks());
}

void GE161::Game::registerAsListener(int eventType, EventListener* listener)
{
	theGame->eventQueue_->registerAsListener(eventType, listener);
}



// Based on res_path.h.
std::string GE161::Game::basePath()
{
	//We give it static lifetime so that we'll only need to call
	//SDL_GetBasePath once to get the executable path
	static std::string baseRes;
	if (baseRes.empty())
	{
		//SDL_GetBasePath will return NULL if something went wrong in retrieving the path
		char *basePath = SDL_GetBasePath();
		if (basePath)
		{
			baseRes = basePath;
			SDL_free(basePath);
		}
		else
		{
			fatalSDLError("error in Game::basePath", SDL_GetError());
			baseRes = "";
		}
	}
	return baseRes;
}

void GE161::Game::debugOut(std::string message)
{
	OutputDebugString((message + "\n").c_str());
}

GE161::Window* GE161::Game::window()
{
	return window_;
}

/// hw6
void GE161::Game::setFramerate(int fps)
{
	framerate_ = fps;
}

void GE161::Game::setBackgroundColor(int red, int green, int blue)
{
	window_->bgRed = red;
	window_->bgGreen = green;
	window_->bgBlue = blue;
}

void GE161::Game::sendEvent(int eventType, int eventData[])   /// hw 8
{
	if (eventType < LOWEST_USER_EVENT_CODE)  // must not conflict with SDL event codes
	{
		fatalSDLError("error in Game::sendEvent, eventType is not less than LOWEST_USER_EVENT_CODE", std::to_string(LOWEST_USER_EVENT_CODE));
		return;
	}
	eventQueue_->insertEvent(new Event(eventType, eventData));
}