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
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    glfwSwapInterval(1);

    gladLoadGL();

    Pendulum pendulum(260.0f, 80.0f, window);
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