#pragma once

#include "VertexBuffer.h"

class VertexArray {

private:
	unsigned int m_ArrayID;

public:
	VertexArray();
	~VertexArray();

	void LinkAttributes(const VertexBuffer& VBO, unsigned int layout, int size, GLenum type, GLsizei stride, const void* offset);
	void Bind()   const;
	void Unbind() const;
	void DeleteVertexArray() const;
};