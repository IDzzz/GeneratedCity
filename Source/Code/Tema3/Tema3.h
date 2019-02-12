#pragma once
#include "Street.h"
#include "Ornament.h"
#include "Terrain.h"
#include "Building.h"
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>

class Tema3 : public SimpleScene
{
public:
	Tema3();
	~Tema3();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;
	void GenerateStreets();
	void generate(bool isHoriz, int ln, int rn, int lm, int rm, int no, int req);
	void RenderTextureMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, Texture2D* texture = NULL, Building* b = NULL);
	void generateBuilding(int j, int i, int type);
	void generateTerrain(int j, int i);
	void RenderBuilding(Building b);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	float cX = 1;
	float cy = 1;
	float moveSun = 2;

	glm::vec3 lightPosition;
	glm::vec3 lightDirection;
	unsigned int materialShininess;
	float materialKd;
	float materialKs;
	float angle;
	float angleS;

	std::unordered_map<std::string, Texture2D*> mapTextures;
	GLuint randomTextureID;

	std::vector<Street> streets;
	std::vector<Building> buildings;
	std::vector<Terrain> terrains;
	std::vector<Ornament> ornaments;
};
