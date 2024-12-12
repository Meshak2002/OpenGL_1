#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "fstream"
#include "sstream"
#include "iostream"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"


struct ShaderSrc
{
	std::string vertexSource;
	std::string fragmentSource;
};
enum class ShaderType
{
	NONE=-1,
	VERTEX=0,
	FRAGMENT=1
};
static ShaderSrc ParseShaders(std::string directory)
{
	ShaderType type = ShaderType::NONE;
	std::ifstream file(directory);
	std::string line;
	std::stringstream ss[2];
	while(getline(file, line))
	{
		if(line.find("#shader")!=std::string::npos)
		{
			if(line.find("vertex")!=std::string::npos)
				type = ShaderType::VERTEX;
			if(line.find("fragment")!=std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
			ss[(int)type]<<line<<std::endl;
	}
	return {ss[0].str(),ss[1].str()};
}

unsigned int CreateShader(unsigned int type, std::string source)
{
	unsigned int shader=glCreateShader(type);
	const char* srcStart = source.c_str(); //Returns the address of first character in the string
	glShaderSource(shader,1,&srcStart,NULL);
	glCompileShader(shader);
	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE)		//result == 0
	{
		int length;
		glGetShaderiv(shader,GL_INFO_LOG_LENGTH, &length);
		char* logMessage= (char*) alloca((sizeof(char) * length));
		glGetShaderInfoLog(shader,length,&length,logMessage);
		std::cout <<"Failed To comile "<<( (type==GL_VERTEX_SHADER)?"Vertex Shader":"Fragment Shader")<<" sad"<< std::endl;
		std::cout << logMessage<<std::endl;
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}

unsigned int CreateShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource)
{
	unsigned int programm= glCreateProgram();
	unsigned int vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int FragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	glAttachShader(programm, vertexShader);
	glAttachShader(programm, FragmentShader);
	glLinkProgram(programm);
	glValidateProgram(programm);
	glDeleteShader(vertexShader);
	glDeleteShader(FragmentShader);
	return programm;
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window;

	window = glfwCreateWindow(640, 480, "Welcome Window",NULL,NULL );
	glfwMakeContextCurrent(window);
	if(glewInit()==GLEW_OK)
		std::cout << glGetString(GL_VERSION) << std::endl;
	{
		float array[] = {
			-.5, -.5,
			 .5, -.5,
			 .5,  .5,
			-.5,  .5
		};
		unsigned int indexes[] =
			{
			0, 1, 2,
			2, 3, 0
			};
		VertexArray vao;
		vao.Bind();
		VertexBuffer vbo( 4 * 2 * sizeof(float), array);

		VertexBufferLayout layout;
		layout.AssignLayoutElement<float>(2,GL_TRUE);
		vao.AddVertexBuffer(vbo, layout);
	
		IndexBuffer ibo(6,indexes);
		ShaderSrc shadersSrc = ParseShaders("res/Basic.shader");
		unsigned int program = CreateShaderProgram(shadersSrc.vertexSource, shadersSrc.fragmentSource);
		CheckGL(glUseProgram(program));
	
		int shaderColorVar = glGetUniformLocation(program, "u_color");
		if(shaderColorVar == -1)
			std::cout<<"Failed to get uniform location!"<<std::endl;
		float rChannel=0;
		float colorIncrmenter=.01f;

		while (!glfwWindowShouldClose(window))
		{
			glfwSwapInterval(1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			rChannel+=colorIncrmenter;
			CheckGL(glUniform4f(shaderColorVar,rChannel,.5f,.3f,1));
			CheckGL(glDrawElements(GL_TRIANGLES,ibo.GetCount(),GL_UNSIGNED_INT,nullptr));

			if(rChannel<0)
				colorIncrmenter=0.01f;
			else if(rChannel>1)
				colorIncrmenter=-0.01f;
		
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		
		glDeleteProgram(program);
	}
	glfwTerminate();
	return 0;
}