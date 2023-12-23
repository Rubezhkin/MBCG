#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "ModelLoader.h"
#include "GLModel.h"


using namespace std;

//GLFWwindow  *window;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    
    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
       /* case GLFW_KEY_SPACE:
            cur_icon_color = (cur_icon_color + 1) % 5;
            set_icon(window, cur_icon_color);
            break;
        case GLFW_KEY_X:
            glfwSetWindowIcon(window, 0, NULL);
            break;*/
    }
}

// Когда пользователь меняет размер окна, окно просмотра также должно быть скорректировано, требуя функцию обратного вызова
void framebuffer_size_callback(GLFWwindow* window,int width,int height){
         // Первые два параметра функции glViewport управляют положением нижнего левого угла окна, а третий и четвертый параметры контролируют ширину и высоту окна рендеринга
    glfwSetKeyCallback(window, key_callback);
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0,0,width,height);
}
// Объявляем функцию, чтобы определить, нажата ли конкретная клавиша
void processInput(GLFWwindow * window){
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

    ModelLoader loader;
    std::string filePath = "data.txt";
    if (!loader.isLoad(filePath)) {
        throw std::runtime_error("Failed to load model from file: " + std::string(filePath));
        return -1;
    }

    GLModel model(loader.getVertices(), loader.getIndices());
    
    //square();

    // Визуализация цикла
    while (!glfwWindowShouldClose(window)) {

        // Проверить, нажата ли конкретная клавиша, и обрабатывать ее каждый кадр
        processInput(window);

        // функция glClearColor - это функция установки состояния, используемая для установки цвета, используемого для очистки экрана
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // Функция glClear - это функция использования состояния, которая использует текущее состояние для очистки экрана с указанным цветом
        glClear(GL_COLOR_BUFFER_BIT);

        model.bind();
        glDrawElements(GL_TRIANGLES, model.nVertices()*3, GL_UNSIGNED_INT, 0);
        model.release();

                 // Функция glfwSwapBuffers будет обмениваться цветовыми буферами
        glfwSwapBuffers(window);
        // Функция glfwPollEvents проверяет, запущены ли какие-либо события
        glfwPollEvents();
    }


    // Освободить все ресурсы, выделенные ранее
    glfwTerminate();

    return 0;
}