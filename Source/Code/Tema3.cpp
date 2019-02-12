#include "Tema3.h"
#include "Street.h"
#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

static int myMap[20][20];
static int nStreet = 10;
static int mStreet = 10;
static int reqStreet = 6;
static float maxHeight = 5;
static float minHeight = 3;

Tema3::Tema3()
{
}

Tema3::~Tema3()
{
}

void Tema3::RenderBuilding(Building b) {
	Texture2D* texture = b.type == 0 ? mapTextures["window"] : mapTextures["old"];
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, b.corner + glm::vec3(0, b.height, 0.0f));
	if (b.type == 0) {
		RenderTextureMesh(b.roof, shaders["TextureShader"], modelMatrix, texture, &b);
	}
	else {
		RenderTextureMesh(b.roof, shaders["TextureShader"], modelMatrix, mapTextures["oldRoof"], &b);
	}
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, b.corner + glm::vec3(0.0f, 0.0f, 0.0f));
	RenderTextureMesh(b.latWall, shaders["TextureShader"], modelMatrix, texture, &b);
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, b.corner + glm::vec3(b.width, 0.0f, 0.0f));
	RenderTextureMesh(b.latWall, shaders["TextureShader"], modelMatrix, texture, &b);
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, b.corner + glm::vec3(0.0f, 0.0f, 0.0f));
	RenderTextureMesh(b.frontWall, shaders["TextureShader"], modelMatrix, texture, &b);
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, b.corner + glm::vec3(0.0f, 0.0f, b.length));
	RenderTextureMesh(b.frontWall, shaders["TextureShader"], modelMatrix, texture, &b);

}

void Tema3::generate(bool isHoriz, int ln, int rn, int lm, int rm, int no, int req) {
	if (no == req)
		return;
	if (rn <= ln + 2)
		return;
	if (rm <= lm + 2)
		return;
	if (isHoriz == true) {
		int c = rand() % (rm - lm) + lm;
		if (c == rm) {
			c = rm - 1;
		}
		if (c == lm) {
			c = lm + 1;
		}
		for (int i = ln; i < rn; i++)
			myMap[i][c] = 1;
		streets.push_back(Street(rn - ln, glm::vec3(c, 0, ln), true));
		Tema3::generate(!isHoriz, ln, rn, lm, c, no + 1, req);
		Tema3::generate(!isHoriz, ln, rn, c + 1, rm, no + 1, req);
	}
	else {
		int r = rand() % (rn - ln) + ln;
		if (r == rn) {
			r = rn - 1;
		}
		if (r == ln) {
			r = ln + 1;
		}

		for (int i = lm; i < rm; i++)
			myMap[r][i] = 1;
		streets.push_back(Street(rm - lm, glm::vec3(lm, 0, r), false));
		Tema3::generate(!isHoriz, ln, r, lm, rm, no + 1, req);
		Tema3::generate(!isHoriz, r + 1, rn, lm, rm, no + 1, req);
	}
}

void Tema3::generateTerrain(int i, int j) 
{
	terrains.push_back(Terrain(glm::vec3(j, 0, i)));
}

void Tema3::GenerateStreets()
{
	generate(true, 0, nStreet, 0, mStreet, 0, reqStreet);
}

