#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"

class Ball {

private:
	VertexArray  VAO;
	VertexBuffer VBO;
	IndexBuffer  IBO;
	Texture texture;

public:
	Ball(float x_coord, float y_coord);
	~Ball() = default;

	void DrawBall() const;
	void DeleteObject() const;
};