#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "iostream"
#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"

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

		Shader ashader("res/Basic.shader");
		ashader.bind();
		
		float rChannel=0;
		float colorIncrmenter=.01f;
		Renderer renderer;
		vao.Unbind();
		vbo.Unbind();
		ibo.Unbind();
		//ashader.unbind();
		
		while (!glfwWindowShouldClose(window))
		{
			glfwSwapInterval(1);
			renderer.Clear();
			
			rChannel+=colorIncrmenter;
			ashader.SetUniform4f("u_color",rChannel,.5f,.3f,1);
			renderer.Draw(ashader,vao,ibo);
			
			if(rChannel<0)
				colorIncrmenter=0.01f;
			else if(rChannel>1)
				colorIncrmenter=-0.01f;
		
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		
		ashader.unbind();
	}
	glfwTerminate();
	return 0;
}