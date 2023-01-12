#version 430 core

layout (location = 1) in vec2 pos;

out VS_OUT {
	vec3 color;
} vs_out;

void main() {
	gl_Position = vec4(pos, 0.0f, 1.0f);
	vs_out.color = vec3(1.0, 0.0, 0.0);
}