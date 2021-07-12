#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Pendulum.h"

#include <iostream>
#include <math.h>

static const float PI = 3.141592654f;
static const float GRAVITY = 1.0f;

Pendulum::Pendulum(float ropeLength, float ballSize, GLFWwindow* window)
    : rope(ropeLength, ((ropeLength/2) + (ballSize/2))),
      ball(ballSize), translation(1.0f),
      m_ModelRope(0), m_ModelBall(0), m_View(0), m_Proj(0),
      m_MvpBall(0),   m_MvpRope(0)
{
    m_Angle = sin(PI / 4);
    m_Length = ropeLength;
    m_Pivot = (ballSize/2) + ropeLength; // Set pivot point to the top of the rope

    shader.InitShaders("src/shaders/vertexShader.vert", "src/shaders/fragmentShader.frag");
    shader.Bind();
    shader.SetUniform4f("vertexColor", 1.0f, (198.0f / 255.0f), (25.0f / 255.0f), 1.0f);
    shader.Unbind();

    // Set up ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // Set up style
    ImGui::StyleColorsDark();
    // Set up Platform and Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

Pendulum::~Pendulum() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Pendulum::SetProjection(unsigned int windowWidth, unsigned int windowHeight) {

    m_WindowWidth  = windowWidth;
    m_WindowHeight = windowHeight;

    // To calculate the appropriate position of the camera depending on the size of the rope
    float diff = ((windowHeight / 2) - m_Pivot);  // difference between top middle of screen and top of rope
    float y_view = diff + (windowHeight / 2);     // desired camera y-coordinate

    shader.Bind();

    m_ModelBall = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    m_ModelRope = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    m_View  = glm::translate(glm::mat4(1.0f), glm::vec3((windowWidth / 2), y_view, 0));
    m_Proj  = glm::ortho(0.0f, (float)m_WindowWidth, 0.0f, (float)m_WindowHeight, -1.0f, 1.0f);

    m_MvpBall = m_ModelBall * m_View * m_Proj;
    m_MvpRope = m_ModelRope * m_View * m_Proj;

    shader.SetUniformMatrix4fv("u_MvpBall", 1, GL_FALSE, &m_MvpBall[0][0]);
    shader.SetUniformMatrix4fv("u_MvpRope", 1, GL_FALSE, &m_MvpRope[0][0]);

    shader.Unbind();
}

void Pendulum::Calculations() { // TODO - Update calculations

    // Thank you The Coding Train for the Simple Pendulum Simulation video!
    float force = GRAVITY * sin(m_Angle);
    m_Accel = (-1 * force) / (translation.y * m_Length); // <- this is incorrect

    //m_Velocity *= 0.99;   // Dampening

    m_Velocity += m_Accel;
    m_Angle += m_Velocity;
}

void Pendulum::SetRopeLength() {

    m_ModelRope *= glm::scale(glm::mat4(1.0f), translation);

    float minValue = -((m_WindowHeight / 2) - (ball.GetSize() / 2));
    float maxValue =  ((m_WindowHeight / 2) - (ball.GetSize() / 2));

    ImGui::SliderFloat("Length of Rope", &translation.y, 0.25f, 2.0f);
}

void Pendulum::UpdateRopePosition() {

    glm::vec3 pivot(0.0f, m_Pivot, 0.0f);                    // 1. Create desired pivot point of rotation (where the top of the rope would be)
    m_ModelRope  = glm::translate(glm::mat4(1.0f), pivot);   // 2. translate the model to the pivot
    m_ModelRope *= glm::rotate(glm::mat4(1.0f), m_Angle, glm::vec3(0, 0, 1.0f));  //3. Rotate the model
    SetRopeLength();                                         // 4. Update Rope's length if changed with ImGui
    m_ModelRope *= glm::translate(glm::mat4(1.0f), -pivot);  // 5. bring the model back to its original position
}

void Pendulum::UpdateBallPosition() {

    float y_coord = (m_WindowHeight / 2) - (m_Length * translation.y);

    glm::vec3 pivot(0.0f, m_Pivot, 0.0f);                    // 1. Create desired pivot point of rotation (where the top of the rope would be)
    m_ModelBall  = glm::translate(glm::mat4(1.0f), pivot);   // 2. translate the model to the pivot
    m_ModelBall *= glm::rotate(glm::mat4(1.0f), m_Angle, glm::vec3(0, 0, 1.0f));  // 3. Rotate the model
    m_ModelBall *= glm::translate(glm::mat4(1.0f), glm::vec3(0, y_coord, 0));     // 4. Update Ball position if Rope changes length
    m_ModelBall *= glm::translate(glm::mat4(1.0f), -pivot);  // 5. bring the model back to its original position
}

void Pendulum::DrawPendulum() {

    shader.Bind();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

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

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    shader.Unbind();
}