#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#pragma once
#include "UniformBuffer.h"

class liRenderShader;

class liShaderProgram {
    friend class liRenderShader;
public:
    liShaderProgram();
    liShaderProgram(const liShaderProgram&) = delete;
    ~liShaderProgram();

    bool Link(std::unordered_map<int, std::string> attribs);
    void Bind() const;
    void LoadTexture(std::string name, ghandle_t handle);
    
    inline ghandle_t Program() const { return program; }
    inline liRenderShader* RenderShader() { return renderShader; }
private:
    ghandle_t program;
    liRenderShader* renderShader;
};

#endif