#version 330 core
out vec4 FragColor;
  
struct Material {
    sampler2D diffuseTexture;
    sampler2D specTexture;
	sampler2D emitTexture;
    float shininess;
}; 
  
uniform Material material;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;  
uniform vec3 viewPos;
uniform float scrolling;

struct Light {
    vec3 position;  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;  

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoord;


void main()
{
    float ambientStrength = 0.1;
	float specularStrength = 1.0;
    vec3 ambient = vec3(texture(material.diffuseTexture, TexCoord))  * light.ambient;
	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);  
	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * vec3(texture(material.diffuseTexture, TexCoord))) * light.diffuse;
	
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular =  (vec3(texture(material.specTexture, TexCoord)) * spec )* light.specular;  
	vec2 cordinate = TexCoord;
	cordinate.y += scrolling;
	vec3 colour = vec3(1.5f);
	vec2 centeredCordinate = TexCoord - vec2(.5);
	if(centeredCordinate.x > .42)
		colour = vec3(0);
	else if(centeredCordinate.y > .42)
		colour = vec3(0);
	else if(centeredCordinate.x < -0.42)
		colour = vec3(0);
	else if(centeredCordinate.y < -0.42)
		colour = vec3(0);
	
	vec3 data = (vec3(1.0) - vec3(texture(material.specTexture, TexCoord)));
	
	vec3 emission= vec3(texture(material.emitTexture, cordinate)) *  colour;
	
    vec3 result = (specular + ambient + diffuse + emission);
    FragColor = vec4(result, 1.0);
}