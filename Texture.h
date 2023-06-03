#include <GL/glew.h> 
#include <iostream>
#include "stb_image.h"
class Texture
{
public :
	Texture();
	Texture(const char* fileLoc);
	void LoadTexture();
	void LoadPNGTexture();
	void UseTexture();
	void ClearTexture();
	~Texture();

private :
	GLuint textureId;
	int width, height, bitDepth;
	const char* fileLocation;
};

