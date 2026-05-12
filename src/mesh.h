#pragma once

#include <cstddef>
#include <optional>

#include "vertexArray.h"
#include "buffers.h"

namespace DG {

	struct MeshData {
		void* vertexData = nullptr;
		size_t vertexSize = 0;
		size_t vertexCount = 0;

		uint32_t* indexData = nullptr;
		size_t indexCount = 0;

		VertexLayout vertexLayout;
	};

	class Mesh {
	private:
		Mesh(const MeshData& data);

	public:
		static std::optional<Mesh> Create(const MeshData& data);

		void Draw();

	private:
		std::optional<DG::VertexBuffer> m_vertexBuffer;
		std::optional<DG::IndexBuffer> m_indexBuffer;
		std::optional<DG::VertexArray> m_vertexArray;
	};

}