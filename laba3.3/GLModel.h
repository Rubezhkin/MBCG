#pragma once
#include "Index_Buffer.h"
#include "Vertex_Buffer.h"
#include "ModelLoader.h"
#include "DrawableObject.h"

class GLModel : public DrawableObject {
private:
	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	Shader shader;
	int numVertices;

public:
	GLModel(const std::vector<glm::vec3>& vertices, const std::vector<glm::uvec3> indices):shader("Vshader.txt", "Fshader.txt")
	{
		numVertices = indices.size();

		vertexBuffer.create();
		indexBuffer.create();
		shader.bind();
		vertexBuffer.bind();
		indexBuffer.bind();
		indexBuffer.allocate((void*)indices.data(), sizeof(glm::uvec3) * numVertices);
		vertexBuffer.allocate((void*)vertices.data(), sizeof(glm::vec3) * numVertices);
		release();
	}

	void bind() override
	{
		vertexBuffer.bind();
		indexBuffer.bind();
		shader.release();
	}

	void release() override
	{
		vertexBuffer.release();
		indexBuffer.release();
		glDisableVertexAttribArray(0);
	}

	int nVertices() override
	{
		return numVertices;
	}

	~GLModel() {
		vertexBuffer.destroy();
		indexBuffer.destroy();
	}
};