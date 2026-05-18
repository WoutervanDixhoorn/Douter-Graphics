#include "renderer.h"

#include <print>

#include "graphics_api.h"
#include "camera.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace DG {

	Renderer2D::Renderer2DData* Renderer2D::m_rendererData = nullptr;

	void Renderer2D::Init() {
		m_rendererData = new Renderer2DData();

		m_rendererData->m_lineShader = std::make_unique<Shader>(Shader::LoadFromFile("assets/douter/shaders/line.glsl"));

		m_rendererData->m_lineVBO = std::make_unique<VertexBuffer>();
		m_rendererData->m_lineVBO->SetData(nullptr, 2 * m_rendererData->MAX_LINES, 2 * sizeof(float));

		VertexLayout lineLayout;
		lineLayout.AddAttribute(AttribType::FLOAT_ATTRIB, 2);
		m_rendererData->m_lineVAO = std::make_unique<VertexArray>(*m_rendererData->m_lineVBO, lineLayout);
	
		m_rendererData->m_lineVertices.reserve(2 * m_rendererData->MAX_LINES);
	}

	void Renderer2D::Clear(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer2D::DrawLine(glm::vec2 startPos, glm::vec2 endPos) {
		if (m_rendererData->m_lineVertices.size() >= m_rendererData->MAX_LINES * 2) {
			std::println(stderr, "Renderer2D::DrawLine, cannot draw more lines then MAX_LINES!");
			return;
		}

		m_rendererData->m_lineVertices.push_back(startPos);
		m_rendererData->m_lineVertices.push_back(endPos);
	}

	void Renderer2D::BeginScene(DG::Camera& camera) {
		m_rendererData->m_camera = &camera;
	}

	void Renderer2D::EndScene() {
		if (m_rendererData->m_lineVertices.empty()) return;

		m_rendererData->m_lineVBO->UpdateData(
			m_rendererData->m_lineVertices.data(),
			static_cast<int>(m_rendererData->m_lineVertices.size()),
			sizeof(glm::vec2)
		);

		m_rendererData->m_lineShader->SetMat4("camera", m_rendererData->m_camera->GetCameraMatrix());

		m_rendererData->m_lineVAO->Bind();
		m_rendererData->m_lineShader->Bind();
		glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(m_rendererData->m_lineVertices.size()));

		m_rendererData->m_lineVertices.clear();
	}

	void Renderer2D::BeginImGui() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Renderer2D::EndImGui() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}


}