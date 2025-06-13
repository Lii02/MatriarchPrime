#ifndef MP_H
#define MP_H
#pragma once
#include "Engine/Framework/Game.h"

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

class MPGame : public liGame {
public:
    MPGame(gameContext_t context);
    MPGame(const MPGame&) = delete;
    ~MPGame();

    virtual void Render() override;
    virtual void Update(float deltaTime) override;
    virtual void ImGui() override;
private:
    liMesh* mesh;
    liRenderShader* renderShader;
    liShaderProgram* program;
    liUniformBuffer* vertexUniform;
    liUniformBuffer* pixelUniform;
    VertexBuffer vertexBuffer;
    PixelBuffer pixelBuffer;
};

#endif