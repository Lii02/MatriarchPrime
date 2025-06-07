#ifndef UNIFORMBUFFER_H
#define UNIFORMBUFFER_H
#pragma once

template <typename T>
class liUniformBuffer {
public:
    liUniformBuffer() {
        glGenBuffers(1, &handle);
        glBindBuffer(GL_UNIFORM_BUFFER, handle);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(T), nullptr, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    liUniformBuffer(const liUniformBuffer&) = delete;
    
    ~liUniformBuffer() {
        glDeleteBuffers(1, &handle);
    }

    void Upload(T* data) {
        glBindBuffer(GL_UNIFORM_BUFFER, handle);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(T), data);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void Bind(ghandle_t program, std::string name, int binding = 0) {
        uint_t blockIndex = glGetUniformBlockIndex(program, name.c_str());
        glUniformBlockBinding(program, blockIndex, binding);
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, handle);
    }
    
    ghandle_t Handle() const { return handle; }
private:
    ghandle_t handle;
};

#endif