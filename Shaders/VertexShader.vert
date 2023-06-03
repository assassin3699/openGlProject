#version 330 
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewSpace;
uniform mat4 projectionSpace;

void main()
{
   gl_Position = projectionSpace * viewSpace *  modelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1);
   ourColor = aPos;
   TexCoord = texCoord;
}