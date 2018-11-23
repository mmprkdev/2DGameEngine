#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void Init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool Running() { return _isRunning; }

	static SDL_Renderer *Renderer;
	

private:
	int _count = 0;
	bool _isRunning;
	SDL_Window *_window;
};

