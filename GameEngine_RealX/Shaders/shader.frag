#version 330 core
out vec4 fragColor;

struct Light
{
	vec3 colour;
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight
{
	Light light;
	vec3 direction;
};

struct PointLight
{
	Light light;

	vec3 position;
	float constantFactor;
	float linearFactor;
	float exponentFactor;
};

struct SpotLight
{
	PointLight light;
	vec3 direction;
	float edge;
};

struct Vertex
{
	vec3 localPosition;
	vec2 textureCords;
	vec3 normal;
	vec3 fragPos;
};

struct Camera
{
	vec3 position;
};

struct Material
{
	float shininess;
	float specularIntensity;
};

uniform Material material;

uniform Camera camera;

in Vertex v;

uniform sampler2D firstTexture;

#define MAXIMUM_NUMBER_OF_DIRECTIONAL_LIGHTS 10
uniform DirectionalLight directionalLights[MAXIMUM_NUMBER_OF_DIRECTIONAL_LIGHTS];
uniform int passedNumberOfDirectionalLights;

#define MAXIMUM_NUMBER_OF_POINT_LIGHTS 10
uniform PointLight pointLights[MAXIMUM_NUMBER_OF_POINT_LIGHTS];
uniform int passedNumberOfPointLights;

#define MAXIMUM_NUMBER_OF_SPOT_LIGHTS 10
uniform SpotLight spotLights[MAXIMUM_NUMBER_OF_SPOT_LIGHTS];
uniform int passedNumberOfSpotLights;

vec4 CalcLightByDirection(Light light, vec3 direction)
{
	vec4 ambientColour = vec4(light.colour, 1.0f) * light.ambientIntensity;
	
	float diffuseFactor = max(dot(normalize(v.normal), normalize(direction)), 0.0f);
	vec4 diffuseColour = vec4(light.colour * light.diffuseIntensity * diffuseFactor, 1.0f);
	
	vec4 specularColour = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	
	if(diffuseFactor > 0.0f)
	{
		vec3 fragToEye = normalize(camera.position - v.fragPos);
		vec3 reflectedVertex = normalize(reflect(direction, normalize(v.normal)));
		float specularFactor = dot(fragToEye, reflectedVertex);
		if(specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColour = vec4(light.colour * material.specularIntensity * specularFactor, 1.0f);
		}
	}
	
	return ambientColour + diffuseColour + specularColour;
}

vec4 CalcPointLight(PointLight pointLight)
{
	vec3 direction = v.fragPos - pointLight.position;
	float distance = length(direction);
	direction = normalize(direction);
	vec4 colour = CalcLightByDirection(pointLight.light, direction);
	float attenuation = pointLight.exponentFactor * distance * distance + pointLight.linearFactor * distance + pointLight.constantFactor;
	return (colour/attenuation);
}

vec4 CalcSpotLight(SpotLight spotLight)
{
	vec3 rayDirection = normalize(v.fragPos - spotLight.light.position);
	float slFactor = dot(rayDirection, normalize(spotLight.direction));
	if(slFactor > spotLight.edge)
	{
		vec4 colour = CalcPointLight(spotLight.light);
		return colour * (1.0f - (1.0f - slFactor)*(1.0f/(1.0f - spotLight.edge)));
	}
	else
	{
		return vec4(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

vec4 CalcSpotLights()
{
	vec4 result = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	for(int i = 0; i<passedNumberOfSpotLights; i++)
	{
		result += CalcSpotLight(spotLights[i]);
	}
	return result;
}

vec4 CalcPointLights()
{
	vec4 result = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	for(int i=0; i<passedNumberOfPointLights; i++)
	{
		result += CalcPointLight(pointLights[i]);
	}
	return result;
}

vec4 CalcDirectionalLights()
{
	vec4 result = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	for(int i=0; i<passedNumberOfDirectionalLights; i++)
	{
		result += CalcLightByDirection(directionalLights[i].light, directionalLights[i].direction);
	}
	return result;
}

void main()
{
	vec4 lights = CalcDirectionalLights() + CalcPointLights() + CalcSpotLights();
	fragColor = texture(firstTexture, v.textureCords) * lights;
}
