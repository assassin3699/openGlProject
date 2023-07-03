#version 330 core
out vec4 FragColor;
  
struct Material {
    sampler2D diffuseTexture;
    sampler2D specTexture;
	sampler2D emitTexture;
    float shininess;
}; 
  
uniform Material material;

uniform vec3 viewPos;
uniform float scrolling;

struct SpotLight {
    vec3  position;
    vec3  direction;
    float cutOff;
	float outerCutOff;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
}; 

struct DirectionLight{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constant;
    float linear;
    float quadratic;
};
#define NR_POINT_LIGHTS 4  

uniform DirectionLight directionLight;
uniform PointLight pointLight[NR_POINT_LIGHTS];
uniform SpotLight spotLight;  

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoord;

vec3 CalculateDirectionLight(DirectionLight light, vec3 normal, vec3 viewDir ){
	vec3 ambient = vec3(texture(material.diffuseTexture, TexCoord))  * light.ambient;
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(-light.direction);  
	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * vec3(texture(material.diffuseTexture, TexCoord))) * light.diffuse;
	
	vec3 reflectDir = reflect(-lightDir, norm);  
	
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular =  (vec3(texture(material.specTexture, TexCoord)) * spec )* light.specular;  
	
	return (ambient+ diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 viewDir , vec3 fragPosition){

	vec3 ambient = vec3(texture(material.diffuseTexture, TexCoord))  * light.ambient;
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPosition);  
	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * vec3(texture(material.diffuseTexture, TexCoord))) * light.diffuse;
	
	vec3 reflectDir = reflect(-lightDir, norm);  
	
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular =  (vec3(texture(material.specTexture, TexCoord)) * spec )* light.specular;  
	
	float distance    = length(light.position - fragPosition);
	float attenuation = 1.0 / (light.constant + light.linear * distance + 
    		    light.quadratic * (distance * distance)); 
	specular *= attenuation;
	ambient *= attenuation;
	diffuse *= attenuation;
	
	return (ambient+ diffuse + specular);
}

vec3 ClaculateSpotLight(SpotLight light, vec3 normal, vec3 viewDir , vec3 fragPosition){
	vec3 ambient = vec3(texture(material.diffuseTexture, TexCoord))  * light.ambient;
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPosition);  
	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * vec3(texture(material.diffuseTexture, TexCoord))) * light.diffuse;
	
	vec3 reflectDir = reflect(-lightDir, norm);  
	
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular =  (vec3(texture(material.specTexture, TexCoord)) * spec )* light.specular;  
	
	float distance    = length(light.position - fragPosition);
	float attenuation = 1.0 / (light.constant + light.linear * distance + 
    		    light.quadratic * (distance * distance)); 
	specular *= attenuation;
	ambient *= attenuation;
	diffuse *= attenuation;
	
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); 
	
	diffuse  *= intensity;
	specular *= intensity;
	
	return  (specular + ambient + diffuse );
}

void main()
{
	vec3 viewDir = normalize(FragPos - viewPos);
	 vec3 result = CalculateDirectionLight(directionLight, Normal, viewDir);
	
	
	for(int i = 0 ; i < NR_POINT_LIGHTS ; i++){
		result += CalculatePointLight(pointLight[i],Normal,viewDir, FragPos);
	}
	vec3 spot = ClaculateSpotLight(spotLight,Normal,viewDir,FragPos);
	result = result + spot;
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
	

    FragColor = vec4(result, 1.0);
}