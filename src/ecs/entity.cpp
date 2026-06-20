#include "entity.h"

namespace DG {

	EntityRegistry::EntityRegistry() {
		m_freedEntities = std::vector<Entity>();
		m_freedEntities.reserve(1000); // Lets start with 1000?
	}

	Entity EntityRegistry::CreateEntity() {
		if (!m_freedEntities.empty()) {
			Entity newEntity = m_freedEntities.back();
			m_freedEntities.pop_back();
			return newEntity;
		}

		return m_nextEntity++;
	}

	void EntityRegistry::DestroyEntity(Entity entity)
	{
		m_freedEntities.push_back(entity);
	}
}