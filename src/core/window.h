#pragma once

struct GLFWwindow;

namespace DG {

	class Window {
	public:
		Window(int width, int height, const char* title);
		~Window();

		bool ShouldClose();
		void PollAndSwap();

	private:
		bool initializeWindow();
		bool initializeImGui();

		int m_width, m_height;
		const char* m_title;

		GLFWwindow* m_window;
	};

}