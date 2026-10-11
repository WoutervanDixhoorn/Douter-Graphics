#pragma once

#include "glm/glm.hpp"

namespace DG {

	//TODO: Maybe create a ICamera interface and have Camera2D and Camera3D so we can only expose the correct methods so usage becomes harder to do wrong!
	class Camera {
	public:
		static Camera Create2D(const uint32_t windowWidth, const uint32_t windowHeight, float minX, float minY, float maxX, float maxY);
		static Camera Create3D(uint32_t windowWidth, uint32_t windowHeight, float fovDegrees, float nearPlane, float farPlane);

		//NOTE: 3D controls
		void SetView(glm::vec3 eye, glm::vec3 target, glm::vec3 up);

		//NOTE: 2D controls
		void SetPosition(glm::vec3 position);
		void SetZoom(float zoomLevel);

		[[nodiscard]] glm::mat4 GetCameraMatrix() const;
		[[nodiscard]] float GetViewHeight() const;
		[[nodiscard]] float GetViewWidth() const;
		[[nodiscard]] float GetZoomLevel() const;
		[[nodiscard]] glm::vec3 GetPosition() const;

	private:
		void recalculateViewMatrix();

	private:
		float m_aspectRatio = 0;
		float m_viewHeight = 0, m_viewWidth = 0;
		float m_minx = 0, m_miny = 0, m_maxx = 0, m_maxy = 0;
		float m_zoomLevel = 0;

		glm::vec3 m_position = glm::vec3(0.0f);

		glm::mat4 m_cameraMatrix{};
		glm::mat4 m_projectionMatrix{};
		glm::mat4 m_viewMatrix{};
	};

}