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

	vec3 norm = normalize(Normal);//法向量标准化
	vec3 lightDir = normalize(lightPos-FragPos);//光源位置和物体位置，得到光源方向向量

	float diff = max(dot(norm,lightDir),0.0);//得出光照和法向量夹角的影响
	vec3 diffuse = diff*lightColor;//漫放射光源系数

	vec3 result = (ambient + diffuse)*objectColor;

	FragColor = vec4(result,1.0f);

}