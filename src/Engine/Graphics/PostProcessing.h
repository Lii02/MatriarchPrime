#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H
#pragma once

class liRenderShader;
class liShaderProgram;
template <typename T>
class liUniformBuffer;
class liRenderPass;

class liPostProcessing {
    struct PixelUniform {
        int padding[4];
    };
public:
    liPostProcessing();
    liPostProcessing(const liPostProcessing&) = delete;
    ~liPostProcessing();

    void Process(liRenderPass* source);
private:
    liRenderShader* renderShader;
    liShaderProgram* program;
    liRenderPass* source;
    liUniformBuffer<PixelUniform>* uniform;
    ghandle_t vao, vbo;
};

#endif