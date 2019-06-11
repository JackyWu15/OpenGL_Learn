#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexture;

out vec2 textureColor;

uniform mat4 transform;

void main(){
	gl_Position  = transform * vec4(aPos,1.0);//æÿ’Ûœ‡≥À
	textureColor = vec2(aTexture.x,aTexture.y);

}