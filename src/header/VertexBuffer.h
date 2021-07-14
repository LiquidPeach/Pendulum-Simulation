#pragma once

#include <glad/glad.h>

class VertexBuffer {

private:
	unsigned int  m_BufferID   = 0;
	GLsizeiptr    m_VertexSize = 0;

public:
	VertexBuffer() = default;
	~VertexBuffer();

	inline GLsizeiptr GetVertexSize() const { return m_VertexSize; }
	void CreateBuffer(float* vertices, GLsizeiptr count);
	void Bind()   const;
	void Unbind() const;
	void DeleteBuffer() const;
};