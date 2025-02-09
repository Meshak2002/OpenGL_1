#pragma once
#include <GL\glew.h>

#include "BaseScene.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "memory"
#include "Texture.h"

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
        float vertexBuffer[72] =
      {
            // Positions        // Colors (RGBA normalized)
            -60.0f , -100.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1 , 0, 0, // Red
            -100.0f, -100.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0 , 0, 0, // Green
            -60.0f , -60.0f,   0.0f, 0.0f, 1.0f, 1.0f, 1 , 1, 0, // Blue
            -100.0f, -60.0f,   1.0f, 1.0f, 0.0f, 1.0f, 0 , 1, 0, // Yellow
             60.0f,  100.0f,   1.0f, 0.0f, 1.0f, 1.0f, 1 , 0, 1,        // Magenta
             100.0f, 100.0f,   0.0f, 1.0f, 1.0f, 1.0f, 0 , 0, 1,  // Cyan
             60.0f,  60.0f,    1.0f, 1.0f, 1.0f, 1.0f, 1 , 1, 1,  // White
             100.0f, 60.0f,    0.0f, 0.0f, 0.0f, 1.0f, 0 , 1, 1 // Black
        };
        unsigned int indexBuffer[12] =
            {
                0 , 1 , 2 ,
                3 , 1 , 2 ,
                4 , 5 , 6 ,
                7 , 5 , 6
            };
        std::unique_ptr<VertexArray>   vao;
        std::unique_ptr<VertexBuffer>  vbo;
        std::unique_ptr<IndexBuffer>   ibo;
        std::unique_ptr<VertexBufferLayout>   layout;
        std::unique_ptr<Shader>     shader;
        std::unique_ptr<Renderer>   renderer;
        std::shared_ptr<Texture>     texture;
        std::shared_ptr<Texture>     texture2;
        
    };
}
