#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* finishedTex = SDL_CreateTextureFromSurface(Game::Renderer, tempSurface);

	return finishedTex;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::Renderer, texture, &src, &dest);
}
