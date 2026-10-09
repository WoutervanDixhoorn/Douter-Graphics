#include "debugRenderer.h"

#include <print>

#include "graphics_api.h"
#include "vertexLayout.h"

//TODO: Make the renderer limits/settings actually variable so that they are tweakable if we want

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
		s_data->circleVBO->SetData(nullptr, static_cast<int>(s_data->MAX_CIRCLES * 4), sizeof(CircleVertex));

		s_data->circleIndices.reserve(s_data->MAX_CIRCLES * 6);
		s_data->circleIBO = std::make_unique<IndexBuffer>();
		s_data->circleIBO->SetData(nullptr, static_cast<int>(s_data->MAX_CIRCLES * 6));

		VertexLayout circleLayout;
		circleLayout.AddAttribute(AttribType::FLOAT_ATTRIB, 3); //NOTE: WorldPos
		circleLayout.AddAttribute(AttribType::FLOAT_ATTRIB, 2); //NOTE: LocalPos
		circleLayout.AddAttribute(AttribType::FLOAT_ATTRIB, 4); //NOTE: Color
		circleLayout.AddAttribute(AttribType::FLOAT_ATTRIB, 1); //NOTE: fillLevel

		s_data->circleVAO = std::make_unique<VertexArray>(*s_data->circleVBO, *s_data->circleIBO, circleLayout);
	}

	void DebugRenderer::initializeLineRenderer() {
		s_data->lineShader = std::make_unique<Shader>(Shader::LoadFromFile("assets/douter/shaders/line.glsl"));

		s_data->lineVertices.reserve(s_data->MAX_LINES * 2);
		s_data->lineVBO = std::make_unique<VertexBuffer>();
		s_data->lineVBO->SetData(nullptr, static_cast<int>(s_data->MAX_LINES * 2), 2 * sizeof(LineVertex));

		VertexLayout lineLayout;
		lineLayout.AddAttribute(AttribType::FLOAT_ATTRIB, 3); //NOTE: Position
		lineLayout.AddAttribute(AttribType::FLOAT_ATTRIB, 4); //NOTE: Color

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

		glDrawElements(GL_TRIANGLES, static_cast<int>(s_data->circleIndices.size()), GL_UNSIGNED_INT, nullptr);

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
			sizeof(LineVertex)
		);

		s_data->lineVAO->Bind();

		s_data->lineShader->Bind();
		s_data->lineShader->SetMat4("camera", s_data->camera->GetCameraMatrix());

		glDrawArrays(GL_LINES, 0, static_cast<int>(s_data->lineVertices.size()));

		s_data->lineVertices.clear();
	}

	void DebugRenderer::DrawLine(const glm::vec3 startPos, const glm::vec3 endPos, const glm::vec4 color) {
		if (s_data->lineVertices.size() >= s_data->MAX_LINES * 2) {
			std::println(stderr, "Renderer2D::DrawLine, cannot draw more lines then MAX_LINES!");
			return;
		}

		s_data->lineVertices.push_back({.pos = startPos, .color = color});
		s_data->lineVertices.push_back({.pos = endPos, .color = color});
	}

	void DebugRenderer::DrawLine(const glm::vec2 startPos, const glm::vec2 endPos) {
		DrawLine(startPos, endPos, {1.0f, 0.0f, 0.0f, 1.0f});
	}

	void DebugRenderer::DrawLine(const glm::vec2 startPos, const glm::vec2 endPos, const glm::vec4 color) {
		DrawLine({startPos.x, startPos.y, 0.0f}, {endPos.x, endPos.y, 0.0f}, color);
	}

	void DebugRenderer::DrawCircle(const glm::vec3 center, const float radius, const glm::vec4 color, const float fillLevel) {
		if (s_data->circleVertices.size() >= s_data->MAX_CIRCLES * 4) {
			std::println(stderr, "DebugRenderer::DrawCircle, cannot draw more circles than MAX_CIRCLES!");
			return;
		}

		const glm::vec3 offsetX(radius, 0.0f, 0.0f);
		const glm::vec3 offsetY(0.0f, radius, 0.0f);

		const int baseIndex = static_cast<int>(s_data->circleVertices.size());

		s_data->circleVertices.push_back({ .worldPos = center - offsetX - offsetY, .localPos = glm::vec2(-1.0f, -1.0f), .color = color, .fillLevel = fillLevel });
		s_data->circleVertices.push_back({ .worldPos = center + offsetX - offsetY, .localPos = glm::vec2(1.0f, -1.0f), .color = color, .fillLevel = fillLevel });
		s_data->circleVertices.push_back({ .worldPos = center + offsetX + offsetY, .localPos = glm::vec2(1.0f,  1.0f), .color = color, .fillLevel = fillLevel });
		s_data->circleVertices.push_back({ .worldPos = center - offsetX + offsetY, .localPos = glm::vec2(-1.0f,  1.0f), .color = color, .fillLevel = fillLevel });
		
		s_data->circleIndices.push_back(baseIndex + 0);
		s_data->circleIndices.push_back(baseIndex + 1);
		s_data->circleIndices.push_back(baseIndex + 2);
		 
		s_data->circleIndices.push_back(baseIndex + 2);
		s_data->circleIndices.push_back(baseIndex + 3);
		s_data->circleIndices.push_back(baseIndex + 0);
	}

	void DebugRenderer::DrawCircle(const glm::vec2 center, const float radius, const float fillLevel) {
		DrawCircle({center, 1.0f}, radius, {1.0f, 0.0f, 0.0f, 1.0f}, fillLevel);
	}

	void DebugRenderer::DrawCircle(const glm::vec2 center, const float radius, const glm::vec4 color) {
		DrawCircle({center, 0.0f}, radius, color, 0.05f);
	}

	void DebugRenderer::DrawFilledCircle(const glm::vec2 center, const float radius, const glm::vec4 color) {
		DrawCircle({center, 0.0f}, radius, color, 1.0f);
	}

	void DebugRenderer::Begin(Camera& camera) {
		s_data->camera = &camera;
	}

	void DebugRenderer::End() {
		flushCircleRenderer();
		flushLineRenderer();
	}

}