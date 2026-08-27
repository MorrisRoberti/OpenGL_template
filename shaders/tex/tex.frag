#version 330 core

out vec4 FragColor;

in vec2 vTexCoord0;

uniform sampler2D gSampler;

void main() {

   FragColor = texture2D(gSampler, vTexCoord0);

}
