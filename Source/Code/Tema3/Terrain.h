#pragma once
#include <vector>
#include <Core/Engine.h>

class Terrain {
public:
	Terrain(glm::vec3 cor)
	{
		corner = cor;
		terrainMesh = generateMesh();
	}

	Mesh* generateMesh()
	{
		std::vector<glm::vec3> vertices
		{
			glm::vec3(1.0f, 0.0f, 0.0f),	// Bottom Left
			glm::vec3(0.0f,  0.0f, 0.0f),	// Bottom Right
			glm::vec3(0.0f,  0.0f, 1.0f),	// Top Right
			glm::vec3(1.0f,  0.0f, 1.0f),	// Top Left
		};

		std::vector<glm::vec3> normals
		{
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0)
		};

		// TODO : Complete texture coordinates for the square
		std::vector<glm::vec2> textureCoords
		{
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(1.0f, 0.0f),
		};

		std::vector<unsigned short> indices =
		{
			0, 1, 2,
			0, 2, 3
		};

		Mesh* mesh = new Mesh("terrain");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		return mesh;
	}

	glm::vec3 corner;
	Mesh* terrainMesh;
};