#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Pendulum.h"

int main() {

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(800, 600, "Pendulum", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    gladLoadGL();

    Pendulum pendulum(5.0f, 260.0f, 40.0f, 40.0f);
    pendulum.SetProjection(800, 600);

    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.0f, (77.0f / 255.0f), (169.0f / 255.0f), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        pendulum.DrawPendulum();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}