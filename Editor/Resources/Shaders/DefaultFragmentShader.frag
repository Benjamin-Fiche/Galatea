#version 450 core
#define MAX_LIGHTS_NUMBER 50

layout(binding = 0) uniform sampler2D diffuseTexture;
layout(binding = 1) uniform sampler2D ambientTexture;
layout(binding = 2) uniform sampler2D specularTexture;
layout(binding = 3) uniform sampler2D emissiveTexture;
layout(binding = 4) uniform sampler2D bumpTexture;    //normalMap

out vec4 gl_FragColor;

in VS_OUT
{
    vec2 uv;
    vec3 normal;
    vec3 vertPos;
    vec3 viewDir;
    mat3 reverseTBN;
} fs_in;

struct Light
{  
    bool    isActive;
	int	    type;
   
    float   power;
    float   shininess;
    float   cutOff;
    float   outerCutOff;

    vec3    diffuse;
    vec3    specular;
    vec3    color;

    vec3    direction;
    vec3    attenuation;

    vec3    position;
};

struct Material
{
    float   shininess;
    float   opacity;
    float   transparencyFactor;
    float   reflectivity;
    float   bumpScaling;

    vec3    ambient;
    vec3    specular;
    vec3    diffuse;
    vec3    emissive;
    vec3    reflective;
};

uniform Light       lights[MAX_LIGHTS_NUMBER];
uniform Material    material;
uniform int         lightNumber;

vec3 AddLightFunction(Light _light, vec3 _norm, vec3 _viewDir);

void main()
{
    vec3 texColor = vec3(texture(diffuseTexture, fs_in.uv));
    vec3 result = material.ambient * texColor;

    vec3 norm = normalize(fs_in.reverseTBN * (vec3(texture(bumpTexture, fs_in.uv)) * 2.0 - 1.0));    //Convert tangent space to world space
    norm *= material.bumpScaling;

    for (int index = 0; index < lightNumber && index < MAX_LIGHTS_NUMBER; ++index)
        result += AddLightFunction(lights[index], norm, fs_in.viewDir) * texColor;

    //gl_FragColor = vec4(pow(result, vec3(1 / 2.2)), 1.0);
    gl_FragColor = vec4(result, 1.0);
}

vec3 PointLightFunction(Light _light, vec3 _norm, vec3 _viewDir);
vec3 SpotLightFunction(Light _light, vec3 _norm, vec3 _viewDir);
vec3 DirectionalLightFunction(Light _light, vec3 _norm, vec3 _viewDir);

vec3 AddLightFunction(Light _light, vec3 _norm, vec3 _viewDir)
{
	switch(_light.type)
    {
        case 0:
            return PointLightFunction(_light, _norm, _viewDir);
        case 1:
            return SpotLightFunction(_light, _norm, _viewDir);
        case 2:
            return DirectionalLightFunction(_light, _norm, _viewDir);
    }

    return vec3(0);
}

vec3 PointLightFunction(Light _light, vec3 _norm, vec3 _viewDir)
{
    if (!_light.isActive)
        return vec3(0.0);
    vec3 lightDir = normalize(_light.position - fs_in.vertPos);

	float distance = length(_light.position - fs_in.vertPos);
	float attenuation = 1 / (_light.attenuation.x + _light.attenuation.y * distance + _light.attenuation.z * (distance * distance));

    float diff = max(dot(_norm, lightDir), 0.0);
    vec3 diffuse = diff * _light.diffuse * material.diffuse;

    vec3 reflectDir = reflect(-lightDir, _norm);  
    float spec = pow(max(dot(_viewDir, reflectDir), 0.0), _light.shininess + material.shininess);
    vec3 specular = spec * _light.specular * material.specular;

    return attenuation * (diffuse + specular) * (_light.color * _light.power);
}

vec3 SpotLightFunction(Light _light, vec3 _norm, vec3 _viewDir)
{
    if (!_light.isActive)
        return vec3(0.0);
    
    // diffuse 
    vec3 lightDir = normalize(_light.position - fs_in.vertPos);
    float diff = max(dot(_norm, lightDir), 0.0);
    vec3 diffuse = _light.diffuse * diff * material.diffuse;  
    
    // specular
    vec3 reflectDir = reflect(-lightDir, _norm);  
    float spec = pow(max(dot(_viewDir, reflectDir), 0.0), material.shininess + _light.shininess);
    vec3 specular = _light.specular * spec * material.specular;  
    
    // spotlight (soft edges)
    float theta = dot(lightDir, normalize(-_light.direction)); 
    float epsilon = (_light.cutOff - _light.outerCutOff);
    float intensity = clamp((theta - _light.outerCutOff) / epsilon, 0.0, 1.0);
    
    // attenuation
    float distance    = length(_light.position - fs_in.vertPos);
    float attenuation = 1.0 / (_light.attenuation.x + _light.attenuation.y * distance + _light.attenuation.z * (distance * distance));      
        
    return attenuation * (diffuse + specular) * intensity * _light.color * _light.power;
}

vec3 DirectionalLightFunction(Light _light, vec3 _norm, vec3 _viewDir)
{
    if (!_light.isActive)
        return vec3(0.0);
   	vec3 lightDir = normalize(-_light.direction);

	float diff = max(dot(_norm, lightDir), 0.0);
	vec3 diffuse = diff * _light.diffuse * material.diffuse;

	vec3 reflectDir = reflect(lightDir, _norm);
	float spec = pow(max(dot(_viewDir, reflectDir), 0.0), _light.shininess + material.shininess);
    vec3 specular = spec * _light.specular * material.specular;

    return (diffuse + specular) * (_light.color * _light.power);
}