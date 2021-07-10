#include "IndexBuffer.h"

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_BufferID);
}

void IndexBuffer::CreateBuffer(unsigned int* indices, GLsizeiptr size) {
	m_IndexSize = size;
	glGenBuffers(1, &m_BufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexSize, indices, GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
}

void IndexBuffer::Unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::DeleteBuffer() const {
	glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_BufferID);
}