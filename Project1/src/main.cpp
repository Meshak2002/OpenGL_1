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
#include "Scenes/BatchRendering.h"
#include "Scenes/MultiObjects.h"
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

	Scenes::SceneMenu *menuScene = new Scenes::SceneMenu();
	menuScene->sceneList.push_back(std::make_pair(std::string("Multi Object Render"),[](){ return new Scenes::MultiObjects(); } ) );
	menuScene->sceneList.push_back(std::make_pair(std::string("Batch Rendering "),[](){return new Scenes::BatchRendering(); } ) );
	Scenes::BaseScene*& currentScene=menuScene->activeScene;
	if(currentScene)
		currentScene->OnBegin();
	while (!glfwWindowShouldClose(window))
		{
			glfwSwapInterval(1);
			CheckGL(glClear(GL_COLOR_BUFFER_BIT));
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			ImGui::Begin("Home");
			if(currentScene)
			{
				currentScene->OnRender();
				currentScene->OnUpdate(.1);
				if(ImGui::Button("Back"))
				{
					delete currentScene;
					currentScene=nullptr;
				}
				if(currentScene)	currentScene->OnGui();
			}
			else
			{
				menuScene->OnGui();
			}
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	if(currentScene!=nullptr)	delete currentScene;
	glfwTerminate();
	return 0;
}
