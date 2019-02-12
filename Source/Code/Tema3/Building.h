#pragma once
#include <vector>
#include <Core/Engine.h>

class Building {
public:
	Building(float w, float h, float l, glm::vec3 cor, int t, glm::vec3 st)
	{
		length = l;
		width = w;
		height = h;
		corner = cor;
		type = t;
		latWall = generateLat(length, height);
		frontWall = generateFront(width, height);
		roof = generateRoof(width, length);
		spotlight = st;
	}

	Mesh* generateRoof(float x, float y) {
		std::vector<glm::vec3> vertices
		{
			glm::vec3(x, 0.0f, 0.0f),	// Bottom Left
			glm::vec3(0.0f,  0.0f, 0.0f),	// Bottom Right
			glm::vec3(0.0f,  0.0f, y),	// Top Right
			glm::vec3(x,  0.0f, y),	// Top Left
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
			glm::vec2(0.0f, x),
			glm::vec2(y, x),
			glm::vec2(y, 0.0f),
		};

		std::vector<unsigned short> indices =
		{
			0, 1, 2,
			0, 2, 3
		};

		Mesh* mesh = new Mesh("roof");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		return mesh;
	}

	Mesh* generateFront(float x, float y)
	{
		std::vector<glm::vec3> vertices
		{
			glm::vec3(0, 0, 0.0f),	// Bottom Left
			glm::vec3(x,  0, 0.0f),	// Bottom Right
			glm::vec3(x,  y, 0.0f),	// Top Right
			glm::vec3(0,  y, 0.0f),	// Top Left
		};

		std::vector<glm::vec3> normals
		{
			glm::vec3(1, 0, 0),
			glm::vec3(1, 0, 0),
			glm::vec3(1, 0, 0),
			glm::vec3(1, 0, 0)
		};

		// TODO : Complete texture coordinates for the square
		std::vector<glm::vec2> textureCoords
		{
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, x),
			glm::vec2(y, x),
			glm::vec2(y, 0.0f),
		};

		std::vector<unsigned short> indices =
		{
			0, 1, 2,
			0, 2, 3
		};

		Mesh* mesh = new Mesh("frontWall");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		return mesh;
	}

	Mesh* generateLat(float x, float y) {
		std::vector<glm::vec3> vertices
		{
			glm::vec3(0, 0.0f, x),	// Bottom Left
			glm::vec3(0.0f,  0.0f, 0.0f),	// Bottom Right
			glm::vec3(0.0f,   y, 0.0f),	// Top Right
			glm::vec3(0.0f,  y, x),	// Top Left
		};

		std::vector<glm::vec3> normals
		{
			glm::vec3(0, 0, 1),
			glm::vec3(0, 0, 1),
			glm::vec3(0, 0, 1),
			glm::vec3(0, 0, 1)
		};

		// TODO : Complete texture coordinates for the square
		std::vector<glm::vec2> textureCoords
		{
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, x),
			glm::vec2(y, x),
			glm::vec2(y, 0.0f),
		};

		std::vector<unsigned short> indices =
		{
			0, 1, 2,
			0, 2, 3
		};

		Mesh* mesh = new Mesh("latWall");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		return mesh;
	}

	float width, height, length;
	int type;
	glm::vec3 corner;
	glm::vec3 spotlight;
	Mesh* latWall;
	Mesh* frontWall;
	Mesh* roof;
	std::vector<Building> subBuildings;
};