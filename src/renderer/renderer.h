#pragma once

namespace DG {

	class Renderer {
	public:
		static void Clear(float r, float g, float b, float a);

		static void BeginImGui();
		static void EndImGui();
	private:
	};

}