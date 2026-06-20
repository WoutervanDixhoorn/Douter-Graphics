#include "debugRenderer.h"

#include <print>

#include "graphics_api.h"
#include "vertexLayout.h"

namespace DG {

	DebugRenderer::RendererData* DebugRenderer::s_data = nullptr;

	void DebugRenderer::Init() {
		s_data = new DebugRenderer::RendererData{};

		initializeCircleRenderer();
		initializeLineRenderer();
	}

	void DebugRenderer::initializeCircleRenderer() {
		s_data->circleShader = std::make_unique<Shader>(Shader::LoadFromFile("assets/douter/shaders/circle.glsl"));

		s_data->circleVertices.reserve(s_data->MAX_CIRCLES * 4);
		s_data->circleVBO = std::make_unique<VertexBuffer>();
		s_data->circleVBO->SetData(nullptr, s_data->MAX_CIRCLES * 4, sizeof(CircleVertex));

		s_data->circleIndices.reserve(s_data->MAX_CIRCLES * 6);
		s_data->circleIBO = std::make_unique<IndexBuffer>();
		s_data->circleIBO->SetData(nullptr, s_data->MAX_CIRCLES * 6);

		VertexLayout circleLayout;
		circleLayout.AddAttribute(AttribType::FLOAT_ATTRIB, 2);
		circleLayout.AddAttribute(AttribType::FLOAT_ATTRIB, 2);
		circleLayout.AddAttribute(AttribType::FLOAT_ATTRIB, 4);

		s_data->circleVAO = std::make_unique<VertexArray>(*s_data->circleVBO, *s_data->circleIBO, circleLayout);
	}

	void DebugRenderer::initializeLineRenderer() {
		s_data->lineShader = std::make_unique<Shader>(Shader::LoadFromFile("assets/douter/shaders/line.glsl"));

		s_data->lineVBO = std::make_unique<VertexBuffer>();
		s_data->lineVBO->SetData(nullptr, 2 * s_data->MAX_LINES, 2 * sizeof(float));

		VertexLayout lineLayout;
		lineLayout.AddAttribute(AttribType::FLOAT_ATTRIB, 2);
		s_data->lineVAO = std::make_unique<VertexArray>(*s_data->lineVBO, lineLayout);

		s_data->lineVertices.reserve(2 * s_data->MAX_LINES);
	}

	void DebugRenderer::flushCircleRenderer() {
		if (s_data->circleVertices.empty()) { return; }

		s_data->circleVBO->UpdateData(s_data->circleVertices.data(), static_cast<int>(s_data->circleVertices.size()), sizeof(CircleVertex));
		s_data->circleIBO->UpdateData(s_data->circleIndices.data(), static_cast<int>(s_data->circleIndices.size()));

		s_data->circleVAO->Bind();

		s_data->circleShader->Bind();
		s_data->circleShader->SetMat4("camera", s_data->camera->GetCameraMatrix());

		glDrawElements(GL_TRIANGLES, s_data->circleIndices.size(), GL_UNSIGNED_INT, NULL);

		s_data->circleVertices.clear();
		s_data->circleIndices.clear();
	}

	void DebugRenderer::flushLineRenderer() {
		if (s_data->lineVertices.empty()) {
			return;
		}

		s_data->lineVBO->UpdateData(
			s_data->lineVertices.data(),
			static_cast<int>(s_data->lineVertices.size()),
			sizeof(glm::vec2)
		);

		s_data->lineShader->SetMat4("camera", s_data->camera->GetCameraMatrix());

		s_data->lineVAO->Bind();
		s_data->lineShader->Bind();
		glDrawArrays(GL_LINES, 0, static_cast<int>(s_data->lineVertices.size()));

		s_data->lineVertices.clear();
	}

	void DebugRenderer::DrawLine(glm::vec2 startPos, glm::vec2 endPos) {
		if (s_data->lineVertices.size() >= s_data->MAX_LINES * 2) {
			std::println(stderr, "Renderer2D::DrawLine, cannot draw more lines then MAX_LINES!");
			return;
		}

		s_data->lineVertices.push_back(startPos);
		s_data->lineVertices.push_back(endPos);
	}

	void DebugRenderer::DrawCircle(glm::vec2 center, float radius) {
		glm::vec2 offsetX(radius, 0.0f);
		glm::vec2 offsetY(0.0f, radius);

		glm::vec4 color(1.0f, 0.0f, 0.0f, 1.0f);

		int baseIndex = static_cast<int>(s_data->circleVertices.size());

		s_data->circleVertices.push_back({ center - offsetX - offsetY, glm::vec2(-1.0f, -1.0f), color });
		s_data->circleVertices.push_back({ center + offsetX - offsetY, glm::vec2(1.0f, -1.0f), color });
		s_data->circleVertices.push_back({ center + offsetX + offsetY, glm::vec2(1.0f,  1.0f), color });
		s_data->circleVertices.push_back({ center - offsetX + offsetY, glm::vec2(-1.0f,  1.0f), color });
		
		s_data->circleIndices.push_back(baseIndex + 0);
		s_data->circleIndices.push_back(baseIndex + 1);
		s_data->circleIndices.push_back(baseIndex + 2);
		 
		s_data->circleIndices.push_back(baseIndex + 2);
		s_data->circleIndices.push_back(baseIndex + 3);
		s_data->circleIndices.push_back(baseIndex + 0);
	}

	void DebugRenderer::Begin(Camera& camera) {
		s_data->camera = &camera;
	}

	void DebugRenderer::End() {
		flushCircleRenderer();
		flushLineRenderer();
	}

}