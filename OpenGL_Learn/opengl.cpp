#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "Shader.h"
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;



////������ɫ��ִ�д���
//const char *vertexShaderSource = "#version 450 core\n"//ָ��opengl�İ汾�����������4.5���Ĵ���
//"layout (location = 0) in vec3 aPos;\n"//layout�����ӵ��������� (location = 0):�趨�����������λ�� in:�������е����붥������ vec3����ʾ�˿ռ���һ������3ά������ʾ apos:������
//"out vec4 vertexColor;\n" //out : �����������
//"void main()\n"//�������
//"{\n"
//"   gl_Position = vec4(aPos, 1.0);\n"//vec.w��͸�ӳ���������������ת��Ϊ4��������ֵ���������
//"   vertexColor = vec4(0.5,0.0,0.0,1.0);\n"//������ɫֵ
//"}\0";


//������ɫ��ִ�д���
const char *vertexShaderSource = "#version 450 core\n"//ָ��opengl�İ汾�����������4.5���Ĵ���
"layout (location = 0) in vec3 aPos;\n"//0:������������Ϊ0
"layout (location = 1) in vec3 aColor;\n"//1:��ɫ��������Ϊ1
"out vec3 vertexColor;\n" //out : �����������
"void main()\n"//�������
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"//vec.w��͸�ӳ���������������ת��Ϊ4��������ֵ���������
"   vertexColor = aColor;\n"//������ɫֵ
"}\0";

////ƬԪ��ɫ��ִ�д���
//const char *fragmentShaderSource = "#version 450 core\n"
//"in vec4 vertexColor;\n"//in: ���ն�����ɫ���ı���ֵ�����ͺ����ֱ���һ��
//"out vec4 FragColor;\n"//out������������������ɫ  vec4:4���� FragColor:������
//"void main()\n"
//"{\n"
////"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"//��ɫ��0.0-1.0��RGBA
//"   FragColor = vertexColor;\n"//��ɫ��0.0-1.0��RGBA
//"}\n\0";



////uniform ��ÿ����ɫ���ж��Ƕ�һ�޶��ģ������Ա���ɫ�������������ɫ��������׶η��ʡ��ڶ����������uniformֵ���ó�ʲô��uniform��һֱ�������ǵ����ݣ�ֱ�����Ǳ����û���£����ƶ�һ����̬���������ⲿ����
//const char *fragmentShaderSource = "#version 450 core\n"
//"out vec4 FragColor;\n"//out������������������ɫ  vec4:4���� FragColor:������
//"uniform vec4 ourColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = ourColor;\n"//��ɫ��0.0-1.0��RGBA
//"}\n\0";



const char *fragmentShaderSource = "#version 450 core\n"
"in vec3 vertexColor;\n"//in: ���ն�����ɫ���ı���ֵ�����ͺ����ֱ���һ��
"out vec3 FragColor;\n"//out������������������ɫ  vec4:4���� FragColor:������
"void main()\n"
"{\n"
//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"//��ɫ��0.0-1.0��RGBA
"   FragColor = vertexColor;\n"//��ɫ��0.0-1.0��RGBA
"}\n\0";

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float deltaTime = 0.0f;//��һ֡�ķѵ�ʱ��
float lastFrame = 0.0f;//��һ֡��ʼʱ��

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);//���λ��
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f,-1.0f);//ԭ��λ��
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);//���ϵ�����

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)//��ǰ
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)//���
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)//����
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)//����
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

bool firstMouse = true;
float yaw = -90.0f;	
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

//����ƶ�
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; 
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; 
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}


//������
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}

