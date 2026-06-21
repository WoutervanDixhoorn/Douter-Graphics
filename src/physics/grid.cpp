#include "grid.h"

#include <algorithm>
#include <print>

#include "renderer/debugRenderer.h"

namespace DG {

	Grid::Grid(float worldWidth, float worldHeight, float cellSize)
		: m_worldWidth(worldWidth), m_worldHeight(worldHeight)
	{
		m_numColumns = std::ceil(m_worldWidth / cellSize);
		m_numRows = std::ceil(m_worldHeight / cellSize);

		m_cellWidth = cellSize;
		m_cellHeight = cellSize;

		size_t actualNumCells = m_numColumns * m_numRows;
		m_gridCells.resize(actualNumCells);
	}

	void Grid::DrawDebugLines() {
		for (float x = 0; x < m_worldWidth; x += m_cellWidth) {
			DG::DebugRenderer::DrawLine({ x, 0.0f }, {x, m_worldHeight});
		}

		for (float y = 0; y < m_worldHeight; y += m_cellHeight) {
			DG::DebugRenderer::DrawLine({ 0.0f, y }, { m_worldWidth, y });
		}
	}

	void Grid::Clear() {
		for (auto& cell : m_gridCells) {
			cell.m_entitiesInCell.clear();
		}
	}

	void Grid::AddCellInhabitant(DG::Entity entity, glm::vec2 position) {
		int cellX = static_cast<int>(position.x / m_cellWidth);
		int cellY = static_cast<int>(position.y / m_cellHeight);

		cellX = std::clamp(cellX, 0, m_numColumns - 1);
		cellY = std::clamp(cellY, 0, m_numRows - 1);

		int cellIndex = cellX + (cellY * m_numColumns);

		m_gridCells[cellIndex].m_entitiesInCell.push_back(entity);
	}

	void Grid::GetCellInhabitants(glm::vec2 searchPosition, float visibilityArea, std::vector<DG::Entity>& ourInhabitants) {
		ourInhabitants.clear();

		glm::vec2 pos = searchPosition;

		int minCellX = static_cast<int>((pos.x - visibilityArea) / m_cellWidth);
		int maxCellX = static_cast<int>((pos.x + visibilityArea) / m_cellWidth);
		int minCellY = static_cast<int>((pos.y - visibilityArea) / m_cellHeight);
		int maxCellY = static_cast<int>((pos.y + visibilityArea) / m_cellHeight);

		minCellX = std::clamp(minCellX, 0, m_numColumns - 1);
		maxCellX = std::clamp(maxCellX, 0, m_numColumns - 1);
		minCellY = std::clamp(minCellY, 0, m_numRows - 1);
		maxCellY = std::clamp(maxCellY, 0, m_numRows - 1);

		for (int x = minCellX; x <= maxCellX; ++x) {
			for (int y = minCellY; y <= maxCellY; ++y) {
				const auto& cell = m_gridCells[x + (y * m_numColumns)];

				ourInhabitants.insert(
					ourInhabitants.end(),
					cell.m_entitiesInCell.begin(),
					cell.m_entitiesInCell.end()
				);
			}
		}
	}

}