void Tema3::generateBuilding(int j, int i, int type)
{
	int no = rand() % 6;
	float hMax = maxHeight;
	float hMin = minHeight;
	float auxH = (rand() % (int)(hMax * 100 - hMin * 100));
	float auxHS = (rand() % (int)(hMax * 100 - hMin * 100));
	float hf = auxH / 100 + hMin;
	float hfs = auxHS / 100 + hMin;
	if (no == 0) {
		int w = rand() % 60 + 40;
		int l = rand() % 40 + 60;
		float wf = ((float)w) / 100;
		float lf = ((float)l) / 100;
		float posX = ((float)(abs(rand() % (100 - w)))) / 100;
		float posZ = ((float)(abs(rand() % (100 - l)))) / 100;
		buildings.push_back(Building(1, hf, 1, glm::vec3(i, 0, j), type, glm::vec3(i +0.2f , hfs, j + posZ + 0.2f)));
	}
	else {
		int w = rand() % 60 + 40;
		int l = rand() % 40 + 60;
		float wf = ((float) w) / 100;
		float lf = ((float) l) / 100;
		float posX = ((float)(abs(rand() % (100 - w)))) / 100;
		float posZ = ((float)(abs(rand() % (100 - l)))) / 100;
		float posXX = ((float)(abs(rand() % (100 - w)))) / 100;
		float posZZ = ((float)(abs(rand() % (100 - l)))) / 100;
		Building b = Building(wf, hf, lf, glm::vec3(i + posX, 0, j + posZ), type, glm::vec3(i + posXX + 0.2f, hfs, j + posZZ + 0.2f));
		
		for (int count = 0; count < no; count++) {
			int procent = rand() % 20;
			hf -= procent * hf / 100;
			int w = rand() % 60 + 40;
			int l = rand() % 40 + 60;
			float wf = ((float)w) / 100;
			float lf = ((float)l) / 100;
			float posX = ((float)(abs(rand() % (100 - w)))) / 100;
			float posZ = ((float)(abs(rand() % (100 - l)))) / 100;
			float posXX = ((float)(abs(rand() % (100 - w)))) / 100;
			float posZZ = ((float)(abs(rand() % (100 - l)))) / 100;
			b.subBuildings.push_back(Building(wf, hf, lf, glm::vec3(i + posX, 0, j + posZ), type, glm::vec3(i + posXX + 0.2f, hfs, j + posZZ + 0.2f)));
		}
		buildings.push_back(b);
	}
}

