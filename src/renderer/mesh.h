#pragma once

#include <cstddef>
#include <optional>
#include <vector>

#include "rendererTypes.h"
#include "vertexArray.h"
#include "buffers.h"

namespace DG {

	struct MeshData {
		std::vector<Vertex> Vertices;
		std::vector<uint32_t> Indices;
	};

	class Mesh {
	private:
		Mesh(const MeshData& data);

	public:
		static std::optional<Mesh> Create(const MeshData& data);

		void Bind();

	private:
		std::optional<DG::VertexBuffer> m_vertexBuffer;
		std::optional<DG::IndexBuffer> m_indexBuffer;
		std::optional<DG::VertexArray> m_vertexArray;
	};

}