#include "pch.h"
#include "ShaderCompiler.h"

liShaderCompiler::liShaderCompiler() {
    this->compiler = shaderc_compiler_initialize();
    this->options = shaderc_compile_options_initialize();

    shaderc_compile_options_set_invert_y(options, true);
#ifdef _DEBUG
    shaderc_compile_options_set_generate_debug_info(options);
#endif
}

liShaderCompiler::~liShaderCompiler() {
    shaderc_compile_options_release(options);
    shaderc_compiler_release(compiler);
}

bool liShaderCompiler::CompileRenderShader(SDL_GPUDevice* device, std::string_view vertexSource, std::string vertexEntry, std::string_view fragSource, std::string fragEntry, compiledRenderShader_t& compiled) {
    shaderc_compilation_result_t result;
    SDL_GPUShaderCreateInfo createInfo = { 0 };
    bool vertexStatus = true;
    bool fragStatus = true;

    // Vertex shader
    result = shaderc_compile_into_spv(compiler, vertexSource.data(), vertexSource.length(), shaderc_vertex_shader, "", vertexEntry.c_str(), options);
    if (shaderc_result_get_compilation_status(result) != shaderc_compilation_status_success) {
		std::cout << shaderc_result_get_error_message(result) << std::endl;
		vertexStatus = false;
	}
    createInfo.code_size = shaderc_result_get_length(result);
    createInfo.code = (Uint8*)shaderc_result_get_bytes(result);
    createInfo.entrypoint = vertexEntry.c_str();
    createInfo.format = SDL_GPU_SHADERFORMAT_SPIRV;
    createInfo.stage = SDL_GPU_SHADERSTAGE_VERTEX;
    SDL_GPUShader* vertexShader = SDL_CreateGPUShader(device, &createInfo);
    compiled.vertexShader = vertexShader;

    result = shaderc_compile_into_spv(compiler, fragSource.data(), fragSource.length(), shaderc_fragment_shader, "", fragEntry.c_str(), options);
    if (shaderc_result_get_compilation_status(result) != shaderc_compilation_status_success) {
		std::cout << shaderc_result_get_error_message(result) << std::endl;
		fragStatus = false;
	}
    createInfo.code_size = shaderc_result_get_length(result);
    createInfo.code = (Uint8*)shaderc_result_get_bytes(result);
    createInfo.entrypoint = fragEntry.c_str();
    createInfo.format = SDL_GPU_SHADERFORMAT_SPIRV;
    createInfo.stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
    SDL_GPUShader* fragShader = SDL_CreateGPUShader(device, &createInfo);
    compiled.fragShader = fragShader;

    return vertexStatus && fragStatus;
}