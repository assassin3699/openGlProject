#include "Shader.h"

Shader::Shader()
{
	ShaderID = 0;
}

Shader::~Shader()
{
	if (ShaderID != 0)
	{
		glDeleteProgram(ShaderID);
		ShaderID = 0;
	}
}

void Shader::CreatFromFile(const char* vertexCodeLocation, const char* fragmentCodeLocation)
{
	std::string vertexString = ReadFile(vertexCodeLocation);
	std::string fragmentString = ReadFile(fragmentCodeLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();
	CompileShader(vertexCode, fragmentCode);
}

void Shader::CreatFromString(const char* vertecCodeString, const char* fragmentCodeString)
{
	CompileShader(vertecCodeString, fragmentCodeString);
}

std::string Shader::ReadFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s! File doesn't exist.", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::UseShader()
{
	glUseProgram(ShaderID);
}

void Shader::ClearShader()
{
	if (ShaderID != 0)
	{
		glDeleteProgram(ShaderID);
		ShaderID = 0;
	}
}

void Shader::SetInt(const char* id, GLint value)
{
	glUniform1i(glGetUniformLocation(ShaderID, id), value);
}

void Shader::SetFloat(const char* id, GLfloat value)
{
	glUniform1f(glGetUniformLocation(ShaderID, id), value);
}

void Shader::SetBool(const char* id, GLboolean value)
{
	glUniform1i(glGetUniformLocation(ShaderID, id), (int)value);
}

void Shader::SetVecFour(const char* id, glm::vec4 value)
{
	glUniform4f(glGetUniformLocation(ShaderID, id), value.x,value.y,value.z,value.w);
}
void Shader::SetVecThree(const char* id, glm::vec3 value)
{
	glUniform3f(glGetUniformLocation(ShaderID, id), value.x, value.y, value.z);
}

void Shader::SetMatFour(const char* id, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(ShaderID, id), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::GetFloat(const char* id, GLfloat * value)
{
	glGetUniformfv(ShaderID, glGetUniformLocation(ShaderID, id), value);
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	int success;
	char infoLog[512];
	ShaderID = glCreateProgram();
	AddShader(ShaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(ShaderID, fragmentCode, GL_FRAGMENT_SHADER);
	glLinkProgram(ShaderID);
	glGetProgramiv(ShaderID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ShaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

}

void Shader::AddShader(GLuint programId, const char* theCode, GLenum shaderType)
{
	int success;
	char infoLog[512];
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theShaderCode[1];
	theShaderCode[0] = theCode;

	GLint codeLength[1];
	codeLength[0] = strlen(theCode);

	glShaderSource(theShader, 1, theShaderCode, codeLength);
	glCompileShader(theShader);

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(theShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	glAttachShader(programId, theShader);
}
