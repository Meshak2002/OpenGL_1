#include "BatchRendering.h"

#include <iostream>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Renderer.h"
#include "imgui/imgui.h"

Scenes::BatchRendering::BatchRendering() :
     ibo(std::make_unique<IndexBuffer>(12, indexBuffer)) ,
    shader(std::make_unique<Shader>("res/Basic.shader")) 
{
}

Scenes::BatchRendering::~BatchRendering()
{
}

void Scenes::BatchRendering::OnBegin()
{
    BaseScene::OnBegin();
    glGenBuffers(1,&vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex)*16*4,nullptr,GL_STATIC_DRAW);
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
    ImGui::DragFloat2("Transform-1",transform);
}

void Scenes::BatchRendering::OnUpdate(float deltaTime)
{
    BaseScene::OnUpdate(deltaTime);
    auto  q0 = CreateQuad(transform[0],transform[1],0,50);
    auto  q1 = CreateQuad(30,30,1,105);
    Vertex ver[8];
    memcpy(ver,q0.data(),q0.size()*sizeof(Vertex));
    memcpy(ver+q0.size(),q1.data(),q1.size()*sizeof(Vertex));
    
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferID);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(ver),ver);
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

std::array<Vertex,4> Scenes::BatchRendering::CreateQuad(float posX,float posY,float texID,float scale)
{
    Vertex V1;
    V1.position = glm::vec2(posX+1.0f*scale, posY);
    V1.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    V1.texCoord = glm::vec2(1, 0);
    V1.texIndex = texID;

    Vertex V2;
    V2.position = glm::vec2(posX, posY);
    V2.color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    V2.texCoord = glm::vec2(0, 0);
    V2.texIndex = texID;

    Vertex V3;
    V3.position = glm::vec2(posX+1.0f*scale, posY+1.0f*scale);
    V3.color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    V3.texCoord = glm::vec2(1, 1);
    V3.texIndex = texID;

    Vertex V4;
    V4.position = glm::vec2(posX, posY+1.0f*scale);
    V4.color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    V4.texCoord = glm::vec2(0, 1);
    V4.texIndex = texID;

    return { V1,V2,V3,V4 };
}
