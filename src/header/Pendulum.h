#pragma once

#include "Shader.h"
#include "Rope.h"
#include "Ball.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Pendulum {

private:
	Shader shader;
	Rope rope;
	Ball ball;

	glm::mat4 m_Model, m_View, m_Proj, m_Mvp;
	float m_Velocity = 0, m_Accel = 0;
	float m_Angle = 0, m_Length = 0, m_Pivot = 0;
	unsigned int m_WindowWidth = 0, m_WindowHeight = 0;

public:
	Pendulum(float rope_X, float rope_Y, float ball_X, float ball_Y);
	~Pendulum() = default;

	void SetProjection(unsigned int windowWidth, unsigned int windowHeight);

	void Calculations();

	void UpdatePosition();
	void DrawPendulum();
};