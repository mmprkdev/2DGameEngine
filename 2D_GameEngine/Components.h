#pragma once

#include "ECS.h"

class PositionComponent : public Component
{
private:
	int _xpos;
	int _ypos;

public:
	int X() { return _xpos; }
	int Y() { return _ypos; }

	void Init() override
	{
		_xpos = 0;
		_ypos = 0;
	}

	void Update() override
	{
		_xpos++;
		_ypos++;
	}

	void SetPos(int x, int y)
	{
		_xpos = x;
		_ypos = y;
	}
};
