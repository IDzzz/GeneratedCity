#pragma once
#include <vector>
#include <Core/Engine.h>

class Street {
public:
	Street(int length, glm::vec3 cor,  bool type)
	{
		l = length;
		corner = cor;
		horiz = type;
		streetMesh = generateMesh();
	}

	Mesh* generateMesh()
	{
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> textureCoords;
		std::vector<glm::vec3> normals;

		if (horiz == true) {
			vertices.push_back(glm::vec3(0, 0.0f, 0));
			textureCoords.push_back(glm::vec2(0, 0));
			normals.push_back(glm::vec3(0, 1, 0));

			vertices.push_back(glm::vec3(1, 0.0f, 0));
			textureCoords.push_back(glm::vec2(1, 0));
			normals.push_back(glm::vec3(0, 1, 0));

			vertices.push_back(glm::vec3(1, 0.0f, l));
			textureCoords.push_back(glm::vec2(1, l));
			normals.push_back(glm::vec3(0, 1, 0));

			vertices.push_back(glm::vec3(0, 0.0f, l));
			textureCoords.push_back(glm::vec2(0, l));
			normals.push_back(glm::vec3(0, 1, 0));
		}
		else {
			vertices.push_back(glm::vec3(0, 0.0f, 0));
			textureCoords.push_back(glm::vec2(0, 0));
			normals.push_back(glm::vec3(0, 1, 0));

			vertices.push_back(glm::vec3(l, 0.0f, 0));
			textureCoords.push_back(glm::vec2(l, 0));
			normals.push_back(glm::vec3(0, 1, 0));

			vertices.push_back(glm::vec3(l, 0.0f, 1));
			textureCoords.push_back(glm::vec2(l, 1));
			normals.push_back(glm::vec3(0, 1, 0));

			vertices.push_back(glm::vec3(0, 0.0f, 1));
			textureCoords.push_back(glm::vec2(0, 1));
			normals.push_back(glm::vec3(0, 1, 0));
		}

		std::vector<unsigned short> indices =
		{
			0, 1, 2,
			2, 3, 0,
		};


		Mesh* mesh = new Mesh("street");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		return mesh;
	}

	bool horiz;
	int l;
	glm::vec3 corner;
	Mesh* streetMesh;
};