void Tema3::Init()
{

	//camera
	GetSceneCamera()->SetPosition(glm::vec3(5, 6, 16));
	const string textureLoc = "Source/Laboratoare/Tema3/Textures/";
	const string modelLoc = "Source/Laboratoare/Tema3/Models/";
	streets.clear();

	for (int i = 0; i < nStreet; i++)
		for (int j = 0; j < mStreet; j++)
			myMap[i][j] = 0;
	Tema3::GenerateStreets();
	cout << streets.size() << "\n";

	//Light & material properties
	angle = 120;
	angleS = 30;
	{
		lightPosition = glm::vec3(0, 10, 5);
		lightDirection = glm::vec3(0, -1, 0);
		materialShininess = 10;
		materialKd = 0.3;
		materialKs = 0.3;
	}

	// Load textures
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "street.png").c_str(), GL_REPEAT);
		mapTextures["street"] = texture;

		Texture2D* texture2 = new Texture2D();
		texture2->Load2D((textureLoc + "window.png").c_str(), GL_REPEAT);
		mapTextures["window"] = texture2;


		Texture2D* texture3 = new Texture2D();
		texture3->Load2D((textureLoc + "terrain.png").c_str(), GL_REPEAT);
		mapTextures["terrain"] = texture3;


		Texture2D* texture4 = new Texture2D();
		texture4->Load2D((textureLoc + "old.png").c_str(), GL_REPEAT);
		mapTextures["old"] = texture4;


		Texture2D* texture5 = new Texture2D();
		texture5->Load2D((textureLoc + "oldRoof.png").c_str(), GL_REPEAT);
		mapTextures["oldRoof"] = texture5;

		Texture2D* texture6 = new Texture2D();
		texture6->Load2D((textureLoc + "sem.png").c_str(), GL_REPEAT);
		mapTextures["sem"] = texture6;

		Texture2D* texture7 = new Texture2D();
		texture7->Load2D((textureLoc + "fountain.png").c_str(), GL_REPEAT);
		mapTextures["fountain"] = texture7;

		Texture2D* texture8 = new Texture2D();
		texture8->Load2D((textureLoc + "btree.png").c_str(), GL_REPEAT);
		mapTextures["btree"] = texture8;

		Texture2D* texture9 = new Texture2D();
		texture9->Load2D((textureLoc + "tree.png").c_str(), GL_REPEAT);
		mapTextures["tree"] = texture9;

		Texture2D* texture10 = new Texture2D();
		texture10->Load2D((textureLoc + "bench.png").c_str(), GL_REPEAT);
		mapTextures["bench"] = texture10;

		Texture2D* texture11 = new Texture2D();
		texture11->Load2D((textureLoc + "redcar.png").c_str(), GL_REPEAT);
		mapTextures["redcar"] = texture11;


		Texture2D* texture12 = new Texture2D();
		texture12->Load2D((textureLoc + "bluecar.png").c_str(), GL_REPEAT);
		mapTextures["bluecar"] = texture12;

		Texture2D* texture13 = new Texture2D();
		texture13->Load2D((textureLoc + "yellowcar.png").c_str(), GL_REPEAT);
		mapTextures["yellowcar"] = texture13;
	}

	{
		{
			Mesh* mesh = new Mesh("sem");
			mesh->LoadMesh(modelLoc, "sem.obj");
			meshes[mesh->GetMeshID()] = mesh;
		}
		
		{
			Mesh* mesh = new Mesh("fountain");
			mesh->LoadMesh(modelLoc, "fountain.obj");
			meshes[mesh->GetMeshID()] = mesh;
		}

		{
			Mesh* mesh = new Mesh("btree");
			mesh->LoadMesh(modelLoc, "btree.obj");
			meshes[mesh->GetMeshID()] = mesh;
		}

		{
			Mesh* mesh = new Mesh("tree");
			mesh->LoadMesh(modelLoc, "tree.obj");
			meshes[mesh->GetMeshID()] = mesh;
		}

		{
			Mesh* mesh = new Mesh("bench");
			mesh->LoadMesh(modelLoc, "bench.obj");
			meshes[mesh->GetMeshID()] = mesh;
		}

		{
			Mesh* mesh = new Mesh("car");
			mesh->LoadMesh(modelLoc, "car.obj");
			meshes[mesh->GetMeshID()] = mesh;
		}
	}


	for (int i = 0; i < nStreet; i++)
	{
		for (int j = 0; j < mStreet; j++)
		{
			if (myMap[i][j] == 0) {
				int pos = rand() % 100;
				if (pos <= 40) {
					generateBuilding(i, j, 0);
				} else if (pos <= 60) {
					generateBuilding(i, j, 1);
				}
				else if (pos <= 70) {
					ornaments.push_back(Ornament(meshes["fountain"], mapTextures["fountain"], glm::vec3(j + 0.5f, -16.11f, i + 0.5f), glm::vec3(0.3f, 0.3f, 0.3f), 0));
				}
				else if (pos <= 75) {
					int randX = rand() % 6;
					int randY = rand() % 6;
					float px = randX / 10.0f;
					float pz = randY / 10.0f;
					ornaments.push_back(Ornament(meshes["btree"], mapTextures["btree"], glm::vec3(j + 0.2f + px, 0, i + 3.2f + pz), glm::vec3(1, 1, 1), 0));
				}
				else if (pos <= 85) {
					int randX = rand() % 5;
					int randY = rand() % 5;
					float px = randX / 10.0f;
					float pz = randY / 10.0f;
					ornaments.push_back(Ornament(meshes["tree"], mapTextures["tree"], glm::vec3(j + 0.4f + px, 0, i + 0.4f + pz), glm::vec3(0.5f, 0.5f, 0.5f), 0));
				}
				else if (pos <= 95) {
					ornaments.push_back(Ornament(meshes["bench"], mapTextures["bench"], glm::vec3(j + 0.5f, 0, i + 0.2f), glm::vec3(0.3f, 0.3f, 0.3f), 0));
					if (rand() % 2 == 0) {
						ornaments.push_back(Ornament(meshes["bench"], mapTextures["bench"], glm::vec3(j + 0.2f, 0, i + 0.5f), glm::vec3(0.3f, 0.3f, 0.3f), 1));
					}
					else {
						ornaments.push_back(Ornament(meshes["bench"], mapTextures["bench"], glm::vec3(j + 0.7f, 0, i + 0.5f), glm::vec3(0.3f, 0.3f, 0.3f), 1));
					}
				}
				generateTerrain(i, j);
			}
			else {
				int pos = rand() % 100;
				if (pos <= 25) {
					int posX = rand() % 9;
					int posZ = rand() % 9;
					float fx = posX / 10.0f;
					float fz = posZ / 10.0f;
					ornaments.push_back(Ornament(meshes["sem"], mapTextures["sem"], glm::vec3(j + fx, 0, i + fz), glm::vec3(0.01f, 0.01f, 0.01f), rand() % 4));
				}
				else if(pos <= 85){
					int posX = rand() % 7;
					int posZ = rand() % 7;
					float fx = posX / 10.0f;
					float fz = posZ / 10.0f;
					Texture2D* t;
					if (pos <= 45) {
						t = mapTextures["redcar"];
					}
					else if (pos <= 65) {
						t = mapTextures["bluecar"];
					}
					else {
						t = mapTextures["yellowcar"];
					}

					ornaments.push_back(Ornament(meshes["car"], t, glm::vec3(j + 0.2f + fx, 0, i + 0.2f + fz), glm::vec3(0.1f, 0.1f, 0.1f), rand() % 4));
				}
			}
		}
	}

	for (int i = 0; i < nStreet; i++)
	{
		for (int j = 0; j < mStreet; j++)
		{
			cout << myMap[i][j] << " ";
		}
		cout << "\n";
	}


	{
		int y = 10;
		int x = 10;
		vector<glm::vec3> vertices
		{
			glm::vec3(x, 0.0f, 0.0f),	// Bottom Left
			glm::vec3(0.0f,  0.0f, 0.0f),	// Bottom Right
			glm::vec3(0.0f,  0.0f, y),	// Top Right
			glm::vec3(x,  0.0f, y),	// Top Left
		};

		vector<glm::vec3> normals
		{
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0)
		};

		// TODO : Complete texture coordinates for the square
		vector<glm::vec2> textureCoords
		{
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, x),
			glm::vec2(y, x),
			glm::vec2(y, 0.0f),
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,
			0, 2, 3
		};

		Mesh* mesh = new Mesh("square");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("TextureShader");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void Tema3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::Update(float deltaTimeSeconds)
{
	if (lightPosition.x > 15) {
		lightPosition.x = -5;
	}
	lightPosition.x += moveSun * deltaTimeSeconds;
	for each (Street street in streets)
	{
		//cout << "ok" << street.corner << " " << street.l << "\n";
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, street.corner);
		RenderTextureMesh(street.streetMesh, shaders["TextureShader"], modelMatrix, mapTextures["street"]);

	}

	for each(Building b in buildings)
	{
		for each(Building s in b.subBuildings)
		{
			RenderBuilding(s);
		}
		RenderBuilding(b);
	}

	for each(Terrain t in terrains)
	{
		//cout << "ok" << street.corner << " " << street.l << "\n";
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, t.corner);
		RenderTextureMesh(t.terrainMesh, shaders["TextureShader"], modelMatrix, mapTextures["terrain"]);
	}

	for each(Ornament o in ornaments) 
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, o.corner);
		modelMatrix = glm::scale(modelMatrix, o.scale);
		modelMatrix = glm::rotate(modelMatrix, o.rot * 1.57f, glm::vec3(0.0f, 0.1f, 0.0f));
		RenderTextureMesh(o.mesh, shaders["TextureShader"], modelMatrix, o.texture);
	}
}

