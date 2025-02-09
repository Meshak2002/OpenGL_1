#include "MultiObjects.h"

#include <iostream>
#include <ostream>

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"

Scenes::MultiObjects::MultiObjects()
	: vbo(std::make_unique<VertexBuffer>( 4 * 4 * sizeof(float), array)) , ibo(std::make_unique<IndexBuffer>(6,indexes)) , tex(std::make_unique<Texture>("res/textures/wood.png")) ,
      vao(std::make_unique<VertexArray>()), layout(std::make_unique<VertexBufferLayout>()) , renderer(std::make_unique<Renderer>()),  ashader(std::make_unique<Shader>("res/Basic.shader")),
	  TranslationA(200.0f,100.0f,0.0f), TranslationB(400.0f,250.0f,0.0f)
{
}

Scenes::MultiObjects::~MultiObjects()
{
	ashader->unbind();
}

void Scenes::MultiObjects::OnBegin()
{
		std::cout<<"OnBegin"<<std::endl;
        vao->Bind();
		vbo->Bind();
        layout->AssignLayoutElement<float>(2,TYPE_Position,GL_TRUE);
        layout->AssignLayoutElement<float>(2,TYPE_TexCoor,GL_TRUE);
        vao->AddVertexBuffer(*vbo, *layout);
		ibo->Bind();
        tex->Bind();
        ashader->bind();
	    projMatrix = glm::ortho(0.0f,640.0f,0.0f,480.0f,-1.0f,1.0f);
		viewMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,0.0f));
		ashader->SetUniform1i("u_useTexture",1);
        ashader->SetUniform1f("u_sampler", 0);
        CheckGL(glEnable(GL_BLEND));
        CheckGL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        vao->Unbind();
        ashader->bind();
        ibo->Unbind();
}

void Scenes::MultiObjects::OnGui()
{
	ImGui::Text("MultiObjects");
	ImGui::SliderFloat3("Translation A",&TranslationA[0],-500.0f,640.0f);
	ImGui::SliderFloat3("Translation B",&TranslationB[0],-500.0f,640.0f);
}

void Scenes::MultiObjects::OnUpdate(float deltaTime)
{
	rChannel+=colorIncrmenter;
	if(rChannel<0)
		colorIncrmenter=0.01f;
	else if(rChannel>1)
		colorIncrmenter=-0.01f;
}

void Scenes::MultiObjects::OnRender()
{
	{
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f),TranslationA);
		glm::mat4 MVP = projMatrix * viewMatrix * modelMatrix;
		ashader->SetUniform4f("u_color",rChannel,0.2,0.5,1);
		ashader->SetUniformMatrix("u_mvp", MVP);
		renderer->Draw(*ashader,*vao,*ibo);
	}
	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f),TranslationB);
	glm::mat4 MVP = projMatrix * viewMatrix * modelMatrix;
	ashader->SetUniform4f("u_color",rChannel,0.2,0.5,1);
	ashader->SetUniformMatrix("u_mvp", MVP);
	renderer->Draw(*ashader,*vao,*ibo);

	
}
