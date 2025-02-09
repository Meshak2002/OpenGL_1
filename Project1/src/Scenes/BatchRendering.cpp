#include "BatchRendering.h"

#include <iostream>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Renderer.h"
#include "imgui/imgui.h"

Scenes::BatchRendering::BatchRendering() :
    vbo(std::make_unique<VertexBuffer>(72*sizeof(float) , &vertexBuffer)) , ibo(std::make_unique<IndexBuffer>(12, indexBuffer)) ,
    shader(std::make_unique<Shader>("res/Basic.shader")) 
{
}

Scenes::BatchRendering::~BatchRendering()
{
}

void Scenes::BatchRendering::OnBegin()
{
    BaseScene::OnBegin();
    vbo->Bind();
    layout = std::make_unique<VertexBufferLayout>();
    layout->AssignLayoutElement<float>(2,TYPE_Position,true);
    layout->AssignLayoutElement<float>(4,TYPE_Color,true);
    layout->AssignLayoutElement<float>(2 , TYPE_TexCoor , true);
    layout->AssignLayoutElement<float>(1 , TYPE_TexSlot , true);
    vao = std::make_unique<VertexArray>();
    vao->AddVertexBuffer(*vbo, *layout);
    texture = std::make_shared<Texture>("res/textures/walt.png");
    texture2 = std::make_shared<Texture>("res/textures/wood.png");
    texture->Bind(0);
    texture2->Bind(1);
    vao->Bind();  
    ibo->Bind();
    shader->bind();
    int samplers[2] = { 0, 1 };
    shader->SetUniform1iv("u_sampler",2,samplers);
    shader->SetUniform1i("u_useTexture",1);
    CheckGL(glEnable(GL_BLEND));
    CheckGL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Scenes::BatchRendering::OnGui()
{
    BaseScene::OnGui();
    ImGui::Text("Batch-Rendering");
}

void Scenes::BatchRendering::OnUpdate(float deltaTime)
{
    BaseScene::OnUpdate(deltaTime);
}

void Scenes::BatchRendering::OnRender()
{
    BaseScene::OnRender();
    glm::vec3 pos = {320, 240, 0}; // Move it to the center
    glm::mat4 position = glm::translate(glm::mat4(1.0f), pos);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 projection = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
    glm::mat4 mvp = projection * view * position;
    shader->SetUniformMatrix("u_mvp", mvp);
    //
    renderer->Draw(*shader, *vao, *ibo);
}
