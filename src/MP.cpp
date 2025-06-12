#include "pch.h"
#include "MP.h"
#include "imgui/imgui.h"

liVertexList vertices = {
    liVertex(liVec3(-0.5f, -0.5f, 0.0f), liVec2(0.0f, 0.0f), liVec3()),
    liVertex(liVec3(0.5f, -0.5f, 0.0f), liVec2(1.0f, 0.0f), liVec3()),
    liVertex(liVec3(-0.5f, 0.5f, 0.0f), liVec2(0.0f, 1.0f), liVec3()),
    liVertex(liVec3(0.5f, 0.5f, 0.0f), liVec2(1.0f, 1.0f), liVec3())
};

liUIntBuffer indices = {
    0, 1, 2, 1, 2, 3
};

MPGame::MPGame(gameContext_t context)
    : liGame(context) {

    mesh = new liMesh(vertices.size(), indices.size());
    mesh->UploadVertices(&vertices);
    mesh->UploadIndices(&indices);
    Assets()->LoadAsset("TestMesh", mesh);
    
    renderShader = new liRenderShader();
    std::string vertexSource, pixelSource;
    liFileIO::Read("./Assets/Shaders/standard.vert", vertexSource);
    liFileIO::Read("./Assets/Shaders/standard.frag", pixelSource);
    renderShader->CompileVertex(vertexSource);
    renderShader->CompilePixel(pixelSource);
    Assets()->LoadAsset("TestShader", renderShader);

    program = new liShaderProgram();
    renderShader->Attach(program);
    program->Link({ { 0, "position" }, { 1, "texCoord" }, { 2, "normal" } });

    vertexUniform = new liUniformBuffer<VertexBuffer>();
    vertexBuffer.model = liMat4::Translate(liVec3(0, 0, -1));
    vertexBuffer.projection = liMat4::Perspective(70.0f, 1.6f, 0.1f, 1000.0f);

    pixelUniform = new liUniformBuffer<PixelBuffer>();
    pixelBuffer.color = liColor(0.5f, 1.0f, 0.25f, 1.0f);
}

MPGame::~MPGame() {
    delete pixelUniform;
    delete vertexUniform;
    delete program;
}

void MPGame::Render() {
    program->Bind();
    vertexUniform->Bind(program->Program(), "VertexUniform", 0);
    vertexUniform->Upload(&vertexBuffer);
    pixelUniform->Bind(program->Program(), "PixelUniform", 1);
    pixelUniform->Upload(&pixelBuffer);
    mesh->Draw(cullMode_t::BACK_FACE, topology_t::TRIANGLES, 0, -1);
}

void MPGame::Update(float deltaTime) {
}

void MPGame::ImGui() {
}