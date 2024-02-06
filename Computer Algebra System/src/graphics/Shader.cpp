#include "Shader.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../maths/Matrix4x4.h"
#include "../maths/Matrix3x3.h"
#include "../maths/Matrix2x2.h"

Shader::Shader(const std::string& filepath, unsigned int shaderType)
{
	std::ifstream shaderFile;
	shaderFile.open(filepath);

	if (!shaderFile.is_open()) {
		std::cout << "File not found" << std::endl;
	}
	std::stringstream stream;
	stream << shaderFile.rdbuf();
	std::string shaderSrc = stream.str();
	const char* cStr = shaderSrc.c_str();

	m_ID = glCreateShader(shaderType);
	glShaderSource(m_ID, 1, &cStr, nullptr);
	glCompileShader(m_ID);
	int success;
	glGetShaderiv(m_ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(m_ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

ShaderProgram::ShaderProgram()
{
	m_ID = glCreateProgram();
}

void ShaderProgram::linkShader(const Shader& shader)
{
	glAttachShader(m_ID, shader.m_ID);
}

void ShaderProgram::compile()
{
	glLinkProgram(m_ID);

	int success;
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog;
	}
}

void ShaderProgram::attach()
{
	glUseProgram(m_ID);
}

void ShaderProgram::setUniformVec4(const std::string& name, const Vec4& vector) {
	glUniform4f(glGetUniformLocation(m_ID, name.c_str()), static_cast<float>(vector[0]), static_cast<float>(vector[1]), static_cast<float>(vector[2]), static_cast<float>(vector[3]));
}

void ShaderProgram::setUniformMatrix4x4(const std::string& name, const Matrix4x4& matrix, bool transpose)
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, transpose ? GL_TRUE : GL_FALSE, &matrix.getRawData());
}

void ShaderProgram::setUniformMatrix3x3(const std::string& name, const Matrix3x3& matrix)
{
	glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &matrix.getRawData());
}

void ShaderProgram::setUniformMatrix2x2(const std::string& name, const Matrix2x2& matrix)
{
	glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &matrix.getRawData());
}
