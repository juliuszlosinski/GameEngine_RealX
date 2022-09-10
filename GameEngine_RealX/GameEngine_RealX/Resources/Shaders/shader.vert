#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 0) in vec3 aColor;
layout (location = 0) in vec2 aTexCords;

struct Vertex{
	vec3 ndcPosition;
	vec3 color;
	vec2 texCords;
};

out Vertex v;
uniform float delta;

void main(){
	v.ndcPosition = aPos;
	v.texCords = aTexCords;
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
}
