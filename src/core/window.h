#pragma once

#include <functional>

#include "events/event.h"
#include "renderer/graphicsContext.h"

struct GLFWwindow;

namespace DG {

	struct WindowData {
		std::function<void(IEvent&)> eventCallback;
	};

	class Window {
	public:
		Window(int width, int height, const char* title);
		~Window();

		void SetEventCallback(std::function<void(IEvent&)> callback);

		bool ShouldClose();

		void PollEvents();
		void SwapBuffers();

	private:
		bool initializeWindow();
		bool initializeCallbacks();
		bool initializeImGui();

		std::unique_ptr<GraphicsContext> m_context;

		WindowData m_data;

		int m_width, m_height;
		const char* m_title;

		GLFWwindow* m_window;
	};

}