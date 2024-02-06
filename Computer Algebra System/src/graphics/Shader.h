#ifndef SHADER_H
#define SHADER_H

#include <string>

class ShaderProgram;
class Matrix4x4;
class Matrix3x3;
class Matrix2x2;
class Vec4;

class Shader {
public:
	Shader(const std::string& filepath, unsigned int shaderType);
	friend ShaderProgram;

private:
	unsigned int m_ID;
};

class ShaderProgram {
public:
	ShaderProgram();
	void linkShader(const Shader& shader);
	void compile();
	void attach();

	void setUniformVec4(const std::string& name, const Vec4& vector);
	void setUniformMatrix4x4(const std::string& name, const Matrix4x4& matrix, bool transpose = false);
	void setUniformMatrix3x3(const std::string& name, const Matrix3x3& matrix);
	void setUniformMatrix2x2(const std::string& name, const Matrix2x2& matrix);

private:
	unsigned int m_ID;
};

#endif