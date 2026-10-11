#pragma once

#include "window.h"
#include "layerStack.h"
#include "renderer/camera.h"

namespace DG {

	struct ApplicationSettings {
		uint32_t windowWidth = 1280;
		uint32_t windowHeight = 720;
		const char* windowTitle = "DG Application";
	};

	class Application {
	public:
		Application(const ApplicationSettings& settings);

		Application(Application const&) = delete;
		void operator=(Application const&) = delete;

		static Application& Get() { return *s_instance; }

		void Run();
		bool IsRunning();

	protected:
		void PushLayer(std::unique_ptr<Layer> layer);
		void PopLayer();

	private:
		void Update(float deltaTime);
		void OnEvent(IEvent& event);
		void Tick();

	private:
		inline static Application* s_instance = nullptr;

		ApplicationSettings m_applicationSettings;
		bool m_running = false;
		DG::Window* m_window;

		LayerStack m_layerStack;
	};

}