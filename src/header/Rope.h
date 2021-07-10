#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"

class Rope {

private:
	VertexArray  VAO;
	VertexBuffer VBO;
	IndexBuffer  IBO;

public:
	Rope(float x_coord, float y_coord, float offset);
	~Rope() = default;

	void DrawRope() const;
	void DeleteObject() const;
};