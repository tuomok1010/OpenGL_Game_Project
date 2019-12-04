#include "Shader.h"

#include <iostream>
#include <fstream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
{
	shaderSourcePaths[GL_VERTEX_SHADER] = vertexPath;
	shaderSourcePaths[GL_FRAGMENT_SHADER] = fragmentPath;
	shaderSourcePaths[GL_GEOMETRY_SHADER] = geometryPath;

	Create();
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::Create()
{
	ID = glCreateProgram();

	GLuint vShader{}, fShader{}, gShader{};

	vShader = Compile(GL_VERTEX_SHADER);
	fShader = Compile(GL_FRAGMENT_SHADER);

	if (!shaderSourcePaths[GL_GEOMETRY_SHADER].empty())
	{
		gShader = Compile(GL_GEOMETRY_SHADER);
		glAttachShader(ID, gShader);
	}

	glAttachShader(ID, vShader);
	glAttachShader(ID, fShader);
	glLinkProgram(ID);
	glValidateProgram(ID);

	int result{};
	char log[1024]{};

	glGetProgramiv(ID, GL_LINK_STATUS, &result);
	if (result != GL_TRUE)
	{
		glGetProgramInfoLog(ID, 1024, nullptr, log);
		std::cerr << "Error linking shader program:\n" << log << std::endl;
	}

	glGetProgramiv(ID, GL_VALIDATE_STATUS, &result);
	if (result != GL_TRUE)
	{
		glGetProgramInfoLog(ID, 1024, nullptr, log);
		std::cerr << "Error validating shader program:\n" << log << std::endl;
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	if(!shaderSourcePaths[GL_GEOMETRY_SHADER].empty())
		glDeleteShader(gShader);
}

GLuint Shader::Compile(GLenum shaderType)
{
	GLuint shaderID = glCreateShader(shaderType);

	std::string shaderCodeString = ReadFromFile(shaderSourcePaths[shaderType]);
	const char* shaderCode = shaderCodeString.c_str();

	glShaderSource(shaderID, 1, &shaderCode, nullptr);
	glCompileShader(shaderID);

	int result{};
	char log[1024]{};
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE)
	{
		glGetShaderInfoLog(shaderID, 1024, nullptr, log);
		if (shaderType == GL_VERTEX_SHADER)
			std::cerr << "Error compiling vertex shader:\n" << log << std::endl;
		else if(shaderType == GL_FRAGMENT_SHADER)
			std::cerr << "Error compiling fragment shader:\n" << log << std::endl;
		else if(shaderType == GL_GEOMETRY_SHADER)
			std::cerr << "Error compiling geometry shader:\n" << log << std::endl;

		return -1;
	}
	return shaderID;
}

std::string Shader::ReadFromFile(const std::string& filePath)
{
	std::fstream stream;
	std::string shaderCode{};

	stream.open(filePath, stream.in);
	if (!stream.is_open())
	{
		std::cerr << "Error opening file " << filePath << std::endl;
		return "";
	}

	stream.seekp(0);
	while (!stream.eof())
	{
		std::string line{};
		std::getline(stream, line);
		shaderCode += (line + '\n');
	}
	stream.close();
	return shaderCode;
}

GLint Shader::GetUniformLocation(const std::string& name)
{
	if (uniformLocations.find(name) != uniformLocations.end())
		return uniformLocations[name];

	GLint loc = glGetUniformLocation(ID, name.c_str());

	if (loc == -1)
		std::cerr << "Uniform " << name << " not found" << std::endl;

	uniformLocations[name] = loc;
	return loc;
}

void Shader::Bind() const
{
	glUseProgram(ID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniformBool(const std::string& name, GLboolean val)
{
	glUniform1i(GetUniformLocation(name), val);
}

void Shader::SetUniformi(const std::string& name, GLint val)
{
	glUniform1i(GetUniformLocation(name), val);
}

void Shader::SetUniform1f(const std::string& name, GLfloat val)
{
	glUniform1f(GetUniformLocation(name), val);
}

void Shader::SetUniform2f(const std::string& name, GLfloat val0, GLfloat val1)
{
	glUniform2f(GetUniformLocation(name), val0, val1);
}

void Shader::SetUniform2f(const std::string& name, const glm::vec2& val)
{
	glUniform2f(GetUniformLocation(name), val.x, val.y);
}

void Shader::SetUniform3f(const std::string& name, GLfloat val0, GLfloat val1, GLfloat val2)
{
	glUniform3f(GetUniformLocation(name), val0, val1, val2);
}

void Shader::SetUniform3f(const std::string& name, const glm::vec3& val)
{
	glUniform3f(GetUniformLocation(name), val.x, val.y, val.z);
}

void Shader::SetUniform4f(const std::string& name, GLfloat val0, GLfloat val1, GLfloat val2, GLfloat val3)
{
	glUniform4f(GetUniformLocation(name), val0, val1, val2, val3);
}

void Shader::SetUniform4f(const std::string& name, const glm::vec4& val)
{
	glUniform4f(GetUniformLocation(name), val.x, val.y, val.z, val.w);
}

void Shader::SetUniformMat4(const std::string& name, const void* matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, (GLfloat*)matrix);
}
