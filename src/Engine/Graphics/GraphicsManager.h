#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H
#pragma once

class liGraphicsManager {
public:
    liGraphicsManager(SDL_Window* window);
    liGraphicsManager(const liGraphicsManager&) = delete;
    ~liGraphicsManager();

    void Prepare();
    void Submit();
    
    SDL_GPUDevice* Device() { return device; }
    SDL_GPUCommandBuffer* CmdBuffer() { return commandBuffer; }
    SDL_GPUTexture* SwapchainTexture() { return swapchainTexture; }
private:
    SDL_Window* window;
    SDL_GPUDevice* device;
    SDL_GPUCommandBuffer* commandBuffer;
    SDL_GPUTexture* swapchainTexture;
};

#endif