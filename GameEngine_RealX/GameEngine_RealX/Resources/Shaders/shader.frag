#version 330 core
out vec4 fragColor;

struct Vertex{
	vec3 ndcPosition;
	vec3 color;
	vec2 texCords;
};

in Vertex v;

uniform sampler2D firstTexture;
uniform sampler2D secondTexture;

void main(){
	fragColor = texture(firstTexture, v.texCords);
}
