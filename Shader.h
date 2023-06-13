#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <GL\glew.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
class Shader
{
public :
	Shader();
	~Shader();
	void CreatFromFile(const char* vertexCodeLocation, const char* fragmentCodeLocation);
	void CreatFromString(const char* vertecCodeString, const char* fragmentCodeString);
	std::string ReadFile(const char* fileLocation);
	void UseShader();
	//void ClearShader();
	void SetInt(const char* id, GLint value);
	void SetFloat(const char* id, GLfloat value);
	void SetBool(const char* id, GLboolean value);
	void SetVecFour(const char* id, glm::vec4 value);
	void SetMatFour(const char* id, glm::mat4 value);
	void SetVecThree(const char* id, glm::vec3 value);
	void GetFloat(const char* id, GLfloat* value);
private:
	int ShaderID;
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint programId, const char* theCode, GLenum shaderType);
};

