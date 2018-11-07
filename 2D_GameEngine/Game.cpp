#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"

GameObject* player;
GameObject* enemy;

// Constructor
Game::Game()
{
}

// Deconstructor
Game::~Game()
{
}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;

	// Check if sdl subsystems are successfully initialized
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized..." << std::endl;

		_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (_window) std::cout << "Window created" << std::endl;

		_renderer = SDL_CreateRenderer(_window, -1, 0);
		if (_renderer) 
		{
			SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl; 
		}

		_isRunning = true;
	}
	
	player = new GameObject("assets\\player1.png", _renderer, 0, 0);
	enemy = new GameObject("assets\\enemy1.png", _renderer, 100, 100);
}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	// SDL_QUIT is set when the x box on the window is clicked
	case SDL_QUIT:
		_isRunning = false;
		break;
	default:
		break;
	}
}

void Game::Update()
{
	player->Update();
	enemy->Update();

	_count++;
	std::cout << _count << std::endl;
}

void Game::Render()
{
	SDL_RenderClear(_renderer);
	player->Render();
	enemy->Render();
	SDL_RenderPresent(_renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}