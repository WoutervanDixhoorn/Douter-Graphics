#pragma once

#include "window.h"
#include "layerStack.h"
#include "Renderer/camera.h"

namespace DG {

	struct ApplicationSettings {
		float windowWidth = 1280;
		float windowHeight = 720;
		const char* windowTitle = "DG Application";
	};

	class Application {
	public:
		Application(const ApplicationSettings& settings);

		void Run();

	protected:
		void PushLayer(Layer& layer);
		void PopLayer();

	private:
		void Update(float deltaTime);

	private:
		ApplicationSettings m_applicationSettings;
		bool m_running = false;
		DG::Window* m_window;

		LayerStack m_layerStack;
	};

}