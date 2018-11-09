#pragma once

#include "Game.h"

class GameObject
{
public:
	GameObject(const char* textureSheet, int xpos, int ypos);
	~GameObject();

	void Update();
	void Render();

private:
	int _xpos;
	int _ypos;

	SDL_Texture* _objTexture;
	// The source rectangle is the size and pos taken from the source image
	// and the destination rectangle is the size and pos to be displayed on
	// the window.
	SDL_Rect _sourceRect, _destRect;
};
