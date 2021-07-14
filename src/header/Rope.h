#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"

class Rope {

private:
	VertexArray  VAO;
	VertexBuffer VBO;
	IndexBuffer  IBO;

public:
	Rope(float ropeLength, float offset);
	~Rope() = default;

	void  DrawRope()     const;
	void  DeleteObject() const;
};