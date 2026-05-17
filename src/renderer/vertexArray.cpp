#include "vertexArray.h"

#include "glad/glad.h"

namespace DG {

	VertexArray::VertexArray(VertexBuffer& vertexBuffer, IndexBuffer& indexBuffer, const VertexLayout& vertexLayout)
	{	
		glGenVertexArrays(1, &m_bufferId);
		Bind();
		
		vertexBuffer.Bind();
		indexBuffer.Bind();
		vertexLayout.Apply();
	}
	
	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &m_bufferId);
	}

	VertexArray::VertexArray(VertexArray&& other) noexcept {
		m_bufferId = other.m_bufferId;

		other.m_bufferId = 0;
	}

	VertexArray& VertexArray::operator=(VertexArray&& other) noexcept {
		if (this != &other) {
			if (m_bufferId != 0) {
				glDeleteVertexArrays(1, &m_bufferId);
			}

			m_bufferId = other.m_bufferId;
			other.m_bufferId = 0;
		}

		return *this;
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_bufferId);
	}
}