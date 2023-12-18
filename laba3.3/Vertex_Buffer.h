#pragma once
#include "Buffer.h"
#include <vector>

class VertexBuffer : public Buffer {
private:
    GLuint id;
public:
    VertexBuffer() : id(0) {}
    VertexBuffer(GLuint id) : id(id) {}

    void create() override {
        glGenVertexArrays(1, &id);
        glGenBuffers(1, &id);
    }

    void destroy() override {
        glDeleteVertexArrays(1, &id);
        glDeleteBuffers(1, &id);
    }

    void release() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void bind() override {
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBindVertexArray(id);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    void allocate(void* data, unsigned int size) {
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
};