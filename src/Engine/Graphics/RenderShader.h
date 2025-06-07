#ifndef RENDERSHADER_H
#define RENDERSHADER_H
#pragma once

class liShaderProgram;

class liRenderShader {
    friend class liShaderProgram;
public:
    liRenderShader();
    liRenderShader(class liRenderShader&) = delete;
    ~liRenderShader();

    bool CompileVertex(std::string_view source);
    bool CompilePixel(std::string_view source);
    void Attach(liShaderProgram* program);
private:
    ghandle_t vertex, pixel;
};

#endif