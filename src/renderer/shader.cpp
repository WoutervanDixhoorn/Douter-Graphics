#include "shader.h"

#include <print>
#include <fstream>
#include <sstream>
#include "glad/glad.h"

#include "glm/gtc/type_ptr.hpp"

namespace DG {

	Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
	{
        m_shaderId = glCreateProgram();

        unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexSource);
        unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

        glAttachShader(m_shaderId, vs);
        glAttachShader(m_shaderId, fs);
        glLinkProgram(m_shaderId);
        glValidateProgram(m_shaderId);

        glDeleteShader(vs);
        glDeleteShader(fs);
	}

    Shader Shader::LoadFromFile(const char* filePath)
    {
        std::fstream shaderFile;
        shaderFile.open(filePath);

        if (shaderFile.fail()) 
        {
            std::println(stderr, "Opening file {} not found!", filePath);
            return Shader();
        }

        //NOTE: 0 - vertex, 1 - fragment
        uint8_t readMode = 0;
        std::stringstream shaderSource[2];
        std::string sourceLine;
        while(std::getline(shaderFile, sourceLine))
        {   
            if (sourceLine.find("#vertex") != std::string::npos) {
                readMode = 0;
                continue;
            } else 
            if (sourceLine.find("#fragment") != std::string::npos) {
                readMode = 1;
                continue;
            }

            shaderSource[readMode] << sourceLine << '\n';
        }

        shaderFile.close();

        std::println(stdout, "Loaded shaders....\n");
        std::println(stdout, "Vertex:\n{}", shaderSource[0].str());
        std::println(stdout, "Fragment:\n{}", shaderSource[1].str());

        return Shader(shaderSource[0].str(), shaderSource[1].str());
    }

	void Shader::Bind()
	{
        glUseProgram(m_shaderId);
	}

	void Shader::SetMat4(const char* uniformName, glm::mat4 matrix)
	{
        Bind();
        unsigned int uniLoc = glGetUniformLocation(m_shaderId, uniformName);
        glUniformMatrix4fv(uniLoc, 1, GL_FALSE, glm::value_ptr(matrix));
	}

    unsigned int Shader::compileShader(unsigned int type, const std::string& source)
    {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        //TODO: Error handling!
        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> message(length);
            glGetShaderInfoLog(id, length, &length, message.data());
            std::println(stderr, "Shader failed compiling!");
            std::println(stderr, "{}", message);

            glDeleteShader(id);
        }

        return id;
    }
}