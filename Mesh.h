#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Mesh
{
public :
	void CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void RenderMesh();
	void ClearMesh();
	Mesh();
	~Mesh();
private :
	unsigned int VBO;
	unsigned int VAO;
	unsigned int IBO;
	unsigned int IndexCount;
};

