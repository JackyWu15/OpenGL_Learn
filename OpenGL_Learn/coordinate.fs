#version 450 core


in vec2 textureColor;
out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
	FragColor = mix(texture(texture1,textureColor),texture(texture2,textureColor),0.2);
}

