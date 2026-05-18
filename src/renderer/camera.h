#pragma once

#include "glm/glm.hpp"

namespace DG {

	class Camera {
	public:
		static Camera Create2D(uint32_t windowWidth, uint32_t windowHeight, float worldHeight);

		glm::mat4 GetCameraMatrix();
	
		float GetViewHeight();
		float GetViewWidth();
	private:
		float m_aspectRatio;
		float m_viewHeight, m_viewWidth;
		glm::mat4 m_cameraMatrix;
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
	};

}