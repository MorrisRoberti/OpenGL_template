#version 330 core

out vec4 FragColor;

in vec2 vTexCoord0;
in vec3 vColor;

uniform sampler2D gSampler;
uniform int hasTexture;

void main() {

   if(hasTexture == 1){
   FragColor = texture2D(gSampler, vTexCoord0);
   }else {
    FragColor = vec4(vColor, 1.0f);
   }

}
