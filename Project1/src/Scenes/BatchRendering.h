#pragma once
#include <GL\glew.h>

#include "BaseScene.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "memory"
#include "array"
#include "Texture.h"

struct Vertex
{
    glm::vec2 position;
    glm::vec4 color;
    glm::vec2 texCoord;
    float texIndex;
};

namespace Scenes
{
    class BatchRendering : public BaseScene
    {
    public:
        BatchRendering();
        ~BatchRendering();
        void OnBegin() override;
        void OnGui() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
     
        unsigned int indexBuffer[12] =
            {
                0 , 1 , 2 ,
                3 , 1 , 2 ,
                4 , 5 , 6 ,
                7 , 5 , 6
            };
        unsigned int vertexBufferID;
        std::unique_ptr<VertexArray>   vao;
        std::unique_ptr<VertexBuffer>  vbo;
        std::unique_ptr<IndexBuffer>   ibo;
        std::unique_ptr<VertexBufferLayout>   layout;
        std::unique_ptr<Shader>     shader;
        std::unique_ptr<Renderer>   renderer;
        std::shared_ptr<Texture>     texture;
        std::shared_ptr<Texture>     texture2;

        float transform[2];
        std::array<Vertex,4> CreateQuad(float posX,float posY,float texID=0,float scale=1);
    };
}
