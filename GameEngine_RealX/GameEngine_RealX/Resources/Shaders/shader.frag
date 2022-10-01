#version 330 core
out vec4 fragColor;

struct Vertex{
	vec3 position;
	vec2 textureCords;
};

in Vertex v;

uniform float delta;
uniform sampler2D firstTexture;
uniform sampler2D secondTexture;

void main(){
	fragColor = mix(texture(firstTexture, v.textureCords), texture(secondTexture, v.textureCords), delta);
}
