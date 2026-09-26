#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in mat4 aInstanceMatrix;

uniform mat4 view;
uniform mat4 projection;

out vec3 vPosition;
out vec2 vTexCoord0;

void main() {

    gl_Position = projection * view * aInstanceMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vTexCoord0 = aTexCoord;
}