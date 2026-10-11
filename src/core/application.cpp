#include "application.h"

#include "renderer/renderer.h"
#include "core/time.h"

#include "renderer/graphics_api.h"

#include <print>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

namespace DG {

	Application::Application(const ApplicationSettings& settings)
		: m_running(false), m_applicationSettings(settings), m_window(nullptr)
	{
		s_instance = this;

		m_window = new DG::Window(
			m_applicationSettings.windowWidth, 
			m_applicationSettings.windowHeight, 
			m_applicationSettings.windowTitle
		);

		m_window->SetEventCallback([&](IEvent& event) {
			OnEvent(event);
		});
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

	void Application::OnEvent(IEvent& event) {
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowResizeEvent>([](WindowResizeEvent& event) {
			//TODO: Create 'RenderCommand' structure. so we can call 'RenderCommand::SetViewPort(x, y, width, height)' etc. Same for commands in our renderer
			glViewport(0, 0, event.GetWidth(), event.GetHeight());
			return false;
		});

		for (auto& l : m_layerStack) {
			l->OnEvent(event);
			if (event.Handled) break;
		}

	}

	void Application::Tick() {
		Time::Update();

		m_window->PollEvents();
		Update(Time::GetDeltaTime());
		m_window->SwapBuffers();

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