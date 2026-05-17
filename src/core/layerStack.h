#pragma once

#include <vector>

#include "Layer.h"

namespace DG {

	class LayerStack {
	public:
		LayerStack();

		void PushLayer(Layer& layer);
		void PopLayer();

		using iterator = std::vector<Layer*>::iterator;
		iterator begin();
		iterator end();

	private:
		std::vector<Layer*> m_layers;
	};

}