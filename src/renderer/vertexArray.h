#pragma once

#include "buffers.h"
#include "vertexLayout.h"

namespace DG {

	class VertexArray {
	public:
		VertexArray(VertexBuffer& vertexBuffer, IndexBuffer& indexBuffer, const VertexLayout& layout);
		VertexArray(VertexBuffer& vertexBuffer, const VertexLayout& layout);

		~VertexArray();
		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;
		VertexArray(VertexArray&& other) noexcept;
		VertexArray& operator=(VertexArray&& other) noexcept;

		void Bind();
		void Unbind();
	private:
		unsigned int m_bufferId;
	};

}