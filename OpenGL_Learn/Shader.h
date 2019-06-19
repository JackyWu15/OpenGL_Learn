#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>



using namespace std;
class  Shader {
public:
	unsigned int ID;
	 Shader(const char *vertexPath,const char *fragmentPath);
	~ Shader();

private:
	void checkCompileErrors(unsigned int shader, std::string type);
public:
	void use();
	void setBool(const std::string &name, bool value)const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
};

 Shader:: Shader(const char *vertexPath, const char *fragmentPath) {
	 string vertexCode;
	 string fragmentCode;
	 ifstream vShaderFile;
	 ifstream fShaderFile;
	 vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	 fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	 try
	 {
		 vShaderFile.open(vertexPath);
		 fShaderFile.open(fragmentPath);
		 stringstream vShaderStream, fShaderStream;
		 vShaderStream<<vShaderFile.rdbuf();
		 fShaderStream << fShaderFile.rdbuf();
		 vShaderFile.close();
		 fShaderFile.close();

		 vertexCode = vShaderStream.str();
		 fragmentCode = fShaderStream.str();
	 }
	 catch (ifstream::failure e)
	 {
		 cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
	 }

	 const char *vShaderCode = vertexCode.c_str();
	 const char *fShaderCode = fragmentCode.c_str();

	 //Брвы
	 unsigned int vertex, fragment;
	 vertex =  glCreateShader(GL_VERTEX_SHADER);
	 glShaderSource(vertex,1,&vShaderCode,NULL);
	 glCompileShader(vertex);

	 checkCompileErrors(vertex,"VERTEX");

	 fragment = glCreateShader(GL_FRAGMENT_SHADER);
	 glShaderSource(fragment,1,&fShaderCode,NULL);
	 glCompileShader(fragment);

	 checkCompileErrors(fragment, "FRAGMENT");

	 ID = glCreateProgram();
	 glAttachShader(ID,vertex);
	 glAttachShader(ID,fragment);
	 glLinkProgram(ID);
	 checkCompileErrors(ID, "PROGRAM");

	 glDeleteShader(vertex);
	 glDeleteShader(fragment);

}

 Shader::~ Shader() {
}



 void Shader::use() {
	 glUseProgram(ID);
 }


 void Shader::setBool(const std::string &name, bool value) const {
	 glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
 }
 // ------------------------------------------------------------------------
 void Shader::setInt(const std::string &name, int value) const {
	 glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
 }
 // ------------------------------------------------------------------------
 void Shader::setFloat(const std::string &name, float value) const {
	 glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
 }

 inline void Shader::setMat4(const std::string & name, const glm::mat4 & mat) const {
	 glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
 }


 void Shader::setVec3(const std::string &name, float x, float y, float z) const {
	 glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
 }
 void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
	 glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
 }
 inline void Shader::checkCompileErrors(unsigned int shader, std::string type) {
	 int success;
	 char infoLog[512];

	 if (type != "PROGRAM") {
		 glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
		 if (!success) {
			 glGetShaderInfoLog(shader,512,NULL,infoLog);
			 std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		 }
	 } else {
		 glGetProgramiv(shader, GL_COMPILE_STATUS, &success);
		 if (!success) {
			 glGetProgramInfoLog(shader, 512, NULL, infoLog);
			 std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		 }
	 }

 }
