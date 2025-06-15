#include "pch.h"
#include "Material.h"
#include "Engine/Graphics/ShaderProgram.h"

liMaterial::liMaterial() {
    memset(&pixelBuffer, 0, sizeof(rawBuffer_t));
    memset(&vertexBuffer, 0, sizeof(rawBuffer_t));
}

liMaterial::~liMaterial() {
    std::free(vertexBuffer.buffer);
    std::free(pixelBuffer.buffer);
    delete pixelUniform;
    delete vertexUniform;
}

void liMaterial::SetProgram(liShaderProgram* program) {
    this->program = program;
}

void liMaterial::Render() {
    program->Bind();
    vertexUniform->Bind(program->Program(), "VertexUniform", 0);
    pixelUniform->Bind(program->Program(), "PixelUniform", 1);
}

void liMaterial::_ConstructBuffers() {
    for(auto [name, type] : values) {
        ulong_t size = _GetValueSize(type.type);
        switch(type.location) {
        case materialValueLocation_t::VERTEX:
            vertexBuffer.size += size;
            break;
        case materialValueLocation_t::PIXEL:
            pixelBuffer.size += size;
            break;
        default:
            vertexBuffer.size += size;
            pixelBuffer.size += size;
            break;
        }
    }

    this->vertexUniform = new liUniformBuffer(vertexBuffer.size);
    vertexBuffer.buffer = std::malloc(vertexBuffer.size);
    this->pixelUniform = new liUniformBuffer(pixelBuffer.size);
    pixelBuffer.buffer = std::malloc(pixelBuffer.size);
}

void liMaterial::_UpdateBuffers() {
}

ulong_t liMaterial::_GetValueSize(materialValueType_t type) {
    switch (type) {
    case materialValueType_t::INT:
        return 4;
    case materialValueType_t::FLOAT:
        return 4;
    case materialValueType_t::MAT4:
        return 64;
    case materialValueType_t::VEC2:
        return 8;
    case materialValueType_t::VEC3:
        return 12;
    case materialValueType_t::VEC4:
        return 16;
    default:
        return 0;
    }
}