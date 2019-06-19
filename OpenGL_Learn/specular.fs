#version 450 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;

void main(){
	//������
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	//�������
	vec3 norm = normalize(Normal);//��������׼��
	vec3 lightDir = normalize(lightPos-FragPos);//�͹�Դ���䷽���෴�ķ�������
	float diff = max(dot(norm,lightDir),0.0);//�ó����պͷ������нǵ�Ӱ��
	vec3 diffuse = diff*lightColor;//�������Դϵ��

	//�����
	float specularStrength = 0.5;//��������
	vec3 viewDir = normalize(viewPos-FragPos);//���Ӿ������෴�ķ�������
	vec3 reflectDir = reflect(-lightDir,norm);//�ⷴ�䷽��
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);//�ⷴ�䷽����Ӿ��෴����ļн�Ӱ��
	vec3 specular = specularStrength * spec * lightColor;  //�����Դϵ��


	vec3 result = (ambient + diffuse+specular)*objectColor;

	FragColor = vec4(result,1.0f);

}