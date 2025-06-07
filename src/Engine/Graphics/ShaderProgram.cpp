#include "pch.h"
#include "ShaderProgram.h"
#include "RenderShader.h"

liShaderProgram::liShaderProgram() {
    this->program = glCreateProgram();
}

liShaderProgram::~liShaderProgram() {
    glDeleteProgram(program);
}

bool liShaderProgram::Link(std::unordered_map<int, std::string> attribs) {
    glLinkProgram(program);
    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if(!status) {
        return false;
    }
    for(ulong_t i = 0; i < attribs.size(); i++) {
        glBindAttribLocation(program, i, attribs[i].c_str());
    }
    return true;
}

void liShaderProgram::Bind() const {
    glUseProgram(program);
}