#pragma once

#include "Shader.h"
#include "Rope.h"
#include "Ball.h"
#include "UserInterface.h"

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Pendulum {

private:
	Shader        shader;
	Rope          rope;
	Ball          ball;
	UserInterface UI;

	GLFWwindow*   m_Window = 0;
	glm::vec3     m_Translation;
	glm::mat4     m_ModelBall, m_ModelRope, m_View, m_Proj, m_MvpBall, m_MvpRope;
	float         m_Pivot = 0, m_Length = 0;
	float         m_Accel = 0, m_Velocity = 0, m_Angle = 0;
	unsigned int  m_WindowWidth = 0, m_WindowHeight = 0;

public:
	Pendulum(float ropeLength, float ballSize, GLFWwindow* window);
	~Pendulum() = default;

	void SetProjection(unsigned int windowWidth, unsigned int windowHeight);
	void Calculations();
	void InputHandling();
	void SetRopeLength();
	void UpdateRopePosition();
	void UpdateBallPosition();
	void DrawPendulum();
};