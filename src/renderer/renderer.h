#pragma once

#include <memory>
#include <vector>

#include "vertexArray.h"
#include "buffers.h"
#include "mesh.h"
#include "shader.h"
#include "camera.h"

#include "glm/glm.hpp"

namespace DG {

	class Renderer2D {
	public:
		static void Init();

		static void Clear(float r, float g, float b, float a);

		static void DrawMesh(Mesh* mesh, glm::mat4 transform);

		static void BeginScene(DG::Camera& camera);
		static void EndScene();

		static void BeginImGui();
		static void EndImGui();

	private:
		static void initializeMeshRenderer();

	private:
		struct Renderer2DData {
			std::unique_ptr<Shader> meshShader;

			Camera* camera;
		};

		static struct Renderer2DData* m_rendererData;
	};

}