#version 450 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

void main(){
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);//��������׼��
	vec3 lightDir = normalize(lightPos-FragPos);//��Դλ�ú�����λ�ã��õ���Դ��������

	float diff = max(dot(norm,lightDir),0.0);//�ó����պͷ������нǵ�Ӱ��
	vec3 diffuse = diff*lightColor;//�������Դϵ��

	vec3 result = (ambient + diffuse)*objectColor;

	FragColor = vec4(result,1.0f);

}