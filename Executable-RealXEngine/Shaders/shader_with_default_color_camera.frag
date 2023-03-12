#version 330 core
out vec4 fragColor;

struct Vertex
{
	vec3 position;
	vec2 textureCords;
	vec3 normal;
};

in Vertex v;

void main()
{
	fragColor = vec4(1.0f);
}