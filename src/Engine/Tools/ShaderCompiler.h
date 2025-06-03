#ifndef SHADERCOMPILER_H
#define SHADERCOMPILER_H
#pragma once

struct compiledRenderShader_t {
    SDL_GPUShader* vertexShader;
    SDL_GPUShader* fragShader;
};

class liShaderCompiler {
public:
    liShaderCompiler();
    ~liShaderCompiler();

    bool CompileRenderShader(SDL_GPUDevice* device, std::string_view vertexSource, std::string vertexEntry, std::string_view fragSource, std::string fragEntry, compiledRenderShader_t& compiled);
private:
    shaderc_compiler_t compiler;
    shaderc_compile_options_t options;
};

#endif