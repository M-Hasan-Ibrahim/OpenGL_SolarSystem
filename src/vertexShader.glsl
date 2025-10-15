#version 330 core            // Minimal GL version support expected from the GPU

layout(location=0) in vec3 vPos;
layout(location=1) in vec3 vCol;

out vec3 fCol;

uniform mat4 viewMat, projMat, modelMat;

void main() {
        fCol = vCol;
        gl_Position = projMat * viewMat * modelMat * vec4(vPos, 1.0); // mandatory to rasterize properly
}
