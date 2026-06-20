#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "componentTypeManager.h"
#include "sparseSet.h"

namespace DG {
	using Entity = uint32_t;

	class EntityRegistry {
	public:
		EntityRegistry();

		Entity CreateEntity();
		void DestroyEntity(Entity entity);

		template <typename T>
		void Register(Entity entity, T component)
		{
			uint32_t componentId = ComponentTypeManager::GetId<T>();

			if (componentId >= m_componentSets.size()) {
				m_componentSets.resize(componentId + 1);
			}

			if (!m_componentSets[componentId]) {
				m_componentSets[componentId] = std::make_unique<SparseSet<T>>();
			}

			SparseSet<T>* componentSet = static_cast<SparseSet<T>*>(m_componentSets[componentId].get());
			componentSet->Insert(entity, component);
		}

		template <typename T>
		T& Get(Entity entity)
		{
			uint32_t componentId = ComponentTypeManager::GetId<T>();

			assert(componentId < m_componentSets.size() && "Entity does not have this component!");
			assert(m_componentSets[componentId] != nullptr && "Entity does not have this component!");

			SparseSet<T>* componentSet = static_cast<SparseSet<T>*>(m_componentSets[componentId].get());
			return componentSet->Get(entity, component);
		}

		template <typename T>
		void Remove(Entity entity)
		{
			uint32_t componentId = ComponentTypeManager::GetId<T>();

			if (componentId >= m_componentSets.size() || m_componentSets[componentId] == nullptr) {
				return;
			}

			SparseSet<T>* componentSet = static_cast<SparseSet<T>*>(m_componentSets[componentId].get());
			componentSet->Remove(entity);
		}

	private:
		Entity m_nextEntity = 0;
		std::vector<Entity> m_freedEntities;
		std::vector<std::unique_ptr<ISparseSet>> m_componentSets;
	};

}