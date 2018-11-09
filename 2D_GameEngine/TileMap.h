#pragma once

#include "Game.h"

class TileMap
{
public:
	TileMap();
	~TileMap();

	void LoadMap(int mapArray[20][25]);
	void DrawMap();

private:
	SDL_Rect _src, _dest;

	SDL_Texture* _dirt;
	SDL_Texture* _grass;
	SDL_Texture* _water;

	int _map[20][25];

};
