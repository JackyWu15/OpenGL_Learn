#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexture;

out vec3 vertexColor;
out vec2 textureColor;

void main()
{
   gl_Position = vec4(aPos, 1.0);//1.0:w∑÷¡ø£¨
   vertexColor = aColor;
   textureColor = vec2(aTexture.x,aTexture.y);
}