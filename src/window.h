#pragma once

struct GLFWwindow;

namespace DG {

	class Window {
	public:
		Window(int width, int height, const char* title);
		~Window();

		bool ShouldClose();
		void PollAndSwap();
		void UpdateDeltaTime();

		float GetDeltaTime();

	private:
		bool initializeWindow();

		int m_width, m_height;
		const char* m_title;

		double m_lastFrameTime = 0.0;
		float m_deltaTime = 0.0f;

		GLFWwindow* m_window;
	};

}