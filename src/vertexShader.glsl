#version 330 core            // Minimal GL version support expected from the GPU

layout(location=0) in vec3 vPosition;
layout(location=2) in vec3 vNormal;
layout(location=3) in vec2 vTexture;

out vec3 fPosition;
out vec3 fNormal;
out vec2 fTexture;

uniform mat4 viewMat, projMat, modelMat;

void main() {
        vec4 worldPos = modelMat * vec4(vPosition, 1.0);
        
        fPosition = worldPos.xyz;

        fNormal = mat3(transpose(inverse(modelMat))) * vNormal;

        fTexture = vTexture;

        gl_Position = projMat * viewMat * worldPos;
}
