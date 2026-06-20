#pragma once

#include <vector>
#include <cassert>

#include "entity.h"

namespace DG {

	const Entity NULL_ENTITY = 0xFFFFFFFF;
	
	class ISparseSet {
	public:
		virtual ~ISparseSet() = default;
	};

	template <typename T>
	class SparseSet : public ISparseSet {
	public:
		SparseSet() = default;

		void Insert(Entity entity, T component)
		{
			if (m_sparse.size() <= entity) {
				m_sparse.resize(entity + 1, NULL_ENTITY);
			}
			
			m_denseEntities.push_back(entity);
			m_denseComponents.push_back(component);

			m_sparse[entity] = m_denseComponents.size() - 1;
		}

		T& Get(Entity entity)
		{
			assert(Has(entity) && "Entity does not have this component!");
			
			return m_denseComponents[m_sparse[entity]];
		}

		void Remove(Entity entity)
		{
			if (!Has(entity)) return;

			size_t idx = m_sparse[entity];
			Entity lastEntity = m_denseEntities.back();

			m_denseEntities[idx] = lastEntity;
			m_denseComponents[idx] = m_denseComponents.back();
		
			m_sparse[lastEntity] = idx;
			m_sparse[entity] = NULL_ENTITY;

			m_denseEntities.pop_back();
			m_denseComponents.pop_back();
		}

		bool Has(Entity entity)
		{
			return entity < m_sparse.size() && m_sparse[entity] != NULL_ENTITY;
		}

	private:
		std::vector<size_t> m_sparse;
		std::vector<Entity> m_denseEntities;
		std::vector<T> m_denseComponents;

	};

}	