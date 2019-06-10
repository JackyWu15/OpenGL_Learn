#version 450 core
in vec3 vertexColor;//in: 接收顶点着色器的变量值，类型和名字必须一致
in vec2 textureColor;

out vec4 FragColor;//out：声明了最后输出的颜色  vec4:4分量 FragColor:变量名

uniform sampler2D texture1;//纹理采样器，纹理坐标的确定相当于在屏幕坐标上钉上了一张画布，采样器根据纹理坐标将纹理颜色采集到画布上
uniform sampler2D texture2;

void main()
{
   //FragColor = vertexColor;//颜色：0.0-1.0，RGBA
   FragColor = mix(texture(texture1,textureColor),texture(texture2,textureColor),0.2);//0.2表示取80%第一个纹理的颜色，20%第二个纹理的颜色
  // FragColor = mix(texture(texture1,textureColor),texture(texture2,textureColor),0.2)*vec4(vertexColor,1.0);//混合颜色
   
}