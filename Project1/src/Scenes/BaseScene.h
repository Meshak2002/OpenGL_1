#pragma once
#include <vector>
#include <functional>
#include <string>
namespace Scenes
{
    class BaseScene
    {
    public:
        BaseScene();
        virtual ~BaseScene();

        virtual void OnBegin();
        virtual void OnGui();
        virtual void OnUpdate(float deltaTime);
        virtual void OnRender();
    
    };

    class SceneMenu : public BaseScene
    {
        public:
        SceneMenu();
        ~SceneMenu();
        
        std::vector<std::pair<std::string,std::function<BaseScene*()>>> sceneList;
        BaseScene* activeScene;
        void OnBegin() override;
        void OnGui() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        
    };
}
