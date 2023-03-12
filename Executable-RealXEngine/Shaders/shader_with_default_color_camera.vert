#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCords;
layout (location = 2) in vec3 aNormal;

struct Vertex
{
	vec3 position;
	vec2 textureCords;
	vec3 normal;
};

out Vertex v;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	v.position = aPos;
	v.textureCords = aTexCords;
	v.normal = aNormal;
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}