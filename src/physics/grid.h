#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "ecs/entity.h"

namespace DG {

	struct GridCell {
		std::vector<DG::Entity> m_entitiesInCell;
	};

	class Grid {
	public:
		Grid(float worldWidth, float worldHeight, float cellSize);

		void DrawDebugLines();

		void Clear();
		void AddCellInhabitant(DG::Entity boid, glm::vec2 position);
		void GetCellInhabitants(glm::vec2 searchPosition, float visibilityArea, std::vector<DG::Entity>& ourInhabitants);
	private:
		float m_worldWidth, m_worldHeight;
		float m_cellWidth, m_cellHeight;
		int m_numColumns, m_numRows;

		std::vector<GridCell> m_gridCells;
	};
}
