#include "Rope.h"

Rope::Rope(float x_coord, float y_coord, float offset) { // Offset is to set the rope at the top of the ball (to to form the pendulum shape)

	float vertices[] = {
		//	Positions	
		-x_coord, -y_coord + offset,
		 x_coord, -y_coord + offset,
		 x_coord,  y_coord + offset,
		-x_coord,  y_coord + offset
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VAO.Bind();
	VBO.CreateBuffer(vertices, sizeof(vertices));
	IBO.CreateBuffer(indices, sizeof(indices));

	VAO.LinkAttributes(VBO, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
}

void Rope::DrawRope() const {
	VAO.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO.Unbind();
}

void Rope::DeleteObject() const {
	VAO.DeleteVertexArray();
	VBO.DeleteBuffer();
	IBO.DeleteBuffer();
}