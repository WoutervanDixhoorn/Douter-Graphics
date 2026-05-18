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

		intializeLineRenderer();
		initializeMeshRenderer();
	}

	void Renderer2D::intializeLineRenderer() {
		m_rendererData->lineShader = std::make_unique<Shader>(Shader::LoadFromFile("assets/douter/shaders/line.glsl"));

		m_rendererData->lineVBO = std::make_unique<VertexBuffer>();
		m_rendererData->lineVBO->SetData(nullptr, 2 * m_rendererData->MAX_LINES, 2 * sizeof(float));

		VertexLayout lineLayout;
		lineLayout.AddAttribute(AttribType::FLOAT_ATTRIB, 2);
		m_rendererData->lineVAO = std::make_unique<VertexArray>(*m_rendererData->lineVBO, lineLayout);

		m_rendererData->lineVertices.reserve(2 * m_rendererData->MAX_LINES);
	}

	void Renderer2D::initializeMeshRenderer() {
		m_rendererData->meshShader = std::make_unique<Shader>(Shader::LoadFromFile("assets/douter/shaders/mesh.glsl"));
	}

	void Renderer2D::Clear(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer2D::DrawMesh(Mesh* mesh, glm::mat4 transform) {
		m_rendererData->meshShader->Bind();
		m_rendererData->meshShader->SetMat4("transform", transform);
		m_rendererData->meshShader->SetMat4("camera", m_rendererData->camera->GetCameraMatrix());
 
		mesh->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	}

	void Renderer2D::DrawLine(glm::vec2 startPos, glm::vec2 endPos) {
		if (m_rendererData->lineVertices.size() >= m_rendererData->MAX_LINES * 2) {
			std::println(stderr, "Renderer2D::DrawLine, cannot draw more lines then MAX_LINES!");
			return;
		}

		m_rendererData->lineVertices.push_back(startPos);
		m_rendererData->lineVertices.push_back(endPos);
	}

	void Renderer2D::BeginScene(DG::Camera& camera) {
		m_rendererData->camera = &camera;
	}

	void Renderer2D::EndScene() {
		if (m_rendererData->lineVertices.empty()) return;

		m_rendererData->lineVBO->UpdateData(
			m_rendererData->lineVertices.data(),
			static_cast<int>(m_rendererData->lineVertices.size()),
			sizeof(glm::vec2)
		);

		m_rendererData->lineShader->SetMat4("camera", m_rendererData->camera->GetCameraMatrix());

		m_rendererData->lineVAO->Bind();
		m_rendererData->lineShader->Bind();
		glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(m_rendererData->lineVertices.size()));

		m_rendererData->lineVertices.clear();
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