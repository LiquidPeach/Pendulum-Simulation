#include "Ball.h"

Ball::Ball(float size) 
	: m_Size(size)
{
	float vertices[] = {
		//	Positions		     Texture
			-(size/2), -(size/2),  0.0f, 0.0f,
			 (size/2), -(size/2),  1.0f, 0.0f,
			 (size/2),  (size/2),  1.0f, 1.0f,
			-(size/2),  (size/2),  0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VAO.Bind();
	VBO.CreateBuffer(vertices, sizeof(vertices));
	IBO.CreateBuffer(indices,  sizeof(indices));
	texture.CreateTexture("src/images/Bob.png");
	texture.Bind();

	VAO.LinkAttributes(VBO, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
	VAO.LinkAttributes(VBO, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// The texture looks like trash if you don't blend lol
	glEnable(GL_BLEND);
}

void Ball::DrawBall() const {
	VAO.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO.Unbind();
}

void Ball::DeleteObject() const {
	VAO.DeleteVertexArray();
	VBO.DeleteBuffer();
	IBO.DeleteBuffer();
	texture.DeleteTexture();
}