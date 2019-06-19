#version 450 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;

void main(){
	//环境光
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	//漫放射光
	vec3 norm = normalize(Normal);//法向量标准化
	vec3 lightDir = normalize(lightPos-FragPos);//和光源照射方向相反的方向向量
	float diff = max(dot(norm,lightDir),0.0);//得出光照和法向量夹角的影响
	vec3 diffuse = diff*lightColor;//漫放射光源系数

	//镜面光
	float specularStrength = 0.5;//镜面亮度
	vec3 viewDir = normalize(viewPos-FragPos);//和视觉方向相反的方向向量
	vec3 reflectDir = reflect(-lightDir,norm);//光反射方向
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);//光反射方向和视觉相反方向的夹角影响
	vec3 specular = specularStrength * spec * lightColor;  //镜面光源系数


	vec3 result = (ambient + diffuse+specular)*objectColor;

	FragColor = vec4(result,1.0f);

}