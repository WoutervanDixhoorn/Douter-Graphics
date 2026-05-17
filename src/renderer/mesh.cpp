#include "mesh.h"
#include "mesh.h"

#include "renderer/graphics_api.h"

#include <print>

namespace DG {

	Mesh::Mesh(const MeshData& data)
	{
		std::println(stdout, "Creating a Mesh..");

		m_vertexBuffer.emplace();
		m_vertexBuffer.value().SetData(data.vertexData, data.vertexCount, data.vertexSize);

		m_indexBuffer.emplace();
		m_indexBuffer.value().SetData(data.indexData, data.indexCount);

		m_vertexArray.emplace(m_vertexBuffer.value(), m_indexBuffer.value(), data.vertexLayout);
	}

	std::optional<Mesh> Mesh::Create(const MeshData& data)
	{
		if (data.vertexCount <= 0 || data.vertexData == nullptr) {
			std::println(stderr, "Creating a Mesh failed, MeshData needs to be filled with data...");
			return std::nullopt;
		}

		return Mesh(data);
	}

	void Mesh::Draw()
	{
		m_vertexArray.value().Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	}

}