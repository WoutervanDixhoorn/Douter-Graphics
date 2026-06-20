#include "renderer.h"

#include <print>

#include "graphics_api.h"
#include "debugRenderer.h"
#include "camera.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace DG {

	Renderer2D::Renderer2DData* Renderer2D::m_rendererData = nullptr;

	void Renderer2D::Init() {
		m_rendererData = new Renderer2DData();

		initializeMeshRenderer();

		//TODO: Ik denk dat ik blending beter ergens anders kan veranderen
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		DebugRenderer::Init();
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

	void Renderer2D::BeginScene(DG::Camera& camera) {
		m_rendererData->camera = &camera;
		DebugRenderer::Begin(camera);
	}

	void Renderer2D::EndScene() {
		DebugRenderer::End();
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