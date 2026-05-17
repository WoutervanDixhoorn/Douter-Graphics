#include "application.h"
#include "layerStack.h"

namespace DG {

	LayerStack::LayerStack() {
		m_layers.reserve(4);
	}

	void LayerStack::PushLayer(Layer& layer) {
		m_layers.push_back(&layer);
		layer.OnAttach();
	}

	void LayerStack::PopLayer() {
		Layer* layer = m_layers.back();
		layer->OnDettach();
		m_layers.pop_back();		
	}

	iterator LayerStack::begin() {
		return m_layers.begin();
	}

	iterator LayerStack::end() {
		return m_layers.end();
	}
}