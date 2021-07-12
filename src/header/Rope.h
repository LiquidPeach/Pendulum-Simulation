#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"

class Rope {

private:
	VertexArray  VAO;
	VertexBuffer VBO;
	IndexBuffer  IBO;

	float m_Width, m_Length;

public:
	Rope(float ropeLength, float offset);
	~Rope() = default;

	float GetWidth()     const { return m_Width; }
	float GetLength()    const { return m_Length; }
	void  DrawRope()     const;
	void  DeleteObject() const;
};