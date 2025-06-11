#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include "pch.h"
#include <Engine/Framework/Stopwatch.h>
#include <Engine/Input/Keyboard.h>
#include <Engine/Input/Mouse.h>
#include <Engine/Graphics/RenderPass.h>
#include <Engine/Graphics/PostProcessing.h>
#include <Engine/Math/Matrices.h>
#include <Engine/Graphics/Mesh.h>
#include <Engine/Graphics/RenderShader.h>
#include <Engine/Graphics/ShaderProgram.h>
#include <Engine/Tools/FileIO.h>
#include <Engine/Framework/AssetManager.h>

struct VertexBuffer {
    liMat4 projection;
    liMat4 view;
    liMat4 model;
};

struct PixelBuffer {
    liColor color;
};

static struct runtime_t {
    SDL_Window* window;
    SDL_GLContext gl;
    int width, height;
    liStopwatch stopwatch;
    float elapsed;
    liKeyboard* keyboard;
    liMouse* mouse;
    
    liRenderPass* renderPass;
    liPostProcessing* post;
    liAssetManager* asset;
    liMesh* mesh;
    liRenderShader* renderShader;
    liShaderProgram* program;
    liUniformBuffer<VertexBuffer>* vertexBuffer;
    liUniformBuffer<PixelBuffer>* pixelBuffer;
} rt;

liVertexList vertices = {
    liVertex(liVec3(-0.5f, -0.5f, 0.0f), liVec2(0.0f, 0.0f), liVec3()),
    liVertex(liVec3(0.5f, -0.5f, 0.0f), liVec2(1.0f, 0.0f), liVec3()),
    liVertex(liVec3(-0.5f, 0.5f, 0.0f), liVec2(0.0f, 1.0f), liVec3()),
    liVertex(liVec3(0.5f, 0.5f, 0.0f), liVec2(1.0f, 1.0f), liVec3())
};

liUIntBuffer indices = {
    0, 1, 2, 1, 2, 3
};

VertexBuffer vertexBuffer;
PixelBuffer pixelBuffer;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
    *appstate = static_cast<void*>(&rt);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD);

    rt.width = 1280;
    rt.height = 800;
    rt.window = SDL_CreateWindow("Matriarch Prime", rt.width, rt.height, SDL_WINDOW_OPENGL);
    SDL_AddGamepadMappingsFromFile("./Assets/gamecontrollerdb.txt");
    rt.elapsed = 0.0f;
    rt.keyboard = new liKeyboard();
    rt.mouse = new liMouse();

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    rt.gl = SDL_GL_CreateContext(rt.window);
    SDL_GL_MakeCurrent(rt.window, rt.gl);
    gladLoadGLES2((GLADloadfunc)SDL_GL_GetProcAddress);
    rt.renderPass = new liRenderPass(rt.width, rt.height, true);
    rt.post = new liPostProcessing();
    rt.asset = new liAssetManager();

    rt.mesh = new liMesh(vertices.size(), indices.size());
    rt.mesh->UploadVertices(&vertices);
    rt.mesh->UploadIndices(&indices);
    rt.asset->LoadAsset("TestMesh", rt.mesh);
    
    rt.renderShader = new liRenderShader();
    std::string vertexSource, pixelSource;
    liFileIO::Read("./Assets/Shaders/standard.vert", vertexSource);
    liFileIO::Read("./Assets/Shaders/standard.frag", pixelSource);
    rt.renderShader->CompileVertex(vertexSource);
    rt.renderShader->CompilePixel(pixelSource);
    rt.asset->LoadAsset("TestShader", rt.renderShader);

    rt.program = new liShaderProgram();
    rt.renderShader->Attach(rt.program);
    rt.program->Link({ { 0, "position" }, { 1, "texCoord" }, { 2, "normal" } });

    rt.vertexBuffer = new liUniformBuffer<VertexBuffer>();
    vertexBuffer.model = liMat4::Translate(liVec3(0, 0, -1));
    vertexBuffer.projection = liMat4::Perspective(70.0f, 1.6f, 0.1f, 1000.0f);

    rt.pixelBuffer = new liUniformBuffer<PixelBuffer>();
    pixelBuffer.color = liColor(0.5f, 1.0f, 0.25f, 1.0f);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    rt.stopwatch.Begin();
    double deltaTime = rt.stopwatch.Seconds();
    rt.elapsed += rt.stopwatch.Seconds();
    rt.renderPass->Begin(liColor(0.5f, 0.25f, 0.25f, 1.0f));
    
    rt.program->Bind();
    rt.vertexBuffer->Bind(rt.program->Program(), "VertexUniform", 0);
    rt.pixelBuffer->Bind(rt.program->Program(), "PixelUniform", 1);
    rt.vertexBuffer->Upload(&vertexBuffer);
    rt.pixelBuffer->Upload(&pixelBuffer);
    rt.mesh->Draw(cullMode_t::BACK_FACE, topology_t::TRIANGLES, 0, -1);

    rt.renderPass->End();

    glClear(GL_COLOR_BUFFER_BIT);
    rt.post->Process(rt.renderPass);

    SDL_GL_SwapWindow(rt.window);
    rt.stopwatch.End();
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    switch (event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    case SDL_EVENT_MOUSE_MOTION:
        rt.mouse->x = event->motion.x;
        rt.mouse->y = event->motion.y;
        return SDL_APP_CONTINUE;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP:
        rt.mouse->buttons[event->button.button] = (event->button.type == SDL_EVENT_MOUSE_BUTTON_DOWN);
        return SDL_APP_CONTINUE;
    case SDL_EVENT_KEY_DOWN:
        return SDL_APP_CONTINUE;
    case SDL_EVENT_KEY_UP:
        rt.keyboard->keys[event->key.scancode] = (event->key.type == SDL_EVENT_KEY_DOWN);
    default:
        return SDL_APP_CONTINUE;
    }
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    delete rt.pixelBuffer;
    delete rt.vertexBuffer;
    delete rt.program;
    
    delete rt.asset;
    delete rt.post;
    delete rt.renderPass;
    delete rt.mouse;
    delete rt.keyboard;
    SDL_GL_DestroyContext(rt.gl);
    SDL_DestroyWindow(rt.window);
}