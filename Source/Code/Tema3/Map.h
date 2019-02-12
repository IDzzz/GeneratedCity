#pragma once
#include <Core/Engine.h>

class Map {
public:
	Map(float w, float h)
	{
		width = w;
		height = h;

	}

	int a[20][20];
	float height;
	float width;

};