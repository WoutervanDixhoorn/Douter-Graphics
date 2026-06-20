#pragma once

#include <vector>
#include <memory>

#include "glm/glm.hpp"

#include "buffers.h"
#include "vertexArray.h"
#include "vertexLayout.h"
#include "camera.h"
#include "shader.h"

namespace DG {

	class DebugRenderer {
	public:
		static void Init();

		static void DrawCircle(glm::vec2 center, float radius);
		static void DrawLine(glm::vec2 startPos, glm::vec2 endPos);

		static void Begin(Camera& camera);
		static void End();

	private:
		static void initializeCircleRenderer();
		static void initializeLineRenderer();
		
		static void flushCircleRenderer();
		static void flushLineRenderer();

	private:
		struct CircleVertex {
			glm::vec2 worldPos, localPos;
			glm::vec4 color;
		};

		struct RendererData {
			std::unique_ptr<Shader> circleShader;
			std::unique_ptr<VertexArray> circleVAO;
			std::unique_ptr<VertexBuffer> circleVBO;
			std::unique_ptr<IndexBuffer> circleIBO;

			std::vector<CircleVertex> circleVertices;
			std::vector<uint32_t> circleIndices;
			size_t MAX_CIRCLES = 2000;

			std::vector<glm::vec2> lineVertices;
			std::unique_ptr<Shader> lineShader;
			std::unique_ptr<VertexArray> lineVAO;
			std::unique_ptr<VertexBuffer> lineVBO;
			const size_t MAX_LINES = 4000;

			Camera* camera;
		};

		static RendererData* s_data;
	};

}