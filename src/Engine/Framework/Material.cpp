#include "pch.h"
#include "Material.h"
#include "Engine/Graphics/ShaderProgram.h"

liMaterial::liMaterial() {
    memset(&pixelBuffer, 0, sizeof(rawBuffer_t));
    memset(&vertexBuffer, 0, sizeof(rawBuffer_t));
}

liMaterial::~liMaterial() {
    delete pixelUniform;
    delete vertexUniform;
}

void liMaterial::SetProgram(liShaderProgram* program) {
    this->program = program;
}

void liMaterial::Render() {
    program->Bind();
    vertexUniform->Bind(program->Program(), "VertexUniform");
    pixelUniform->Bind(program->Program(), "PixelUniform", 1);
}