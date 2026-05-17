#pragma once

#include <vector>
#include <memory>

#include "Layer.h"

namespace DG {

	class LayerStack {
	public:
		LayerStack();

		void PushLayer(std::unique_ptr<Layer> layer);
		void PopLayer();

		using iterator = std::vector<std::unique_ptr<Layer>>::iterator;
		iterator begin();
		iterator end();

	private:
		std::vector<std::unique_ptr<Layer>> m_layers;
	};

}