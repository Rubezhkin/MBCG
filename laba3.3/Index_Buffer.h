#pragma once
#include "Buffer.h"


class IndexBuffer : public Buffer {
private:
    GLuint id;
public:
    IndexBuffer() : id(0) {}
    IndexBuffer(GLuint id) : id(id) {}

    void create() override {
        glGenBuffers(1, &id);
    }

    void destroy() override {
        glDeleteBuffers(1, &id);
    }

    virtual void release() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void bind() override {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void setAttributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) {
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        glEnableVertexAttribArray(index);
    }

    void allocate(void* data, unsigned int size) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }


};