#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include "pch.h"
#include <Engine/Graphics/GraphicsManager.h>

static struct runtime_t {
    SDL_Window* window;
    int width, height;

    liGraphicsManager* gfx;
} rt;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
    *appstate = static_cast<void*>(&rt);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD);

    rt.width = 1280;
    rt.height = 800;
    rt.window = SDL_CreateWindow("Matriarch Prime", rt.width, rt.height, 0);
    rt.gfx = new liGraphicsManager(rt.window);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    rt.gfx->Prepare();

    SDL_GPUColorTargetInfo colorTargetInfo = {0};
    colorTargetInfo.clear_color = { 0.3f, 0.4f, 0.5f, 1.0f };
    colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
    colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;
    colorTargetInfo.texture = rt.gfx->SwapchainTexture();

    SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(rt.gfx->CmdBuffer(), &colorTargetInfo, 1, nullptr);
    SDL_EndGPURenderPass(renderPass);

    rt.gfx->Submit();
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    switch (event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    default:
        return SDL_APP_CONTINUE;
    }
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    delete rt.gfx;
    SDL_DestroyWindow(rt.window);
}