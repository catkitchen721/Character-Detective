#version 430 core

out vec4 FragColor;

in VS_OUT {
	vec3 color;
} fs_in;

void main() {
	FragColor = vec4(fs_in.color, 1.0);
}