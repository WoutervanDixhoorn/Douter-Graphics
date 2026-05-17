#include "application.h"

#include "renderer/renderer.h"

namespace DG {

	Application::Application(const ApplicationSettings& settings)
		: m_running(false), m_applicationSettings(settings), m_window(nullptr)
	{
		m_window = new DG::Window(
			m_applicationSettings.windowWidth, 
			m_applicationSettings.windowHeight, 
			m_applicationSettings.windowTitle
		);
	}

	void Application::Run() {
		m_running = true;

		while (m_running) {
			m_window->UpdateDeltaTime();

			Update(m_window->GetDeltaTime());

			m_window->PollAndSwap();
			if (m_window->ShouldClose()) {
				m_running = false;
			}
		}
	}

	void Application::Update(float deltaTime) {
		for (auto& l : m_layerStack) {
			l->OnUpdate(deltaTime);
		}

		DG::Renderer::BeginImGui();
		for (auto& l : m_layerStack) {
			l->OnGuiDraw();
		}
		DG::Renderer::EndImGui();
	}

	void Application::PushLayer(std::unique_ptr<Layer> layer) {
		m_layerStack.PushLayer(std::move(layer));
	}

	void Application::PopLayer() {
		m_layerStack.PopLayer();
	}

}