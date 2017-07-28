//Timothy Pranoto
//38964311
//ICS161 HW3

#include "Sprite.h"

Sprite::Sprite(int nwidth, int nheight, SDL_Renderer* ren)
{
	width = nwidth;
	height = nheight;
	renderer = ren;
	sequenceIndex = 0;
}

Sprite::~Sprite(void){}

void Sprite::setPos(int x, int y)
{
	currX = x;
	currY = y;
}

void Sprite::movex(int delta)
{

	currX += delta;
}

void Sprite::movey(int delta)
{
	currY += delta;
}

int Sprite::getX()
{
	return currX;
}

int Sprite::getY()
{
	return currY;
}

int Sprite::makeFrame(SDL_Texture* texture, int x, int y)
{
	frame dst;
	dst.texture = texture;
	dst.x = x;
	dst.y = y;
	frames.push_back(dst);
	return frames.size() - 1;
}

int Sprite::addFrameToSequence(std::string seqName, int frameIndex)
{
	sequenceList[seqName].push_back(frameIndex);
	return sequenceList[seqName].size();
}

void Sprite::show(int frameIndex)
{
	SDL_Rect src;
	src.h = height;
	src.w = width;
	src.x = frames[frameIndex].x;
	src.y = frames[frameIndex].y;

	SDL_Rect dst;
	dst.h = height;
	dst.w = width;
	dst.x = currX;
	dst.y = currY;
	SDL_RenderCopy(renderer, frames[frameIndex].texture, &src, &dst);
}

void Sprite::show(std::string sequence)
{
	std::vector<int> total = sequenceList[sequence];
	if (sequenceIndex<total[0] || sequenceIndex >= (total[0] + total.size()))
		sequenceIndex = total[0];
	SDL_Rect src;
	src.h = height;
	src.w = width;
	src.x = frames[sequenceIndex].x;
	src.y = frames[sequenceIndex].y;

	SDL_Rect dst;
	dst.h = height;
	dst.w = width;
	dst.x = currX;
	dst.y = currY;
	SDL_RenderCopy(renderer, frames[sequenceIndex++].texture, &src, &dst);
}