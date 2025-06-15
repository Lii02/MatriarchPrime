#ifndef MATERIAL_H
#define MATERIAL_H
#pragma once
#include "Engine/Framework/Asset.h"
#include "Engine/Math/Vectors.h"
#include "Engine/Math/Matrices.h"
#include "Engine/Graphics/UniformBuffer.h"

class liShaderProgram;
class liUniformBuffer;

enum class materialValueType_t {
    INT,
    FLOAT,
    MAT4,
    VEC2,
    VEC3,
    VEC4
};

enum class materialValueLocation_t {
    VERTEX,
    PIXEL
};

struct materialValue_t {
    materialValueType_t type;
    materialValueLocation_t location;

    union {
        int intValue;
        float floatValue;
        liMat4 mat4;
        liVec2 vec2;
        liVec3 vec3;
        liVec4 vec4;
    };
};

class liMaterial : public liAsset {
public:
    liMaterial();
    liMaterial(const liMaterial&) = delete;
    ~liMaterial();
    
    void SetProgram(liShaderProgram* program);
    void Render();
private:
    void _ConstructBuffers();
    void _UpdateBuffers();
    ulong_t _GetValueSize(materialValueType_t type);

    liShaderProgram* program;
    liUniformBuffer* vertexUniform, *pixelUniform;
    rawBuffer_t vertexBuffer, pixelBuffer;
    std::map<std::string, materialValue_t> values;
};

#endif