int main(int argc,char *argv[]){
	glfwInit();//��ʼ��glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.5);//���汾ʹ��opengl 4.x �汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4.5);//�ΰ汾ʹ��opengl 4.x �汾
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//ֻʹ��opengl���Ĵ����

	//��������
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	
	glfwMakeContextCurrent(window);//�Ѵ�������������Ϊ��ǰ�̵߳���������

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//���ô���仯�ļ���

	glfwSetCursorPosCallback(window, mouse_callback);//����ƶ�����

	glfwSetScrollCallback(window, scroll_callback);//����������

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//�������¼�

	//��ʼ��glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}


	

	////������ɫ��
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);

	////װ�ش��룬�����룬��������.o�������ļ�
	//glShaderSource(vertexShader,1,&vertexShaderSource,NULL);//1:�ַ�������
	//glCompileShader(vertexShader);

	////��ȡ����״̬
	//int success;
	//char infoLog[512];
	//glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
	//if (!success) {
	//	glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
	//	cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog <<endl;
	//	return -1;
	//}

	////ƬԪ��ɫ��
	//unsigned int fragmentShader;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	//glCompileShader(fragmentShader);
	//glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
	//if (!success) {
	//	glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
	//	cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	//	return -1;
	//}

	////��������ɫ���ϲ������ӳ�һ�������������ɿ�ִ���ļ�
	//unsigned int shaderProgram;
	//shaderProgram =	glCreateProgram();
	//glAttachShader(shaderProgram,vertexShader);
	//glAttachShader(shaderProgram,fragmentShader);
	//glLinkProgram(shaderProgram);

	//glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
	//if (!success) {
	//	glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
	//	cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	//}
	//
	//
	//glDeleteShader(vertexShader);//ɾ���������
	//glDeleteShader(fragmentShader);

		////���ڲ�ѯ������ɫ�������
	//int nrAttributes;
	//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	//std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;


	//Shader ourShader("shader.vs", "shader.fs");
	//Shader ourShader("transform.vs", "shader.fs");
	Shader ourShader("coordinate.vs", "coordinate.fs");

	////�����ζ�������
	//float vertices[] = {
	//-0.5f, -0.5f, 0.0f,
	// 0.5f, -0.5f, 0.0f,
	// 0.0f,  0.5f, 0.0f
	//};

	////������ɫ����
	//float vertices[] = {
	//	// λ��              // ��ɫ
	//	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
	//	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
	//	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
	//};

	////���ζ�������
	//float vertices[] = {
	//	// positions  -        // texture coords
	//	 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
	//	 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
	//	-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	//};				   


	////���δ���ɫ��������
	//float vertices[] = {		
	//		//��������		//��ɫ			// ��������
	//	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,1.0f, // top right
	//	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,0.0f,// bottom right
	//	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,0.0f, // bottom left
	//	-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,1.0f  // top left 
	//};


	////��������
	//unsigned int indices[] = {
	//	0,1,3,
	//	1,2,3
	//};


	//�����嶥������
	float vertices[] = {
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	//ƽ����������
	glm::vec3 cubePositions[] = {
	   glm::vec3(0.0f,  0.0f,  0.0f),
	   glm::vec3(2.0f,  5.0f, -15.0f),
	   glm::vec3(-1.5f, -2.2f, -2.5f),
	   glm::vec3(-3.8f, -2.0f, -12.3f),
	   glm::vec3(2.4f, -0.4f, -3.5f),
	   glm::vec3(-1.7f,  3.0f, -7.5f),
	   glm::vec3(1.3f, -2.0f, -2.5f),
	   glm::vec3(1.5f,  2.0f, -2.5f),
	   glm::vec3(1.5f,  0.2f, -1.5f),
	   glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	


	//�½�����������ڹ����㻺����������һ���Խ������Ķ������ݴ洢��GPU�ڴ棨�Դ棩��
	//VBO:���㻺��������
	//VAO:�����������

	unsigned int VBO,VAO,EBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1,&EBO);

	//������
	glBindVertexArray(VAO);

	//���������󶨵�����������(OpenGL�кܶ໺��������ͣ����㻺�����Ļ���������GL_ARRAY_BUFFER)
	//GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣
	//GL_DYNAMIC_DRAW�����ݻᱻ�ı�ܶࡣ�Կ�������ݴ�ŵ��ɸ��߶�д���ڴ�
	//GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//�����ݴ渴�ƻ�������������


	//����������󶨵���������
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	

	
	/*��һ������ָ������Ҫ���õĶ������ԡ��ڶ�����ɫ����ʹ��layout(location = 0)������position�������Ե�λ��ֵ(Location)�������԰Ѷ������Ե�λ��ֵ����Ϊ0����Ϊ����ϣ�������ݴ��ݵ���һ�����������У������������Ǵ���0��
		�ڶ�������ָ���������ԵĴ�С������������һ��vec3������3��ֵ��ɣ����Դ�С��3��
		����������ָ�����ݵ����ͣ�������GL_FLOAT(GLSL��vec*�����ɸ�����ֵ��ɵ�)��
		�¸��������������Ƿ�ϣ�����ݱ���׼��(Normalize)�������������ΪGL_TRUE���������ݶ��ᱻӳ�䵽0�������з�����signed������ - 1����1֮�䡣���ǰ�������ΪGL_FALSE��
		�����������������(Stride)�������������������Ķ���������֮��ļ���������¸���λ��������3��float֮�����ǰѲ�������Ϊ3 * sizeof(float)��Ҫע�������������֪����������ǽ������еģ���������������֮��û�п�϶������Ҳ��������Ϊ0����OpenGL�������岽���Ƕ��٣�ֻ�е���ֵ�ǽ�������ʱ�ſ��ã���һ�������и���Ķ������ԣ����Ǿͱ����С�ĵض���ÿ����������֮��ļ���������ں���ῴ����������ӣ���ע: �����������˼��˵���Ǵ�������Եڶ��γ��ֵĵط�����������0λ��֮���ж����ֽڣ���
		���һ��������������void*��������Ҫ���ǽ��������ֵ�ǿ������ת��������ʾλ�������ڻ�������ʼλ�õ�ƫ����(Offset)������λ������������Ŀ�ͷ������������0����
		�ǻ��ں�����ϸ�������������*/

	//glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);//��opengl������ɫ��ָ�������ڴ�����
	//glEnableVertexAttribArray(0);//��������Ĭ�Ϲرգ���������

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	/*glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);*/



	unsigned int texture1, texture2;
	glGenTextures(1,&texture1);
	glBindTexture(GL_TEXTURE_2D,texture1);//����һ��������а�

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);//���������곬��Ĭ�Ϸ�Χʱ��0-1������Χ��ռ�Ϊͼ���ظ�
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);//ȡ���긽�������أ��ۺϼ���һ�������ɫ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);//opengl����Ļy���෴

	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);//��ȡͼƬ����
	if (data) {
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);//��1�����ص��󶨵������У�2���༶��Զ�ļ���0Ϊ��������3���洢��ʽ��6����ʷ���⣻7,8��Դͼ��ʽ���������ͣ�
		glGenerateMipmap(GL_TEXTURE_2D);//Ҫ���ϵ����ڶ�������ʹ�ö༶��Զ��������ô˷���
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);


	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	ourShader.use();//ÿ������uiformǰ�������г���

	//glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);//0��Ϊ��������������Ԫ������ԽСԽ���ϣ���ָ���˲��������������Ԫ
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	glEnable(GL_DEPTH_TEST);//����z���壬�����ǰƬ��������Ƭ��֮�󣬻ᱻ���������������Ч���ص�



	/*glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	ourShader.setMat4("projection", projection);
*/
	//ѭ����Ⱦ����
	while (!glfwWindowShouldClose(window)) {
		float currentFrame =glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);//������ɫ�����z����


		glActiveTexture(GL_TEXTURE0);//��������Ԫ
		glBindTexture(GL_TEXTURE_2D, texture1);//�������뵥Ԫ�н��вɼ�
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		ourShader.use();
		//glUseProgram(shaderProgram);//���г���GPU����ɫ����Ⱦ�����Զ�ʹ�����Ǵ����ĳ�����

		
		//----------------------------------------ƽ�ƺ���ת-------------------------------------------------------//
		//glm::mat4 transform = glm::mat4(1.0f);//0.9.9.x�Ժ�glm����Ĭ��Ϊ0���󣬱��汾Ϊ0.9.9.6����ʼ��Ϊ��λ����
		//transform = glm::translate(transform, glm::vec3(0.0f,0.0f,0.0f));//ƽ��
		//transform = glm::rotate(transform,(float)glfwGetTime(),glm::vec3(0.0f,1.0f,0.0f));//��ת


		//unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));//��ֵ��uniform�Ͷ����������

		//----------------------------------------ƽ�ƺ���ת-------------------------------------------------------//



		//////----------------------------------------ģ����ͼ͸�Ӿ���任-------------------------------------------------------//
		//glm::mat4 model = glm::mat4(1.0f);//ģ�Ͳ�������
		//glm::mat4 view = glm::mat4(1.0f);//��ͼ���������������꣩
		//glm::mat4 projection = glm::mat4(1.0f);//͸�Ӳ�������

		////model = glm::rotate(model,glm::radians(-55.0f),glm::vec3(1.0f,0.0f,0.0f));//glm::radians(-55.0f):����ת�Ƕ�תΪ���ȣ���Ϊ˳ʱ�븺Ϊ��ʱ�루�������귽��
		//model = glm::rotate(model,(float)glfwGetTime(),glm::vec3(0.5,1.0f,0.0f));
		//view = glm::translate(view, glm::vec3(0.0f,0.0f,-3.0f));//���������
		////��Ұ�Ƕȣ��ӿڿ�߱ȣ�����Զƽ�棨�˴������������Ļ����ķ���Ϊ����Ĭ����0λ�ã�������Ļ0�����غϣ�����������������3�������ƽ������Ϊ3����ô��Ұ���������º����������ص���
		//projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);


		//unsigned int modelLoc =	glGetUniformLocation(ourShader.ID,"model");
		//unsigned int viewLoc = glGetUniformLocation(ourShader.ID,"view");
		//
		//glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
		//glUniformMatrix4fv(viewLoc,1,GL_FALSE,&view[0][0]);
		//ourShader.setMat4("projection",projection);

		//////----------------------------------------ģ����ͼ͸�Ӿ���任-------------------------------------------------------//



		////----------------------------------------��ת���-------------------------------------------------------//

		//glm::mat4 view = glm::mat4(1.0f);
		//float radius = 10.0f;
		//
		//float camX = sin(glfwGetTime())*radius;
		//float camZ = cos(glfwGetTime())*radius;
		//cout << camX<<">>>>>>>>>>>"<<camZ << endl;
		//view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		//ourShader.setMat4("view", view);

		////----------------------------------------��ת���-------------------------------------------------------//



		//----------------------------------------WSAD������ƶ����-------------------------------------------------------//

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);

		glm::mat4 view = glm::mat4(1.0f);

		view = glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);

		ourShader.setMat4("view", view);

		//----------------------------------------�ƶ����-------------------------------------------------------//



		//----------------------------------------�������-------------------------------------------------------//
		
		//��ͼ��͸����ͬһ�����ȳ�ʼ��������������䣬����Ҫÿһ֡���������ã����Է�ѭ���⣩
		//glm::mat4 view = glm::mat4(1.0f);
		//glm::mat4 projection = glm::mat4(1.0f);

		////view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		//projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		//
		////ourShader.setMat4("view", view);
		//ourShader.setMat4("projection", projection);

		glBindVertexArray(VAO);

		//��Ⱦʮ������
		unsigned int i = 0;
		for (i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f*i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			ourShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//----------------------------------------�������-------------------------------------------------------//


		


		//glBindVertexArray(VAO);//����ֻ�õ�һ�����飬����ÿ�ζ���ȡͬһ�������Ҫ����������л��󶨵�����,���ﰴ�淶Ҳ�����

		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawArrays(GL_TRIANGLES,0,3);//0:�������鿪ʼ�Ǳ꣬3:size
		//glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);//ʹ����������


		//float timeValue = glfwGetTime();
		//float greenValue = sin(timeValue) / 2.0f + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram,"ourColor");//����ɫ������ȡuniform��λ��
		//glUniform4f(vertexColorLocation,0.0f,greenValue,0.0f,1.0f);


		//glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

		glfwSwapBuffers(window);//�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
		glfwPollEvents();//���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ�����
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	//�ͷ��ڴ�
	glfwTerminate();
	return 0;
}


