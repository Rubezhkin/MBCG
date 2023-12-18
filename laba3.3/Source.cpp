#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Vertex_Buffer.h"
#include "Index_Buffer.h"
#include "Buffer.h"
#include "Shader.h"
#include "ModelLoader.h"
#include "GLModel.h"

using namespace std;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	}
}

// ����� ������������ ������ ������ ����, ���� ��������� ����� ������ ���� ���������������, ������ ������� ��������� ������
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// ������ ��� ��������� ������� glViewport ��������� ���������� ������� ������ ���� ����, � ������ � ��������� ��������� ������������ ������ � ������ ���� ����������
	glfwSetKeyCallback(window, key_callback);
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

// ��������� �������, ����� ����������, ������ �� ���������� �������
void processInput(GLFWwindow* window) {
	// ��������, �������� �� ������������ ������� �������� (Esc) (���� �� ������, glfwGetKey ������ GLFW_RELEASE, ���� ������, GLFW_PRESS)
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

const unsigned int width = 800;
const unsigned int height = 800;

int main(int argc, char** argv)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW + GLAD", NULL, NULL);

	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	ModelLoader loader;
	std::string filePath = "data.txt";
	if (!loader.isLoad(filePath)) {
		throw std::runtime_error("Failed to load model from file: " + std::string(filePath));
		return -1;
	}
	
	GLModel model(loader.getVertices(), loader.getIndices());
	
	while (!glfwWindowShouldClose(window)) {

		// ���������, ������ �� ���������� �������, � ������������ �� ������ ����
		processInput(window);

		// ������� glClearColor - ��� ������� ��������� ���������, ������������ ��� ��������� �����, ������������� ��� ������� ������
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// ������� glClear - ��� ������� ������������� ���������, ������� ���������� ������� ��������� ��� ������� ������ � ��������� ������
		glClear(GL_COLOR_BUFFER_BIT);

		model.bind();
		glDrawElements(GL_TRIANGLES, model.nVertices() * 3, GL_UNSIGNED_INT, 0);
		model.release();

		// ������� glfwSwapBuffers ����� ������������ ��������� ��������
		glfwSwapBuffers(window);
		// ������� glfwPollEvents ���������, �������� �� �����-���� �������
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
