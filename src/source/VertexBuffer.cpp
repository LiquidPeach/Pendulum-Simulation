#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(GL_ARRAY_BUFFER, &m_BufferID);
}

void VertexBuffer::CreateBuffer(float* vertices, GLsizeiptr size) {
	m_VertexSize = size;
	glGenBuffers(1, &m_BufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, m_VertexSize, vertices, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::DeleteBuffer() const {
	glDeleteBuffers(GL_ARRAY_BUFFER, &m_BufferID);
}