void Tema3::FrameEnd()
{
	//DrawCoordinatSystem();
}

void Tema3::RenderTextureMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture, Building* b)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	int light_position = glGetUniformLocation(shader->program, "light_position");
	glUniform3f(light_position, lightPosition.x, lightPosition.y, lightPosition.z);

	int light_direction = glGetUniformLocation(shader->program, "light_direction");
	glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = GetSceneCamera()->transform->GetWorldPosition();
	int eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

	// TODO: Set material property uniforms (shininess, kd, ks, object color) 
	int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(material_shininess, materialShininess);

	int material_kd = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(material_kd, materialKd);

	int material_ks = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(material_ks, materialKs);

	
	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	int loc_angle = glGetUniformLocation(shader->program, "angle");
	glUniform1f(loc_angle, angle);
	
	int building = 0;
	if (b != NULL) {
		building = 1;
		int light_positionB = glGetUniformLocation(shader->program, "light_positionB");
		glUniform3f(light_positionB, b->spotlight.x, b->spotlight.y, b->spotlight.z);

		int loc_angleB = glGetUniformLocation(shader->program, "angleB");
		glUniform1f(loc_angleB, angleS);
	}

	int loc_building = glGetUniformLocation(shader->program, "building");
	glUniform1f(loc_building, building);

	if (texture)
	{
		//TODO : activate texture location 0
		//TODO : Bind the texture1 ID
		//TODO : Send texture uniform value
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture"), 0);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema3::OnInputUpdate(float deltaTime, int mods)
{
	float speed = 2;

	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		glm::vec3 up = glm::vec3(0, 1, 0);
		glm::vec3 right = GetSceneCamera()->transform->GetLocalOXVector();
		glm::vec3 forward = GetSceneCamera()->transform->GetLocalOZVector();
		forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));

		// Control light position using on W, A, S, D, E, Q
		if (window->KeyHold(GLFW_KEY_W)) lightPosition -= forward * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_A)) lightPosition -= right * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_S)) lightPosition += forward * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_D)) lightPosition += right * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_E)) lightPosition += up * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_Q)) lightPosition -= up * deltaTime * speed;
	}
}

void Tema3::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{
}
