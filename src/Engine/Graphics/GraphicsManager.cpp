#include "pch.h"
#include "GraphicsManager.h"

liGraphicsManager::liGraphicsManager(SDL_Window* window) {
    this->window = window;

    this->device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, _DEBUG, nullptr);
    SDL_ClaimWindowForGPUDevice(device, window);
}

liGraphicsManager::~liGraphicsManager() {
    SDL_ReleaseWindowFromGPUDevice(device, window);
    SDL_DestroyGPUDevice(device);
}

void liGraphicsManager::Prepare() {
    this->commandBuffer = SDL_AcquireGPUCommandBuffer(device);
    Uint32 width, height;
    SDL_WaitAndAcquireGPUSwapchainTexture(commandBuffer, window, &swapchainTexture, &width, &height);
}

void liGraphicsManager::Submit() {
    SDL_SubmitGPUCommandBuffer(commandBuffer);
}