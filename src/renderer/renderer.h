#pragma once

#include <memory>
#include <vector>

#include "vertexArray.h"
#include "buffers.h"
#include "shader.h"
#include "camera.h"

#include "glm/glm.hpp"

namespace DG {

	class Renderer2D {
	public:
		static void Init();

		static void Clear(float r, float g, float b, float a);

		static void DrawLine(glm::vec2 startPos, glm::vec2 endPos);

		static void BeginScene(DG::Camera& camera);
		static void EndScene();

		static void BeginImGui();
		static void EndImGui();
	private:
		struct Renderer2DData {
			std::vector<glm::vec2> m_lineVertices;

			std::unique_ptr<DG::Shader> m_lineShader;
			std::unique_ptr<DG::VertexArray> m_lineVAO;
			std::unique_ptr<DG::VertexBuffer> m_lineVBO;

			DG::Camera* m_camera;
			const size_t MAX_LINES = 2000;
		};

		static struct Renderer2DData* m_rendererData;
	};

}