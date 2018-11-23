#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "TileMap.h"
#include "ECS.h"
#include "Components.h"

GameObject *player;
GameObject *enemy;
TileMap *tileMap;

SDL_Renderer *Game::Renderer = nullptr;

Manager manager;
auto& newPlayer(manager.AddEntity());

// Constructor
Game::Game()
{
}

// Deconstructor
Game::~Game()
{
}

void Game::Init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;

	// Check if sdl subsystems are successfully initialized
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized..." << std::endl;

		_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (_window) std::cout << "Window created" << std::endl;

		Renderer = SDL_CreateRenderer(_window, -1, 0);
		if (Renderer) 
		{
			SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl; 
		}

		_isRunning = true;
	}
	
	player = new GameObject("assets\\player1.png", 0, 0);
	enemy = new GameObject("assets\\enemy1.png", 100, 100);
	tileMap = new TileMap();

	newPlayer.AddComponent<PositionComponent>();
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

// This is just handling movement of game objects for now
void Game::Update()
{
	player->Update();
	enemy->Update();
	manager.Update();

	// TODO:
	// Figure out why x and y are not incrementing...
	std::cout << newPlayer.GetComponent<PositionComponent>().X() << "," << newPlayer.GetComponent<PositionComponent>().Y() << std::endl;

	_count++;
	std::cout << _count << std::endl;
}

// This is handling the drawing of game objects and the background
void Game::Render()
{
	SDL_RenderClear(Renderer);
	tileMap->DrawMap();
	player->Render();
	enemy->Render();
	SDL_RenderPresent(Renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}