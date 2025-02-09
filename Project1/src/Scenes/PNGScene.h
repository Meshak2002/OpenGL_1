#pragma once
#include "BaseScene.h"

namespace Scenes
{
    class PNGScene : public BaseScene
    {
    public:
        PNGScene() = default;
        ~PNGScene() = default;

        void OnGui() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
    
    };
}