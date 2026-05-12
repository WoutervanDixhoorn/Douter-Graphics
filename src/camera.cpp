#include "camera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace DG {

	Camera Camera::Create2D(uint32_t windowWidth, uint32_t windowHeight, float worldHeight)
	{
        Camera cam;

        cam.m_aspectRatio = (float)windowWidth / (float)windowHeight;

        cam.m_worldHeight = worldHeight;
        cam.m_worldWidth = worldHeight * cam.m_aspectRatio;
        cam.m_projectionMatrix = glm::ortho(-cam.m_worldWidth, cam.m_worldWidth, -cam.m_worldHeight, cam.m_worldHeight, -1.0f, 1.0f);
        cam.m_viewMatrix = glm::mat4(1.0f);

        cam.m_cameraMatrix = cam.m_projectionMatrix * cam.m_viewMatrix;

        return cam;
	}

    glm::mat4 Camera::GetCameraMatrix()
    {
        m_cameraMatrix = m_projectionMatrix * m_viewMatrix;
        return m_cameraMatrix;
    }

    float Camera::GetHalfWorldHeight()
    {
        return m_worldHeight;
    }

    float Camera::GetHalfWorldWidth()
    {
        return m_worldWidth;
    }
}