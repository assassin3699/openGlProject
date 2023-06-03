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

Texture textureOne;
Texture textureTwo;

Window mainWindow;



float vertices[] = {

	 -0.5f,  -0.5f,  0.0f,       0.0f, 0.0f, 
	 -0.5f,   0.5f,  0.0f,       0.0f, 1.0f,
	  0.5f,   0.5f,  0.0f,       1.0f, 1.0f,
	  0.5f,  -0.5f,  0.0f,		 1.0f, 0.0f,
	 -0.5f,  -0.5f, -0.5f,       0.0f, 0.0f,
	 -0.5f,   0.5f, -0.5f,       0.0f, 1.0f,
	  0.5f,   0.5f, -0.5f,       1.0f, 1.0f,
	  0.5f,  -0.5f, -0.5f,		 1.0f, 0.0f
};
unsigned int indices[] = {
	0 , 1 , 2 , 0 , 2 , 3   
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
    obj1->CreateMesh(vertices, indices, 20, 6);
    mesh.push_back(obj1);
}

void CreateShaders() {
	Shader* obj1 = new Shader();
	obj1->CreatFromFile(vShader, fShader);
	shaderList.push_back(*obj1);
}
// Include standard headers
int main() {

	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	 
	CreateShaders();
    CreateObjects();
	CreateObjects();
	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);

	textureOne = Texture("Textures/container.jpg");
	textureOne.LoadTexture();
	shaderList[0].UseShader();

	shaderList[0].SetInt("textureone", 0);

	textureTwo = Texture("Textures/awesomeface.png");
	shaderList[0].UseShader();
	textureTwo.LoadPNGTexture();
	shaderList[0].SetInt("texturetwo", 1);






	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	GLfloat deltaTime;
	GLfloat lastTime = glfwGetTime();
	while (!mainWindow.getShouldClose()) {

		GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
		deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
		lastTime = now;


		glm::mat4 model(1.0f);

		model = glm::translate(model, glm::vec3(0.5f, -0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		shaderList[0].UseShader();
		shaderList[0].SetMatFour("viewSpace", view);
		shaderList[0].SetMatFour("projectionSpace", proj);
		//shaderList[0].SetVecFour("ourColor", vertexColor);
		shaderList[0].SetMatFour("modelMatrix", model);
		glActiveTexture(GL_TEXTURE0);
		textureOne.UseTexture();
		glActiveTexture(GL_TEXTURE1);
		textureTwo.UseTexture();

		bool* keys = mainWindow.getsKeys();
		GLfloat currentScrollerValue =1;
		shaderList[0].GetFloat( "mixValue", &currentScrollerValue);
		if (keys[GLFW_KEY_UP] == true) {
			currentScrollerValue += deltaTime;
			if (currentScrollerValue > 1) {
				currentScrollerValue = 1;
			}
		}
		if (keys[GLFW_KEY_DOWN] == true) {
			currentScrollerValue -= deltaTime;
			if (currentScrollerValue < 0) {
				currentScrollerValue = 0;
			}
		}
		shaderList[0].SetFloat("mixValue", currentScrollerValue);
		mesh[0]->RenderMesh();

		model = glm::mat4 (1.0f);
		model = glm::translate(model, glm::vec3(-0.5f, 0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(glm :: sin(glfwGetTime()), glm::sin(glfwGetTime()), 1));
		shaderList[0].SetMatFour("modelMatrix", model);
		mesh[1]->RenderMesh();
		glfwPollEvents();
		glUseProgram(0);
		mainWindow.swapBuffers();
	}
}