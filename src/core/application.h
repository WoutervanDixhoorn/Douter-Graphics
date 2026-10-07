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

		void Run();
		bool IsRunning();

	protected:
		void PushLayer(std::unique_ptr<Layer> layer);
		void PopLayer();

	private:
		void Update(float deltaTime);
		void Tick();

	private:
		ApplicationSettings m_applicationSettings;
		bool m_running = false;
		DG::Window* m_window;

		LayerStack m_layerStack;
	};

}