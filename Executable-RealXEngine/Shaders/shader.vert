#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCords;
layout (location = 2) in vec3 aNormal;

struct Vertex
{
	vec3 localPosition;
	vec2 textureCords;
	vec3 normal;
	vec3 fragPos;
};

out Vertex v;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	v.localPosition = aPos;
	v.textureCords = aTexCords;
	v.normal = mat3(transpose(inverse(model))) * aNormal;
	v.fragPos = vec3(model * vec4(aPos, 1.0));
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}
