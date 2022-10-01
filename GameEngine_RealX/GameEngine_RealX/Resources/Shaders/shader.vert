#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCords;

struct Vertex{
	vec3 position;
	vec2 textureCords;
};

out Vertex v;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	v.position = aPos;
	v.textureCords = aTexCords;
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}
