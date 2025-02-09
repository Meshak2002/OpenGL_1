#include "BaseScene.h"

#include "imgui/imgui.h"

Scenes::BaseScene::BaseScene()
{
}

Scenes::BaseScene::~BaseScene()
{
}

void Scenes::BaseScene::OnBegin()
{
}

void Scenes::BaseScene::OnGui()
{
}

void Scenes::BaseScene::OnUpdate(float deltaTime)
{
}

void Scenes::BaseScene::OnRender()
{
}

Scenes::SceneMenu::SceneMenu() : activeScene(nullptr)
{
    
}

Scenes::SceneMenu::~SceneMenu()
{
}


void Scenes::SceneMenu::OnBegin()
{
    BaseScene::OnBegin();
}

void Scenes::SceneMenu::OnGui()
{
    BaseScene::OnGui();
    ImGui::Text("---Scene List---");
    for (auto scene : sceneList)
    {
        if( ImGui::Button(scene.first.c_str()) )
        {
            activeScene=scene.second();
            activeScene->OnBegin();
        }
    }
}

void Scenes::SceneMenu::OnUpdate(float deltaTime)
{
    BaseScene::OnUpdate(deltaTime);
}

void Scenes::SceneMenu::OnRender()
{
    BaseScene::OnRender();
}
