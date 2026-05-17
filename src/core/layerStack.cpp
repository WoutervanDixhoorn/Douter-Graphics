#include "application.h"
#include "layerStack.h"

namespace DG {

	LayerStack::LayerStack() {
		m_layers.reserve(4);
	}

	void LayerStack::PushLayer(std::unique_ptr<Layer> layer) {
		layer->OnAttach();
		m_layers.push_back(std::move(layer));
	}

	void LayerStack::PopLayer() {
		if (m_layers.empty()) return;

		m_layers.back()->OnDettach();
		m_layers.pop_back();
	}

	LayerStack::iterator LayerStack::begin() {
		return m_layers.begin();
	}

	LayerStack::iterator LayerStack::end() {
		return m_layers.end();
	}
}