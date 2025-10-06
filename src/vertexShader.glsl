#version 330 core
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vCol;

out vec3 fCol;

uniform mat4 viewMat;
uniform mat4 projMat;

void main() {
    fCol = vCol;
    gl_Position = projMat * viewMat * vec4(vPos, 1.0);
}