#include "buffers.h"

#include "renderer/graphics_api.h"

namespace DG {

	VertexBuffer::VertexBuffer() {
		glGenBuffers(1, &m_bufferId);
		Bind();
	}

	VertexBuffer::~VertexBuffer() {
		if (m_bufferId != 0) {
			glDeleteBuffers(1, &m_bufferId);
		}
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept {
		m_bufferId = other.m_bufferId;
		other.m_bufferId = 0;
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept {
		if (this != &other) {
			if (m_bufferId != 0) {
				glDeleteBuffers(1, &m_bufferId);
			}

			m_bufferId = other.m_bufferId;
			other.m_bufferId = 0;
		}

		return *this;
	}

	void VertexBuffer::Bind() {
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
	}

	void VertexBuffer::SetData(void* vertexData, int vertexCount, size_t vertexSize) {
		Bind();
		glBufferData(GL_ARRAY_BUFFER, vertexCount * vertexSize, vertexData, GL_STATIC_DRAW);
	}

	void VertexBuffer::UpdateData(void* vertexData, int vertexCount, size_t vertexSize) {
		Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertexCount * vertexSize, vertexData);
	}

	IndexBuffer::IndexBuffer() {
		glGenBuffers(1, &m_bufferId);
		Bind();
	}

	IndexBuffer::~IndexBuffer() {
		if (m_bufferId != 0) {
			glDeleteBuffers(1, &m_bufferId);
		}
	}

	IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept {
		m_bufferId = other.m_bufferId;
		other.m_bufferId = 0;
	}

	IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept {
		if (this != &other) {
			if (m_bufferId != 0) {
				glDeleteBuffers(1, &m_bufferId);
			}

			m_bufferId = other.m_bufferId;
			other.m_bufferId = 0;
		}

		return *this;
	}

	void IndexBuffer::Bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
	}

	void IndexBuffer::SetData(uint32_t* indexData, int indexCount) {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(uint32_t), indexData, GL_STATIC_DRAW);
	}
}