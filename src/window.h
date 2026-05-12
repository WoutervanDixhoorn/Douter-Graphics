#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace DG {

	class Window {
	public:
		Window(int width, int height, const char* title);
		~Window();

		bool ShouldClose();
		 void PollAndSwap();

	private:
		bool initializeWindow();

		int m_width, m_height;
		const char* m_title;

		GLFWwindow* m_window;
	};

}