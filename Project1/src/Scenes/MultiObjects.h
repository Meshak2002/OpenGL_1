#pragma once
#include <memory>

#include "BaseScene.h"

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Scenes
{
    class MultiObjects : public Scenes::BaseScene
    {
    public:
        MultiObjects();
        ~MultiObjects();
        void OnBegin() override;
        void OnGui() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;

    private:
        float array[16]={
            -50, -50,   0, 0,
             50, -50,   1, 0,
             50,  50,   1, 1,
            -50,  50,   0, 1
       }; 
        unsigned int indexes[6] =  {
            0, 1, 2,
            2, 3, 0
            };
        std::unique_ptr<VertexArray> vao;
        std::unique_ptr<VertexBuffer> vbo;
        std::unique_ptr<VertexBufferLayout> layout;
        std::unique_ptr<IndexBuffer> ibo;
        std::unique_ptr<Texture> tex;
        std::unique_ptr<Shader> ashader;
        std::unique_ptr<Renderer> renderer;

        glm::mat4 projMatrix;
        glm::mat4 viewMatrix;
        float rChannel=0;
        float colorIncrmenter=.01f;
        glm::vec3 TranslationA;
        glm::vec3 TranslationB;
    };
}