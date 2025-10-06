#version 330 core

in vec3 fCol;
out vec4 color;
void main() {
	color = vec4(fCol, 1.0);
}
