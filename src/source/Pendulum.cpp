#include "Pendulum.h"

#include <iostream>
#include <math.h>

static const float PI      = 3.141592654f;
static const float GRAVITY = 1.0f;
static bool isHovering     = false;
static bool isButtonDown   = false;

Pendulum::Pendulum(float ropeLength, float ballSize, GLFWwindow * window)
    : rope(ropeLength, ((ropeLength / 2) + (ballSize / 2))),
      ball(ballSize), UI(window),
      m_ModelRope(0), m_ModelBall(0), m_View(0), m_Proj(0),
      m_MvpBall(0), m_MvpRope(0), m_Translation(1.0f)
{
    m_Window = window;
    m_Angle  = 0.0f;
    m_Length = ropeLength;
    m_Pivot  = (ballSize / 2) + ropeLength; // Set pivot point to the top of the rope

    shader.InitShaders("src/shaders/mainShader.vert", "src/shaders/mainShader.frag");
    shader.Bind();
    shader.SetUniform4f("vertexColor", 1.0f, (198.0f / 255.0f), (25.0f / 255.0f), 1.0f);
    shader.Unbind();
}

void Pendulum::SetProjection(unsigned int windowWidth, unsigned int windowHeight) {

    m_WindowWidth = windowWidth;
    m_WindowHeight = windowHeight;

    // To calculate the appropriate position of the camera depending on the size of the rope
    float diff = ((windowHeight / 2) - m_Pivot);  // difference between top middle of screen and top of rope
    float y_view = diff + (windowHeight / 2);     // desired camera y-coordinate

    shader.Bind();

    m_ModelBall = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    m_ModelRope = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    m_View = glm::translate(glm::mat4(1.0f), glm::vec3((windowWidth / 2), y_view, 0));
    m_Proj = glm::ortho(0.0f, (float)m_WindowWidth, 0.0f, (float)m_WindowHeight, -1.0f, 1.0f);

    m_MvpBall = m_ModelBall * m_View * m_Proj;
    m_MvpRope = m_ModelRope * m_View * m_Proj;

    shader.SetUniformMatrix4fv("u_MvpBall", 1, GL_FALSE, &m_MvpBall[0][0]);
    shader.SetUniformMatrix4fv("u_MvpRope", 1, GL_FALSE, &m_MvpRope[0][0]);

    shader.Unbind();
}

void Pendulum::Calculations() { // TODO - Update calculations

    // Thank you The Coding Train for the Simple Pendulum Simulation video!
    if (!isButtonDown) {
        float force = GRAVITY * sin(m_Angle);
        m_Accel = (-1 * force) / (m_Translation.y * m_Length);

        m_Velocity *= 0.99;   // Dampening

        m_Velocity += m_Accel;
        m_Angle += m_Velocity;
    }
}

void Pendulum::InputHandling() {

    /*        Model matrix
    [ X-axis.x, X-axis.y, X-axis.z, 0 ]
    [ Y-axis.x, Y-axis.y, Y-axis.z, 0 ]
    [ Z-axis.x, Z-axis.y, Z-axis.z, 0 ]
    [ transl.x, transl.y, transl.z, 1 ]
    */

    // Get balls position measured in the screen's coordinates, where the top left is the origin
    float xBallPos = m_ModelBall[3][0] + (m_WindowWidth / 2);
    float yBallPos = (m_WindowHeight / 2) - m_ModelBall[3][1];

    // Bounds of the ball
    float minX = xBallPos - (ball.GetSize() / 2);
    float maxX = xBallPos + (ball.GetSize() / 2);
    float minY = yBallPos - (ball.GetSize() / 2);
    float maxY = yBallPos + (ball.GetSize() / 2);

    double xMousePos, yMousePos;
    glfwGetCursorPos(m_Window, &xMousePos, &yMousePos);

    if (xMousePos > minX && xMousePos < maxX) {   // If the mouse is within the bounds of the ball
        if (yMousePos > minY && yMousePos < maxY)
            isHovering = true;
        else
            isHovering = false;
    }
    else
        isHovering = false;

    int state = glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT);
    if (isHovering && state == GLFW_PRESS)
        isButtonDown = true;
    else
        isButtonDown = false;
}

void Pendulum::SetRopeLength() { // Also setting rope angle with ImGui temporarily

    m_ModelRope *= glm::scale(glm::mat4(1.0f), m_Translation);

    UI.SetSlider("Length", &m_Translation.y, 0.25f, 2.0f);
    UI.SetSlider("Angle (radians)", &m_Angle, glm::radians(-90.0f), glm::radians(90.0f));

    if (UI.IsButtonPressed()) {
        m_Accel    = 0.0f;
        m_Velocity = 0.0f;
    }
}

void Pendulum::UpdateRopePosition() {

    glm::vec3 pivot(0.0f, m_Pivot, 0.0f);                    // 1. Create desired pivot point of rotation (where the top of the rope would be)
    m_ModelRope  = glm::translate(glm::mat4(1.0f), pivot);   // 2. translate the model to the pivot
    m_ModelRope *= glm::rotate(glm::mat4(1.0f), m_Angle, glm::vec3(0, 0, 1.0f));  //3. Rotate the model
    SetRopeLength();                                         // 4. Update Rope's length if changed with ImGui
    m_ModelRope *= glm::translate(glm::mat4(1.0f), -pivot);  // 5. bring the model back to its original position
}

void Pendulum::UpdateBallPosition() {

    float y_coord = (m_WindowHeight / 2) - (m_Length * m_Translation.y);

    glm::vec3 pivot(0.0f, m_Pivot, 0.0f);                    // 1. Create desired pivot point of rotation (where the top of the rope would be)
    m_ModelBall  = glm::translate(glm::mat4(1.0f), pivot);   // 2. translate the model to the pivot
    m_ModelBall *= glm::rotate(glm::mat4(1.0f), m_Angle, glm::vec3(0, 0, 1.0f));  // 3. Rotate the model
    m_ModelBall *= glm::translate(glm::mat4(1.0f), glm::vec3(0, y_coord, 0));     // 4. Update Ball position if Rope changes length
    m_ModelBall *= glm::translate(glm::mat4(1.0f), -pivot);  // 5. bring the model back to its original position
}

void Pendulum::DrawPendulum() {

    //InputHandling();

    shader.Bind();
    UI.NewFrame();

    Calculations();
    UpdateBallPosition();
    UpdateRopePosition();

    /* Render Rope */
    m_MvpRope = m_Proj * m_View * m_ModelRope;
    shader.SetUniform1i("rope", 1);
    shader.SetUniformMatrix4fv("u_MvpRope", 1, GL_FALSE, &m_MvpRope[0][0]);
    shader.SetUniform1i("useTex", 0); // No texture in use

    rope.DrawRope();

    /* Render Ball */
    m_MvpBall = m_Proj * m_View * m_ModelBall;
    shader.SetUniform1i("rope", 0);
    shader.SetUniformMatrix4fv("u_MvpBall", 1, GL_FALSE, &m_MvpBall[0][0]);
    shader.SetUniform1i("useTex", 1); // Texture in use

    ball.DrawBall();

    UI.Render();
    shader.Unbind();
}