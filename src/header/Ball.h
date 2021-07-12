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

	float m_Size;

public:
	Ball(float size);
	~Ball() = default;

	float GetSize()      const { return m_Size; }
	void  DrawBall()     const;
	void  DeleteObject() const;
};