#include "pch.h"
#include "MP.h"
#include "imgui/imgui.h"
#include <Engine/Graphics/RenderPass.h>
#include <Engine/Framework/AssetManager.h>
#include <Engine/Input/Keyboard.h>

MPGame::MPGame(gameContext_t context)
    : liGame(context) {
    Setup();
}

MPGame::~MPGame() {
}

void MPGame::Setup() {
    liGame::Setup();

    this->debugMenus = false;
}

void MPGame::Render() {
}

void MPGame::Update(float deltaTime) {
    liKeyboard* keyboard = Keyboard();

    if(keyboard->IsButtonPressed(LI_KEY_KP_7)) {
        this->debugMenus = !debugMenus;
    }
}

void MPGame::ImGui() {
    if(debugMenus) {
        if(ImGui::Begin("Assets")) {
            ulong_t assetCount = Assets()->AssetCount();
            ImGui::Text("Loaded assets: %d", assetCount);
            ImGui::BeginChild("Scrolling");
            for(ulong_t i = 0; i < assetCount; i++) {
                liAsset* asset = Assets()->GetAssetByIndex(i);
                ImGui::Text("%s, %s: %s", asset->Name().c_str(), asset->GUID(), typeid(*asset).name());
            }
            ImGui::EndChild();
            ImGui::End();
        }
    }
}