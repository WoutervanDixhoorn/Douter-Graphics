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

		static void DrawCircle(glm::vec3 center, float radius, glm::vec4 color, float fillLevel);
		static void DrawCircle(glm::vec2 center, float radius, float fillLevel);
		static void DrawCircle(glm::vec2 center, float radius, glm::vec4 color);
		static void DrawFilledCircle(glm::vec2 center, float radius, glm::vec4 color);

		static void DrawLine(glm::vec3 startPos, glm::vec3 endPos, glm::vec4 color);
		static void DrawLine(glm::vec2 startPos, glm::vec2 endPos);
		static void DrawLine(glm::vec2 startPos, glm::vec2 endPos, glm::vec4 color);

		static void Begin(Camera& camera);
		static void End();

	private:
		static void initializeCircleRenderer();
		static void initializeLineRenderer();
		
		static void flushCircleRenderer();
		static void flushLineRenderer();

	private:
		struct LineVertex {
			glm::vec3 pos;
			glm::vec4 color;
		};

		struct CircleVertex {
			glm::vec3 worldPos;
			glm::vec2 localPos;
			glm::vec4 color;
			float fillLevel;
		};

		struct RendererData {
			std::unique_ptr<Shader> circleShader;
			std::unique_ptr<VertexArray> circleVAO;
			std::unique_ptr<VertexBuffer> circleVBO;
			std::unique_ptr<IndexBuffer> circleIBO;

			std::vector<CircleVertex> circleVertices;
			std::vector<uint32_t> circleIndices;
			size_t MAX_CIRCLES = 20000;

			std::vector<LineVertex> lineVertices;
			std::unique_ptr<Shader> lineShader;
			std::unique_ptr<VertexArray> lineVAO;
			std::unique_ptr<VertexBuffer> lineVBO;
			const size_t MAX_LINES = 40000;

			Camera* camera;
		};

		static RendererData* s_data;
	};

}