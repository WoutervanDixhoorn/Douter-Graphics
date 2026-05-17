#pragma once

namespace DG {

	class Layer {
	public:
		virtual ~Layer() = default;

		virtual void OnAttach() = 0;
		virtual void OnDettach() = 0;
		virtual void OnUpdate(float deltaTime) = 0;
		virtual void OnGuiDraw() = 0;
	};

};
