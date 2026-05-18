#pragma once
#include <string>

#include "glm/glm.hpp"

namespace DG {

	class Shader {
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader(Shader&& other) noexcept;
		Shader& operator=(Shader&& other) noexcept;

		static Shader LoadFromFile(const char* filePath);

		void Bind();

		void SetMat4(const char* uniformName, glm::mat4 matrix);
	private:
		Shader() = default;

		unsigned int compileShader(unsigned int type, const std::string& source);

		unsigned int m_shaderId;
	};

}