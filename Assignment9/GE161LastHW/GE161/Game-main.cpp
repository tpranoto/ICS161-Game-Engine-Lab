#include "Game.h"

void GE161::Game::main(int x)
{
	if (x != 8675309)
	{
		fatalSDLError("Do not invoke GE161::Game::main()");
		return;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fatalSDLError("SDL_Init(SDL_INIT_EVERYTHING) Error in main(): ", SDL_GetError());
		return;
	}

	// Invoke the game's overridden setup() method, and create the SDL window.
	framerate_ = 30;		/// hw 6
	window_ = new GE161::Window();
	setup();
	window_->initialize();
	window_->clearBackground();

	eventQueue_ = new GE161::EventQueue();

	std::string sceneName = GE161::Game::START_GAME;
	int returnCode = CONTINUE_SCENE;

	// Loop through the outer while loop once per scene.
	// A negative return code from a scene says "Stop the program!"
	while (returnCode >= 0)
	{
		// Ask the game which scene to do next.
		sceneName = GE161::Game::theGame->chooseScene(sceneName, returnCode);
		GE161::Scene* scene = GE161::Game::theGame->lookUpScene(sceneName);

		// Now we have the scene to use.  First, run its setup().
		bool success = scene->setup();
		if (!success)
		{
			fatalSDLError("error in main(), setup failed for scene", sceneName);
			return;
		}

		// setup() succeeded.  Run its draw() until a non-zero return code.
		returnCode = CONTINUE_SCENE;
		/// hw 6
		int actualFPS[5];
		int currentSecond = 0;
		int actualStartofSecond = getTicks();
		int actualFrames = 0;
		int fpsStart = getTicks();			/// hw 6
		float fpsFramesThisSecond = 0;
		// Loop through the inner while loop once per frame in scene.
		while (returnCode == CONTINUE_SCENE)
		{
			eventQueue_->getSDLEvents();
			eventQueue_->callEventListeners();

			window_->clearBackground();
			returnCode = scene->draw();
			window_->drawToScreen();
			/// hw 6
			int fpsNow = getTicks();		/// hw 6
			fpsFramesThisSecond++;
			actualFrames++;
			int actualTicks = fpsNow - fpsStart;
			// The static_cast of float to int truncates, which is what we want.
			int goalTicks = static_cast<int>((fpsFramesThisSecond / framerate_) * 1000);
			if (actualTicks < goalTicks)
			{
				delay(goalTicks - actualTicks);
			}
			if (fpsFramesThisSecond >= framerate_)
			{
				fpsFramesThisSecond = 0;
				fpsStart = getTicks();
			}
			if (getTicks() - actualStartofSecond >= 1000)  // second's up, store num of frames
			{
				actualFPS[currentSecond++] = actualFrames;
				actualFrames = 0;
				actualStartofSecond = getTicks();
				if (currentSecond == 5) // we've hit the fifth second
				{
					float average =
						static_cast<float>(actualFPS[0] + actualFPS[1] + actualFPS[2] + actualFPS[3] + actualFPS[4])
						/ 5.0f;
					debugOut(std::string("Average framerate in last five seconds: ") +
						std::to_string(average));
					currentSecond = 0;
				}
			}

		}
		std::string m = std::string("return code from ") + sceneName + std::string(": ") + std::to_string(returnCode);
		debugOut(m);
	}

	SDL_Quit();
	return;
}