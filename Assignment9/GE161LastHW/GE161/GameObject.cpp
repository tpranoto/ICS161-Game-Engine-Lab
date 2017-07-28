#include "GameObject.h"
#include "Game.h"


GE161::GameObject::GameObject(int startingX, int startingY) :
x_(startingX),
y_(startingY),
sprite_(nullptr)
{
}


GE161::GameObject::~GameObject()
{
}

void GE161::GameObject::setPos(int x, int y)
{
	x_ = x;
	y_ = y;
}

void GE161::GameObject::moveX(int delta)
{
	x_ += delta;
}

void GE161::GameObject::moveY(int delta)
{
	y_ += delta;
}

int GE161::GameObject::getX()
{
	return x_;
}

int GE161::GameObject::getWidth()
{
	if (sprite_ == nullptr)
		return 0;
	else
		return sprite_->frameWidth_;
}

int GE161::GameObject::getCenterX()
{
	return x_ + (getWidth() / 2);
}

int GE161::GameObject::getY()
{
	return y_;
}

int GE161::GameObject::getHeight()
{
	if (sprite_ == nullptr)
		return 0;
	else
		return sprite_->frameHeight_;
}

int GE161::GameObject::getCenterY()
{
	return y_ + (getHeight() / 2);
}


void GE161::GameObject::attachSprite(GE161::Sprite* sprite)
{
	sprite_ = sprite;	
}
void GE161::GameObject::draw(int frameIndex)
{
	if (sprite_ == nullptr)
	{
		debugOut("GameObject::draw called, but no Sprite is attached.");
		return;
	}

	SDL_Rect srcrect = {sprite_->frames[frameIndex].x, sprite_->frames[frameIndex].y, sprite_->frameWidth_, sprite_->frameHeight_};
	SDL_Rect destrect = {x_, y_, sprite_->frameWidth_, sprite_->frameHeight_};
	int success = SDL_RenderCopy(GE161::Game::theGame->getRenderer(), sprite_->frames[frameIndex].texture, &srcrect, &destrect);
	if (success != 0)
	{
		fatalSDLError("In GameObject::draw, SDL_RenderCopy: ", SDL_GetError());
	}
}

void GE161::GameObject::draw(std::string sequenceName)
{
	draw(sprite_->getNextFrameIndex(sequenceName));
}

bool GE161::GameObject::overlapsWith(GameObject& otherGameObject)
{
	if (this->sprite_ == nullptr || otherGameObject.sprite_ == nullptr)
		return false;

	// If the this overlaps other, return true
	int thisLeft = this->getX();
	int thisRight = this->getX() + this->sprite_->frameWidth_;
	int thisTop = this->getY();
	int thisBottom = this->getY() + this->sprite_->frameHeight_;
	int otherLeft = otherGameObject.getX();
	int otherRight = otherGameObject.getX() + otherGameObject.sprite_->frameWidth_;
	int otherTop = otherGameObject.getY();
	int otherBottom = otherGameObject.getY() + otherGameObject.sprite_->frameHeight_;
	if (thisRight < otherLeft ||
		thisLeft >= otherRight ||
		thisBottom < otherTop ||
		thisTop >= otherBottom)
	{
		return false;
	}
	else
	{
		return true;
	}
}



