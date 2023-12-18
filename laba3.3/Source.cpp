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

// Когда пользователь меняет размер окна, окно просмотра также должно быть скорректировано, требуя функцию обратного вызова
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// Первые два параметра функции glViewport управляют положением нижнего левого угла окна, а третий и четвертый параметры контролируют ширину и высоту окна рендеринга
	glfwSetKeyCallback(window, key_callback);
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

// Объявляем функцию, чтобы определить, нажата ли конкретная клавиша
void processInput(GLFWwindow* window) {
	// Проверка, нажимает ли пользователь клавишу возврата (Esc) (если не нажата, glfwGetKey вернет GLFW_RELEASE, если нажата, GLFW_PRESS)
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

		// Проверить, нажата ли конкретная клавиша, и обрабатывать ее каждый кадр
		processInput(window);

		// функция glClearColor - это функция установки состояния, используемая для установки цвета, используемого для очистки экрана
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// Функция glClear - это функция использования состояния, которая использует текущее состояние для очистки экрана с указанным цветом
		glClear(GL_COLOR_BUFFER_BIT);

		model.bind();
		glDrawElements(GL_TRIANGLES, model.nVertices() * 3, GL_UNSIGNED_INT, 0);
		model.release();

		// Функция glfwSwapBuffers будет обмениваться цветовыми буферами
		glfwSwapBuffers(window);
		// Функция glfwPollEvents проверяет, запущены ли какие-либо события
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
