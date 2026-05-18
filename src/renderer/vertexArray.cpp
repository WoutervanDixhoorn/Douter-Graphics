#include "vertexArray.h"

#include "renderer/graphics_api.h"

namespace DG {

	VertexArray::VertexArray(VertexBuffer& vertexBuffer, IndexBuffer& indexBuffer, const VertexLayout& vertexLayout)
	{	
		glGenVertexArrays(1, &m_bufferId);
		Bind();
	
		vertexBuffer.Bind();
		indexBuffer.Bind();
		vertexLayout.Apply();

		Unbind();
	}

	VertexArray::VertexArray(VertexBuffer& vertexBuffer, const VertexLayout& vertexLayout)
	{
		glGenVertexArrays(1, &m_bufferId);
		Bind();

		vertexBuffer.Bind();
		vertexLayout.Apply();

		Unbind();
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

	void VertexArray::Bind() {
		glBindVertexArray(m_bufferId);
	}

	void VertexArray::Unbind() {
		glBindVertexArray(0);
	}
}