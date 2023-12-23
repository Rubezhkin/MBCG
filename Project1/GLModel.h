#pragma once
#include "DrawableObject.h"
#include <glm/common.hpp>
#include <vector>
#include <string>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ModelLoader.h"

class GLModel : public DrawableObject {
public:
    GLModel(std::vector<glm::vec3> vertexData, std::vector<glm::uvec3> indexData):verticies(vertexData), indices(indexData),shader() {
        vao.create();
        ebo.create();

        bind();

        vao.allocate(verticies.data(), sizeof(glm::vec3) * verticies.size());
        ebo.allocate(indices.data(), sizeof(glm::uvec3) * indices.size());

        release();
    }

    void bind() override {
        
        vao.bind();
        ebo.bind();
        shader.bind();
    }

    void release() override {
        vao.release();
        ebo.release();
    }

    int nVertices() override {
        return indices.size();
    }


private:
    VertexBuffer vao;
    IndexBuffer ebo;
    Shader shader;


    std::vector<glm::vec3> verticies;
    std::vector<glm::uvec3> indices;
};