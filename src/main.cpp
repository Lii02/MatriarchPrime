#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include "pch.h"
#include <Engine/Graphics/RenderPass.h>
#include <Engine/Graphics/Mesh.h>

static struct runtime_t {
    SDL_Window* window;
    SDL_GLContext gl;
    int width, height;
    liRenderPass* renderPass;

    liMesh* mesh;
} rt;

liVertexList vertices = {
    liVertex(liVec3(-0.5f, -0.5f, 0.0f), liVec2(), liVec3()),
    liVertex(liVec3(0.5f, -0.5f, 0.0f), liVec2(), liVec3()),
    liVertex(liVec3(0.0f,  0.5f, 0.0f), liVec2(), liVec3())
};

liUIntBuffer indices = {
    0, 1, 2
};

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
    *appstate = static_cast<void*>(&rt);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD);

    rt.width = 1280;
    rt.height = 800;
    rt.window = SDL_CreateWindow("Matriarch Prime", rt.width, rt.height, SDL_WINDOW_OPENGL);
    SDL_AddGamepadMappingsFromFile("./Assets/gamecontrollerdb.txt");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    rt.gl = SDL_GL_CreateContext(rt.window);
    SDL_GL_MakeCurrent(rt.window, rt.gl);
    gladLoadGLES2((GLADloadfunc)SDL_GL_GetProcAddress);
    rt.renderPass = new liRenderPass(rt.width, rt.height, true);

    rt.mesh = new liMesh();
    rt.mesh->Upload(&vertices, &indices);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    //rt.renderPass->Begin(liColor(0.5f, 0.25f, 0.25f, 1.0f));
    
    rt.mesh->Draw();

    //rt.renderPass->End();

    SDL_GL_SwapWindow(rt.window);
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
    delete rt.mesh;
    SDL_GL_DestroyContext(rt.gl);
    SDL_DestroyWindow(rt.window);
}