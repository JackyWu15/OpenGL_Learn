#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "Shader.h"
#include "stb_image.h"

using namespace std;

////顶点着色器执行代码
//const char *vertexShaderSource = "#version 450 core\n"//指定opengl的版本，这里采用了4.5核心代码
//"layout (location = 0) in vec3 aPos;\n"//layout：连接到顶点数据 (location = 0):设定了输入变量的位置 in:声明所有的输入顶点属性 vec3：表示了空间上一个点以3维向量表示 apos:变量名
//"out vec4 vertexColor;\n" //out : 定义输出变量
//"void main()\n"//函数入口
//"{\n"
//"   gl_Position = vec4(aPos, 1.0);\n"//vec.w：透视除法，将输入数据转化为4分量，赋值给输出变量
//"   vertexColor = vec4(0.5,0.0,0.0,1.0);\n"//设置颜色值
//"}\0";


//顶点着色器执行代码
const char *vertexShaderSource = "#version 450 core\n"//指定opengl的版本，这里采用了4.5核心代码
"layout (location = 0) in vec3 aPos;\n"//0:坐标数据设置为0
"layout (location = 1) in vec3 aColor;\n"//1:颜色数据设置为1
"out vec3 vertexColor;\n" //out : 定义输出变量
"void main()\n"//函数入口
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"//vec.w：透视除法，将输入数据转化为4分量，赋值给输出变量
"   vertexColor = aColor;\n"//设置颜色值
"}\0";

////片元着色器执行代码
//const char *fragmentShaderSource = "#version 450 core\n"
//"in vec4 vertexColor;\n"//in: 接收顶点着色器的变量值，类型和名字必须一致
//"out vec4 FragColor;\n"//out：声明了最后输出的颜色  vec4:4分量 FragColor:变量名
//"void main()\n"
//"{\n"
////"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"//颜色：0.0-1.0，RGBA
//"   FragColor = vertexColor;\n"//颜色：0.0-1.0，RGBA
//"}\n\0";



////uniform 在每个着色器中都是独一无二的，它可以被着色器程序的任意着色器在任意阶段访问。第二，无论你把uniform值设置成什么，uniform会一直保存它们的数据，直到它们被重置或更新（类似定一个静态变量，供外部访问
//const char *fragmentShaderSource = "#version 450 core\n"
//"out vec4 FragColor;\n"//out：声明了最后输出的颜色  vec4:4分量 FragColor:变量名
//"uniform vec4 ourColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = ourColor;\n"//颜色：0.0-1.0，RGBA
//"}\n\0";



