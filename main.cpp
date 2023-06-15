#define STB_IMAGE_IMPLEMENTATION

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/glm.hpp>

using namespace glm;
#include "Window.h"
#include <iostream>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"

Texture textureOne;
Texture textureTwo;
Texture textureThree;

Window mainWindow;

Camera camera;

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f

};
unsigned int indices[] = {
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35
};
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};
//Shader Code

unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgramOne, shaderProgramTwo;

std::vector<Shader> shaderList;
std::vector<Mesh*> mesh;
glm :: vec4 vertexColor;
//ErrorChecking
int  success;
char infoLog[512];

// Vertex Shader
static const char* vShader = "Shaders/VertexShader.vert";

// Fragment Shader
static const char* fShader = "Shaders/FragmentShader.frag";

// Vertex Shader
static const char* Colour_vShader = "Shaders/1.colors.vert";

// Fragment Shader
static const char* Colour_fShader = "Shaders/1.colors.frag";

// Vertex Shader
static const char* LightCube_vShader = "Shaders/1.light_cube.vert";

// Fragment Shader
static const char* LightCube_fShader = "Shaders/1.light_cube.frag";

const char* vertexShaderSourceOne = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1);\n"
"}\0";
const char* fragmentShaderSourceOne = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1f);\n"
"}\n\0";

const char* vertexShaderSourceTwo = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1);\n"
"}\0";
const char* fragmentShaderSourceTwo = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0f, 0f, 1f);\n"
"}\n\0";


void CreateObjects() {
    Mesh* obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 288, 36);
    mesh.push_back(obj1);
}

void CreateShaders() {
	Shader* obj1 = new Shader();
	obj1->CreatFromFile(Colour_vShader, Colour_vShader);
	shaderList.push_back(*obj1);
}
// Include standard headers
int main() {

	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

	//CreateShaders();

	Shader* obj1 = new Shader();
	obj1->CreatFromFile(Colour_vShader, Colour_fShader);
	shaderList.push_back(*obj1);


	Shader* obj2 = new Shader();
	obj2->CreatFromFile(LightCube_vShader, LightCube_fShader);
	shaderList.push_back(*obj2);


	for (int i = 0; i < 2; i++) {
		CreateObjects();
	}
	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);

	textureOne = Texture("Textures/container2.png");
	textureOne.LoadPNGTexture();


	shaderList[0].SetInt("material.diffuseTexture", 0);

	textureTwo = Texture("Textures/container2_specular.png");
	shaderList[0].UseShader();
	textureTwo.LoadPNGTexture();
	shaderList[0].SetInt("material.specTexture", 1);

	textureThree = Texture("Textures/matrix.jpg");
	shaderList[0].UseShader();
	textureThree.LoadTexture();
	shaderList[0].SetInt("material.emitTexture", 2);

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	glm::mat4 view(1.0f);
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	GLfloat deltaTime;
	GLfloat lastTime = glfwGetTime();
	float scorllTime = 0;
	while (!mainWindow.getShouldClose()) {

		GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
		deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
		lastTime = now;


		glm::mat4 model(1.0f);
		float time = (float)glfwGetTime();
		glm::vec3 lightPos(1.2f,glm :: sin(time), 2.0f);
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		
		proj = glm::perspective(glm::radians(mainWindow.getFOV()), (float)800 / (float)600, 0.1f, 100.0f);
		view = camera.calculateViewMatrix();
		glm::vec3 objectColour = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
		//lightColour.x = sin(glfwGetTime() * 2.0f);
		//lightColour.y = sin(glfwGetTime() * 0.7f);
		//lightColour.z = sin(glfwGetTime() * 1.3f);

		model = glm::mat4(1.0f);

		model = glm::translate(model, lightPos);
		shaderList[1].UseShader();
		shaderList[1].SetMatFour("view", view);
		shaderList[1].SetVecThree("lightColor", lightColour);
		shaderList[1].SetMatFour("projection", proj);
		shaderList[1].SetMatFour("model", model);
		mesh[1]->RenderMesh();
		model = glm::mat4(1.0f);
		shaderList[0].UseShader();
		shaderList[0].SetMatFour("view", view);
		shaderList[0].SetMatFour("projection", proj);
		shaderList[0].SetMatFour("model", model);

		glActiveTexture(GL_TEXTURE0);
		textureOne.UseTexture();
		glActiveTexture(GL_TEXTURE1);
		textureTwo.UseTexture();
		glActiveTexture(GL_TEXTURE2);
		textureThree.UseTexture();

		shaderList[0].SetVecThree("objectColor", objectColour);
		shaderList[0].SetVecThree("lightColor", lightColour);
		shaderList[0].SetVecThree("lightPos", lightPos);
		shaderList[0].SetVecThree("viewPos", camera.position);
		shaderList[0].SetInt("material.diffuseTexture", 0);
		shaderList[0].SetInt("material.specTexture", 1);
		shaderList[0].SetInt("material.emitTexture", 2);
		shaderList[0].SetFloat("material.shininess", 32.0f);
		shaderList[0].SetFloat("scrolling", scorllTime);
		scorllTime += deltaTime * .1f;
		if (scorllTime > 1) scorllTime = 0;
		glm::vec3 diffuseColor = lightColour * glm::vec3(5.0f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
		shaderList[0].SetVecThree("light.ambient", glm::vec3(0.5f));
		shaderList[0].SetVecThree("light.diffuse", glm::vec3(0.5f)); // darken diffuse light a bit
		shaderList[0].SetVecThree("light.specular", glm::vec3(0.5f));
		shaderList[0].SetFloat("material.shininess", 32.0f);
		mesh[0]->RenderMesh();



		//shaderList[0].SetMatFour("viewSpace", view);
		//shaderList[0].SetMatFour("projectionSpace", proj);
		//shaderList[0].SetVecFour("ourColor", vertexColor);
		//shaderList[0].SetMatFour("modelMatrix", model);
		//glActiveTexture(GL_TEXTURE0);
		//textureOne.UseTexture();
		//glActiveTexture(GL_TEXTURE1);
		//textureTwo.UseTexture();

		//bool* keys = mainWindow.getsKeys();
		//GLfloat currentScrollerValue =1;
		//shaderList[0].GetFloat( "mixValue", &currentScrollerValue);
		//if (keys[GLFW_KEY_UP] == true) {
		//	currentScrollerValue += deltaTime;
		//	if (currentScrollerValue > 1) {
		//		currentScrollerValue = 1;
		//	}
		//}
		//if (keys[GLFW_KEY_DOWN] == true) {
		//	currentScrollerValue -= deltaTime;
		//	if (currentScrollerValue < 0) {
		//		currentScrollerValue = 0;
		//	}
		//}

		//shaderList[0].SetFloat("mixValue", currentScrollerValue);

		//mesh[0]->RenderMesh();
		//for (int i = 0; i < 10; i++) {
		//	model = glm::mat4(1.0f);
		//	model = glm::translate(model, cubePositions[i]);
		//	float angle = 20.0f * i;
		//	if ((i + 1) % 3 == 0 || i == 0) {
		//		GLfloat t = glfwGetTime();
		//		model = glm::rotate(model, t, glm::vec3(0.0, 0.0, 1.0));
		//	}
		//	else
		//	{
		//		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		//	}
		//	shaderList[0].SetMatFour("modelMatrix", model);
		//	mesh[i]->RenderMesh();
		//}

		glfwPollEvents();
		glUseProgram(0);
		
		mainWindow.swapBuffers();
	}
}