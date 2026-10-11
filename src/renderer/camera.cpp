#include "camera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace DG {

	Camera Camera::Create2D(const uint32_t windowWidth, const uint32_t windowHeight, float minX, float minY, float maxX, float maxY)
	{
        Camera cam;

		cam.m_aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
		cam.m_viewWidth = maxX - minX;
		cam.m_viewHeight = maxY - minY;

		const float expectedHeight = cam.m_viewWidth / cam.m_aspectRatio;
		const float expectedWidth = cam.m_viewHeight * cam.m_aspectRatio;

		if (expectedHeight > cam.m_viewHeight) {
			const float diffHeight = expectedHeight - cam.m_viewHeight;
			minY -= diffHeight / 2;
			maxY += diffHeight / 2;
		} else {
			const float diffWidth = expectedWidth - cam.m_viewWidth;
			minX -= diffWidth / 2;
			maxX += diffWidth / 2;
		}

		cam.m_minx = minX;
		cam.m_miny = minY;
		cam.m_maxx = maxX;
		cam.m_maxy = maxY;

        cam.m_projectionMatrix = glm::ortho(minX, maxX, maxY, minY, -1.0f, 1.0f);
        cam.m_viewMatrix = glm::mat4(1.0f);

        cam.m_cameraMatrix = cam.m_projectionMatrix * cam.m_viewMatrix;

        return cam;
	}

    Camera Camera::Create3D(const uint32_t windowWidth, const uint32_t windowHeight, const float fovDegrees, const float nearPlane, const float farPlane) {
	    Camera cam;

	    cam.m_aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

		const float fovRadians = glm::radians(fovDegrees);
		cam.m_viewHeight = static_cast<float>(windowHeight);
		cam.m_viewWidth = static_cast<float>(windowHeight) * cam.m_aspectRatio;
		cam.m_projectionMatrix = glm::perspective(fovRadians, cam.m_aspectRatio, nearPlane, farPlane);
		cam.m_viewMatrix = glm::mat4(1.0f);

		return cam;
	}

	void Camera::SetView(const glm::vec3 eye, const glm::vec3 target, const glm::vec3 up) {
		m_viewMatrix = glm::lookAt(eye, target, up);
		recalculateViewMatrix();
	}

	void Camera::SetPosition(const glm::vec3 position) {
		m_position = position;
		m_viewMatrix = glm::translate(glm::mat4(1.0f), -m_position);
		recalculateViewMatrix();
	}

	void Camera::SetZoom(const float zoomLevel) {
		m_zoomLevel = zoomLevel;

		const float centerX = (m_minx + m_maxx) / 2;
		const float centerY = (m_miny + m_maxy) / 2;
		const float halfW = (m_maxx - m_minx) / 2 / m_zoomLevel;
		const float halfH = (m_maxy - m_miny) / 2 / m_zoomLevel;

		m_projectionMatrix = glm::ortho(centerX - halfW, centerX + halfW, centerY + halfH, centerY - halfH, -1.0f, 1.0f);
		recalculateViewMatrix();
	}

	float Camera::GetZoomLevel() const {
		return m_zoomLevel;
	}

    glm::mat4 Camera::GetCameraMatrix() const{
        return m_cameraMatrix;
    }

    float Camera::GetViewHeight() const
    {
        return m_viewHeight;
    }

    float Camera::GetViewWidth() const
    {
        return m_viewWidth;
    }

	glm::vec3 Camera::GetPosition() const {
		return m_position;
	}

	void Camera::recalculateViewMatrix() {
		m_cameraMatrix = m_projectionMatrix * m_viewMatrix;
	}
}