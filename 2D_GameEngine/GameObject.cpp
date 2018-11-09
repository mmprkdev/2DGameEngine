#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int xpos, int ypos)
{
	_objTexture = TextureManager::LoadTexture(textureSheet);

	_xpos = xpos;
	_ypos = ypos;
}

void GameObject::Update()
{
	_xpos++;
	_ypos++;

	_sourceRect.w = 800;
	_sourceRect.h = 600;
	_sourceRect.x = 0;
	_sourceRect.y = 0;

	_destRect.x = _xpos;
	_destRect.y = _ypos;
	_destRect.w = _sourceRect.w / 2;
	_destRect.h = _sourceRect.h / 2;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::Renderer, _objTexture, &_sourceRect, &_destRect);
}