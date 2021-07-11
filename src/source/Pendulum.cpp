#include "Pendulum.h"

#include <iostream>
#include <math.h>

static const float PI = 3.141592654f;
static const float GRAVITY = 1.0f;

Pendulum::Pendulum(float rope_X, float rope_Y, float ball_X, float ball_Y)
    : rope(rope_X, rope_Y, (rope_Y + ball_Y)),
      ball(ball_X, ball_Y),
      m_Model(0), m_View(0), m_Proj(0), m_Mvp(0)
{
    m_Angle  = sin(PI / 4);
    m_Length = rope_Y * 2;
    m_Pivot  = ball_Y + m_Length;

    shader.InitShaders("src/shaders/vertexShader.vert", "src/shaders/fragmentShader.frag");
    shader.Bind();
    // The ball will have a texture and the rope will not. Using the uniform "useTex", I can tell the fragment shader whether there
    // will be a texture in use or not. (Thank you Rid on theCherno's Discord server)
    shader.SetUniform1i("useTex", 1);
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

    m_Proj  = glm::ortho(0.0f, (float)m_WindowWidth, 0.0f, (float)m_WindowHeight, -1.0f, 1.0f);
    m_View  = glm::translate(glm::mat4(1.0f), glm::vec3((windowWidth / 2), y_view, 0));
    m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    m_Mvp = m_Proj * m_View * m_Model;
    shader.SetUniformMatrix4fv("u_MVP", 1, GL_FALSE, &m_Mvp[0][0]);

    shader.Unbind();
}

void Pendulum::Calculations() {

    // Thank you The Coding Train for the Simple Pendulum Simulation video!
    float force = GRAVITY * sin(m_Angle);
    m_Accel = (-1 * force) / m_Length;

    //m_Velocity *= 0.99;   // Dampening

    m_Velocity += m_Accel;
    m_Angle += m_Velocity;
}

void Pendulum::UpdatePosition() {

    glm::vec3 pivot(0, m_Pivot, 0);                      // 1. Create desired pivot point of rotation (where the top of the rope would be)
    m_Model  = glm::translate(glm::mat4(1.0f), pivot);   // 2. translate the model to the pivot
    m_Model *= glm::rotate(glm::mat4(1.0f), m_Angle, glm::vec3(0, 0, 1.0f));  //3. Rotate the model
    m_Model *= glm::translate(glm::mat4(1.0f), -pivot);  // 4. bring the model back to its original position
}

void Pendulum::DrawPendulum() {

    shader.Bind();

    Calculations();
    UpdatePosition();

    m_Mvp = m_Proj * m_View * m_Model;
    shader.SetUniformMatrix4fv("u_MVP", 1, GL_FALSE, &m_Mvp[0][0]);

    shader.SetUniform1i("useTex", 0); // No texture in use
    rope.DrawRope();
    shader.SetUniform1i("useTex", 1); // Texture in use
    ball.DrawBall();

    shader.Unbind();
}