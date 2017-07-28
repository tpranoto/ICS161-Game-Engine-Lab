#pragma once

#include <string>
#include "Sprite.h"

namespace GE161
{
	class GameObject
	{
	public:
		GameObject(int startingX = 0, int startingY = 0);
		~GameObject();

		void setPos(int x, int y);
		void moveX(int delta);
		void moveY(int delta);
		int getX();
		int getWidth();
		int getCenterX();
		int getY();
		int getHeight();
		int getCenterY();
		void attachSprite(Sprite* sprite);
		void draw(int frameIndex);
		void draw(std::string sequenceName);
		bool overlapsWith(GameObject& otherGameObject);

	private:
		int x_;		// current position of
		int y_;		// this game object
		Sprite* sprite_;

	};

}

