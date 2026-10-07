#include "camera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace DG {

	Camera Camera::Create2D(const uint32_t windowWidth, const uint32_t windowHeight, const float viewHeight)
	{
        Camera cam;

        cam.m_aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

        cam.m_viewHeight = viewHeight;
        cam.m_viewWidth = viewHeight * cam.m_aspectRatio;
        cam.m_projectionMatrix = glm::ortho(0.0f, cam.m_viewWidth, cam.m_viewHeight, 0.0f, -1.0f, 1.0f);
        cam.m_viewMatrix = glm::mat4(1.0f);

        cam.m_cameraMatrix = cam.m_projectionMatrix * cam.m_viewMatrix;

        return cam;
	}

    glm::mat4 Camera::GetCameraMatrix()
    {
        m_cameraMatrix = m_projectionMatrix * m_viewMatrix;
        return m_cameraMatrix;
    }

    float Camera::GetViewHeight()
    {
        return m_viewHeight;
    }

    float Camera::GetViewWidth()
    {
        return m_viewWidth;
    }
}