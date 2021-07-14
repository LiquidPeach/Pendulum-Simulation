#pragma once

#include <glad/glad.h>

class IndexBuffer {

private:
	unsigned int m_BufferID  = 0;
	GLsizeiptr   m_IndexSize = 0;

public:
	IndexBuffer() = default;
	~IndexBuffer();

	inline GLsizeiptr GetIndexSize() const { return m_IndexSize; }
	void CreateBuffer(unsigned int* indices, GLsizeiptr count);
	void Bind()   const;
	void Unbind() const;
	void DeleteBuffer() const;
};