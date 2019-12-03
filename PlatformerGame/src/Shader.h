#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

class Shader
{
// public functions
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath = "");
	~Shader();

	void Create();

	void Bind() const;
	void Unbind() const;

	void SetUniformBool(const std::string& name, GLboolean val);
	void SetUniformi(const std::string& name, GLint val);
	void SetUniform1f(const std::string& name, GLfloat val);

	void SetUniform2f(const std::string& name, GLfloat val0, GLfloat val1);
	void SetUniform2f(const std::string& name, const glm::vec2& val);

	void SetUniform3f(const std::string& name, GLfloat val0, GLfloat val1, GLfloat val2);
	void SetUniform3f(const std::string& name, const glm::vec3& val);

	void SetUniform4f(const std::string& name, GLfloat val0, GLfloat val1, GLfloat val2, GLfloat val3);
	void SetUniform4f(const std::string& name, const glm::vec4& val);

	void SetUniformMat4(const std::string& name, const void* matrix);

// public variables
public:

// private functions
private:
	GLuint Compile(GLint shaderType);
	std::string ReadFromFile(const std::string& filePath);
	GLint GetUniformLocation(const std::string& name);

// private variables
private:
	GLuint ID;
	std::unordered_map<GLuint, std::string> shaderSourcePaths{};
	std::unordered_map<std::string, GLint> uniformLocations{};
};

