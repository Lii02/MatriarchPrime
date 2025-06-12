#ifndef GAME_H
#define GAME_H
#pragma once

class liKeyboard;
class liMouse;
class liRenderPass;
class liPostProcessing;
class liAssetManager;

struct gameContext_t {
    liKeyboard* keyboard;
    liMouse* mouse;
    liRenderPass* renderPass;
    liPostProcessing* post;
    liAssetManager* assets;
};

class liGame : public IRunnable {
public:
    liGame(gameContext_t context);
    virtual ~liGame() { }

    virtual void Render();
    virtual void Update(float deltaTime);
    virtual void ImGui() = 0;

    inline liKeyboard* Keyboard() { return keyboard; }
    inline liMouse* Mouse() { return mouse; }
    inline liAssetManager* Assets() { return assets; }
private:
    liKeyboard* keyboard;
    liMouse* mouse;
    liRenderPass* renderPass;
    liPostProcessing* post;
    liAssetManager* assets;
};

#endif