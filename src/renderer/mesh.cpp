#include "mesh.h"
#include "mesh.h"

#include "renderer/graphics_api.h"

#include <print>

namespace DG {

	Mesh::Mesh(const MeshData& data)
	{
		std::println(stdout, "Creating a Mesh..");

		m_vertexBuffer.emplace();
		m_vertexBuffer.value().SetData((void*)data.Vertices.data(), data.Vertices.size(), sizeof(Vertex));

		m_indexBuffer.emplace();
		m_indexBuffer.value().SetData(data.Indices.data(), data.Indices.size());

		m_vertexArray.emplace(m_vertexBuffer.value(), m_indexBuffer.value(), VertexLayout::GetDefaultMeshLayout());
	}

	std::optional<Mesh> Mesh::Create(const MeshData& data)
	{
		if (data.Vertices.size() <= 0) {
			std::println(stderr, "Creating a Mesh failed, MeshData needs to be filled with data...");
			return std::nullopt;
		}

		return Mesh(data);
	}

	void Mesh::Bind() {
		m_vertexArray.value().Bind();
	}

}