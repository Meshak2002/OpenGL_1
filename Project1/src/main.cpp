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
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "Welcome Window",NULL,NULL );
	glfwMakeContextCurrent(window);
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	const char* glsl_version = "#version 330";
#ifdef __EMSCRIPTEN__
	ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
	ImGui_ImplOpenGL3_Init(glsl_version);
	
	if(glewInit()==GLEW_OK)
		std::cout << glGetString(GL_VERSION) << std::endl;
	
	{
		float array[] = {
			 -50, -50,   0, 0,
			  50, -50,   1, 0,
			  50,  50,   1, 1,
			 -50,  50,   0, 1
		};
		unsigned int indexes[] =
			{
			0, 1, 2,
			2, 3, 0
			};
		VertexArray vao;
		vao.Bind();
		VertexBuffer vbo( 4 * 4 * sizeof(float), array);

		VertexBufferLayout layout;
		layout.AssignLayoutElement<float>(2,GL_TRUE);
		layout.AssignLayoutElement<float>(2,GL_TRUE);
		
		vao.AddVertexBuffer(vbo, layout);
		IndexBuffer ibo(6,indexes);

		Texture tex("res/textures/wood.png");
		tex.Bind();
		
		Shader ashader("res/Basic.shader");
		ashader.bind();
		glm::mat4 projMatrix = glm::ortho(0.0f,640.0f,0.0f,480.0f,-1.0f,1.0f);
		glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,0.0f));
		 
		ashader.SetUniform1f("u_sampler", 0);
		CheckGL(glEnable(GL_BLEND));
		CheckGL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		float rChannel=0;
		float colorIncrmenter=.01f;
		Renderer renderer;
		vao.Unbind();
		vbo.Unbind();
		ibo.Unbind();
		glm::vec3 TranslationA(200.0f,100.0f,0.0f);
		glm::vec3 TranslationB(400.0f,250.0f,0.0f);

		while (!glfwWindowShouldClose(window))
		{
			glfwSwapInterval(1);
			renderer.Clear();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			ImGui::Begin("Hello, world!");
			ImGui::SliderFloat3("Translation A",&TranslationA[0],-500.0f,640.0f);
			ImGui::SliderFloat3("Translation B",&TranslationB[0],-500.0f,640.0f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
			
			{
				glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f),TranslationA);
				glm::mat4 MVP = projMatrix * viewMatrix * modelMatrix;
				ashader.SetUniform4f("u_color",rChannel,0.2,0.5,1);
				ashader.SetUniformMatrix("u_mvp", MVP);
				renderer.Draw(ashader,vao,ibo);
			}
			glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f),TranslationB);
			glm::mat4 MVP = projMatrix * viewMatrix * modelMatrix;
			ashader.SetUniform4f("u_color",rChannel,0.2,0.5,1);
			ashader.SetUniformMatrix("u_mvp", MVP);
			renderer.Draw(ashader,vao,ibo);

			rChannel+=colorIncrmenter;
			if(rChannel<0)
				colorIncrmenter=0.01f;
			else if(rChannel>1)
				colorIncrmenter=-0.01f;
			
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		ashader.unbind();
	}
	glfwTerminate();
	return 0;
}
