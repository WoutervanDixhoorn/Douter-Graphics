#include "application.h"

#include "renderer/renderer.h"
#include "core/time.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

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

#ifdef __EMSCRIPTEN__
		emscripten_set_main_loop_arg([](void* userData) {
			Application* app = static_cast<Application*>(userData);
			app->Tick();
		}, this, 0, 1);
#else
		while (m_running) {
			Tick();
		}
#endif
	}

	bool Application::IsRunning() {
		return m_running;
	}

	void Application::Update(float deltaTime) {
		for (auto& l : m_layerStack) {
			l->OnUpdate(deltaTime);
		}

		DG::Renderer2D::BeginImGui();
		for (auto& l : m_layerStack) {
			l->OnGuiDraw();
		}
		DG::Renderer2D::EndImGui();
	}

	void Application::Tick() {
		Time::Update();

		Update(Time::GetDeltaTime());

		m_window->PollAndSwap();
		if (m_window->ShouldClose()) {
			m_running = false;
		}
	}

	void Application::PushLayer(std::unique_ptr<Layer> layer) {
		m_layerStack.PushLayer(std::move(layer));
	}

	void Application::PopLayer() {
		m_layerStack.PopLayer();
	}

}