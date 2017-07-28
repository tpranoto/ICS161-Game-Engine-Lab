#pragma once

#include <string>
#include <map>
#include "Window.h"
#include "Scene.h"
#include "EventQueue.h"

namespace GE161
{
	class Game
	{
		friend class Sprite;
		friend class GameObject;
		friend class Texty;

	public:
		Game();
		~Game();

		// These functions are called by the game code.
		void addScene(std::string name, Scene* scene);
		Scene* lookUpScene(std::string name);
		Window* window();
		static void registerAsListener(int eventType, EventListener* listener);
		void setFramerate(int fps);		/// hw 6
		void setBackgroundColor(int red, int green, int blue);  /// hw 6
		void sendEvent(int eventType, int eventData[]);    /// hw 8

		// Helpful functions exposed to the game programmer.
		static void delay(int milliseconds);
		static std::string pathSlash();
		static std::string basePath();
		static void debugOut(std::string);
		static int getTicks();

		// These functions have to be overridden by the game code.
		virtual void setup() = 0;
		virtual std::string chooseScene(std::string prevScene, int prevReturnCode) = 0;

		// This function should be called exactly once by main().
		void main(int x);

		static const std::string START_GAME;
		static const std::string EXIT_GAME;

		static Game* theGame;
		static const int CONTINUE_SCENE = 0;
		const int LOWEST_USER_EVENT_CODE;

	private:
		SDL_Renderer* getRenderer();

		Window* window_;
		std::map<std::string, Scene*> sceneMap;
		EventQueue* eventQueue_;
		int framerate_;		/// hw6
	};

}
