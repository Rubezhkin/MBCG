#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "glad.c"

using namespace std;

//GLFWwindow* window;

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

void triang()
{
	GLuint vbo = 0; 
	GLuint vao = 0;

	float points[] = {
	   -0.5f,  0.5f,  0.0f,
	   1.0f,  0.0f,  1.0f,
	   -0.5f,  -0.5f,  0.0f,
	   0.0f,  0.0f,  0.0f,
	   0.5f,  -0.5f,  0.0f,
	   0.0f,  1.0f,  1.0f,
		- 0.5f,  0.5f,  0.0f,
	   1.0f,  0.0f,  1.0f,
	   0.5f,  0.5f,  0.0f,
	   1.0f,  1.0f,  1.0f,
	   0.5f,  -0.5f,  0.0f,
	   0.0f,  1.0f,  1.0f
	};

	const char* vertex_shader =
		"#version 400\n"
		"in vec3 vp;"
		"in vec3 color;"
		"out vec3 vcolour;"
		"void main() {"
		"  gl_Position = vec4(vp, 1.0);"
		"  vcolour = color;"
		"}";

	const char* fragment_shader =
		"#version 400\n"
		"in vec3 vcolour;"
		"out vec4 frag_colour;"
		"void main() {"
		"  frag_colour = vec4(vcolour, 1.0);"
		"}";


	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint shader_programme = glCreateProgram();
	glGenBuffers(1, &vbo);// создание буфера
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // активизация буфера
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(float), points, GL_STATIC_DRAW); // передача данных в буфер
	glGenVertexArrays(1, &vao);  // созданиые массива вершин
	glBindVertexArray(vao); // активизация массива
	glEnableVertexAttribArray(0); // активизация индекса 
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // деактивизация
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); // указание данных для передачи в шейдер
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	


	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);

	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	glUseProgram(shader_programme);
	glBindVertexArray(vao);
	// draw points 0-6 from the currently bound VAO with current in-use shader

	// update other events like input handling 
}

void draw()
{
	// binf shader
	// bind vbo vao
	// bind ebo
	glDrawArrays(GL_TRIANGLES, 0, 6);
	// release ebo
	// release vbo vao
	// release shader

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

int main(int argc, char** argv)
{ // Инициализация GLFW
	glfwInit();

	// Установить номер основной версии OpenGL (Major) и номер вспомогательной версии (Minor) в 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Использование режима ядра (Core-profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Если это система MacOS, вам понадобится следующая строка кода для работы конфигурации
//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	 // Создать объект окна
	GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW + GLAD", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	// Уведомить GLFW, чтобы установить контекст нашего окна в качестве основного контекста текущего потока
	glfwMakeContextCurrent(window);

	// GLAD используется для управления указателем функции OpenGL, нам нужно инициализировать GLAD перед вызовом любой функции OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	// Зарегистрируем определенную функцию обратного вызова и сообщаем GLFW вызывать эту функцию при каждом изменении размера окна
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	triang();
	
	// Визуализация цикла
	while (!glfwWindowShouldClose(window)) {

		// Проверить, нажата ли конкретная клавиша, и обрабатывать ее каждый кадр
		processInput(window);

		// функция glClearColor - это функция установки состояния, используемая для установки цвета, используемого для очистки экрана
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// Функция glClear - это функция использования состояния, которая использует текущее состояние для очистки экрана с указанным цветом
		glClear(GL_COLOR_BUFFER_BIT);
		//triang(); - запускаем отрисовку треугольника. Работает именно в этом месте!
		draw();
		// Функция glfwSwapBuffers будет обмениваться цветовыми буферами
		glfwSwapBuffers(window);
		// Функция glfwPollEvents проверяет, запущены ли какие-либо события
		glfwPollEvents();
	}


	// Освободить все ресурсы, выделенные ранее
	glfwTerminate();

	return 0;
}