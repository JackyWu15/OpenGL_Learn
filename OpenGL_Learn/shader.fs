#version 450 core
in vec3 vertexColor;//in: ���ն�����ɫ���ı���ֵ�����ͺ����ֱ���һ��
in vec2 textureColor;

out vec4 FragColor;//out������������������ɫ  vec4:4���� FragColor:������

uniform sampler2D texture1;//��������������������ȷ���൱������Ļ�����϶�����һ�Ż����������������������꽫������ɫ�ɼ���������
uniform sampler2D texture2;

void main()
{
   //FragColor = vertexColor;//��ɫ��0.0-1.0��RGBA
   FragColor = mix(texture(texture1,textureColor),texture(texture2,textureColor),0.2);//0.2��ʾȡ80%��һ���������ɫ��20%�ڶ����������ɫ
  // FragColor = mix(texture(texture1,textureColor),texture(texture2,textureColor),0.2)*vec4(vertexColor,1.0);//�����ɫ
   
}