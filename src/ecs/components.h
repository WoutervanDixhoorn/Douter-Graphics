#pragma once

#include "glm/glm.hpp"
#include "renderer/mesh.h"
#include "renderer/renderer.h"

namespace DG {
	
	struct TransformComponent {
		glm::vec2 position = { 0.0f, 0.0f };
	};

	struct VelocityComponent {
		glm::vec2 velocity = { 0.0f, 0.0f };
	};
	
	struct AccelerationComponent {
		glm::vec2 acceleration = { 0.0f, 0.0f };
	};

	struct MeshRenderComponent {
		DG::Mesh* mesh = nullptr;

		void Draw(glm::mat4 transform)
		{
			if (mesh == nullptr) return;

			DG::Renderer2D::DrawMesh(mesh, transform);
		}
	};
}