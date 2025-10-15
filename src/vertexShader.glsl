#version 330 core            // Minimal GL version support expected from the GPU

layout(location=0) in vec3 vPosition;
layout(location=2) in vec3 vNormal;

out vec3 fPosition;
out vec3 fNormal;

uniform mat4 viewMat, projMat, modelMat;

void main() {
        vec4 worldPos = modelMat * vec4(vPosition, 1.0);
        fPosition = worldPos.xyz;

        fNormal = mat3(modelMat) * vNormal;

        gl_Position = projMat * viewMat * worldPos; // mandatory to rasterize properly
}