const char *fragmentShaderSource = "#version 450 core\n"
"in vec3 vertexColor;\n"//in: 接收顶点着色器的变量值，类型和名字必须一致
"out vec3 FragColor;\n"//out：声明了最后输出的颜色  vec4:4分量 FragColor:变量名
"void main()\n"
"{\n"
//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"//颜色：0.0-1.0，RGBA
"   FragColor = vertexColor;\n"//颜色：0.0-1.0，RGBA
"}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main(int argc,char *argv[]){
	glfwInit();//初始化glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.5);//主版本使用opengl 4.x 版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4.5);//次版本使用opengl 4.x 版本
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//只使用opengl核心代码库

	//创建窗体
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//把窗体上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);

	//设置窗体变化的监听
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//初始化glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}


	

	////顶点着色器
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);

	////装载代码，并编译，类似生成.o机器码文件
	//glShaderSource(vertexShader,1,&vertexShaderSource,NULL);//1:字符串数量
	//glCompileShader(vertexShader);

	////获取编译状态
	//int success;
	//char infoLog[512];
	//glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
	//if (!success) {
	//	glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
	//	cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog <<endl;
	//	return -1;
	//}

	////片元着色器
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

	////将所有着色器合并并联接成一个程序，类似生成可执行文件
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
	//glDeleteShader(vertexShader);//删除编译对象
	//glDeleteShader(fragmentShader);

		////用于查询顶点着色器最大数
	//int nrAttributes;
	//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	//std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	Shader ourShader("shader.vs", "shader.fs");


	////三角形顶点数据
	//float vertices[] = {
	//-0.5f, -0.5f, 0.0f,
	// 0.5f, -0.5f, 0.0f,
	// 0.0f,  0.5f, 0.0f
	//};

	//方形顶点数据
	float vertices[] = {		
			//顶点坐标		//颜色			// 纹理坐标
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,1.0f, // top right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,0.0f,// bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,1.0f  // top left 
	};

	//索引数据
	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};

	////增加颜色数据
	//float vertices[] = {
	//	// 位置              // 颜色
	//	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
	//	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
	//	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
	//};


	//新建缓冲对象，用于管理顶点缓冲区，可以一次性将大量的顶点数据存储到GPU内存（显存）中
	//VBO:顶点缓冲区对象
	//VAO:顶点数组对象

	unsigned int VBO,VAO,EBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1,&EBO);

	//绑定数组
	glBindVertexArray(VAO);

	//将缓冲对象绑定到缓冲数组中(OpenGL有很多缓冲对象类型，顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER)
	//GL_STATIC_DRAW ：数据不会或几乎不会改变。
	//GL_DYNAMIC_DRAW：数据会被改变很多。显卡会把数据存放到可告诉读写的内存
	//GL_STREAM_DRAW ：数据每次绘制时都会改变。
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//将数据存复制缓冲区的数组中


	//将索引对象绑定到缓冲区中
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

	

	
	/*第一个参数指定我们要配置的顶点属性。在顶点着色器中使用layout(location = 0)定义了position顶点属性的位置值(Location)吗？它可以把顶点属性的位置值设置为0。因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入0。
		第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
		第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec*都是由浮点数值组成的)。
		下个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是 - 1）到1之间。我们把它设置为GL_FALSE。
		第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在3个float之后，我们把步长设置为3 * sizeof(float)。要注意的是由于我们知道这个数组是紧密排列的（在两个顶点属性之间没有空隙）我们也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。一旦我们有更多的顶点属性，我们就必须更小心地定义每个顶点属性之间的间隔，我们在后面会看到更多的例子（译注: 这个参数的意思简单说就是从这个属性第二次出现的地方到整个数组0位置之间有多少字节）。
		最后一个参数的类型是void*，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0。我们会在后面详细解释这个参数。*/

	//glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);//让opengl顶点着色器指向数据内存区域
	//glEnableVertexAttribArray(0);//顶点属性默认关闭，这里启用

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);



	unsigned int texture1, texture2;
	glGenTextures(1,&texture1);
	glBindTexture(GL_TEXTURE_2D,texture1);//创建一张纹理进行绑定

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);//当纹理坐标超出默认范围时（0-1），范围外空间为图像重复
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);//取坐标附近的像素，综合计算一个混合颜色
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);//opengl和屏幕y轴相反

	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);//获取图片数据
	if (data) {
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);//参1：加载到绑定的纹理中；2：多级渐远的级别，0为基本级别；3，存储格式；6：历史问题；7,8：源图格式和数据类型，
		glGenerateMipmap(GL_TEXTURE_2D);//要不断递增第二参数来使用多级渐远处理，或调用此方法
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

	ourShader.use();//设置uiform前要运行程序

	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);//0：为采样器分配纹理单元，数字越小越靠上，即指定了采样器处理这个单元

	ourShader.setInt("texture2", 1);

	//循环渲染窗体
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glActiveTexture(GL_TEXTURE0);//激活纹理单元
		glBindTexture(GL_TEXTURE_2D, texture1);//纹理送入单元中进行采集
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		//glUseProgram(shaderProgram);//运行程序，GPU的着色和渲染都会自动使用我们创建的程序了
		//ourShader.use();

		glBindVertexArray(VAO);//程序只用到一个数组，所以每次都会取同一个，如果要多个，可以切换绑定的数组

		//glDrawArrays(GL_TRIANGLES,0,3);
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);//使用索引绘制


		//float timeValue = glfwGetTime();
		//float greenValue = sin(timeValue) / 2.0f + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram,"ourColor");//从着色程序中取uniform的位置
		//glUniform4f(vertexColorLocation,0.0f,greenValue,0.0f,1.0f);

		//glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

		glfwSwapBuffers(window);//函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
		glfwPollEvents();//函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	//释放内存
	glfwTerminate();
	return 0;
}


