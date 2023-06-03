#version 330 
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D textureone;
uniform sampler2D texturetwo;
uniform float mixValue;

void main()
{
	vec4 texone = texture(texturetwo, TexCoord);
	
    FragColor =   mix (texture(textureone, TexCoord), texture(texturetwo, vec2(TexCoord.x, 1.0 - TexCoord.y)), mixValue);
}