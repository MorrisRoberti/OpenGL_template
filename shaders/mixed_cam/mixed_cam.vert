#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int hasTexture;

out vec3 vPosition;
out vec2 vTexCoord0;
out vec3 vColor;

void main() {

    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    if(hasTexture == 1){
    vTexCoord0 = aTexCoord;
    }else {
   
        vColor=aColor;
        
    }
}