#include "VertexArray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_ArrayID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_ArrayID);
}

void VertexArray::LinkAttributes(const VertexBuffer& VBO, unsigned int layout, int size, GLenum type, GLsizei stride, const void* offset) {
	VBO.Bind();
	glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VertexArray::Bind() const {
	glBindVertexArray(m_ArrayID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}

void VertexArray::DeleteVertexArray() const {
	glDeleteVertexArrays(1, &m_ArrayID);
}