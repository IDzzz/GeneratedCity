#pragma once
#include <vector>
#include <Core/Engine.h>

class Ornament {
public:
	Ornament( Mesh* m, Texture2D* t, glm::vec3 cor, glm::vec3 s, int r)
	{
		corner = cor;
		mesh = m;
		texture = t;
		scale = s;
		rot = r;
	}

	float rot;
	glm::vec3 scale;
	glm::vec3 corner;
	Mesh* mesh;
	Texture2D* texture;
};