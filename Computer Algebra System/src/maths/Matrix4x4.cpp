#include "Matrix4x4.h"
#include <array>

Matrix4x4::Matrix4x4() 
	: m_data{ {}, {}, {}, {} }, m_floatData{ {}, {}, {}, {} }
{
}

Matrix4x4::Matrix4x4(const Vec4& x, const Vec4& y, const Vec4& z, const Vec4& w)
	: m_data{ x, y, z, w }, m_floatData{ x[0], x[1], x[2], x[3], y[0], y[1], y[2], y[3], z[0], z[1], z[2], z[3], w[0], w[1], w[2], w[3]}
{
}

Vec4 const& Matrix4x4::operator[](int index) const
{
	return m_data[index];
}

Vec4& Matrix4x4::operator[](int index) {
	return m_data[index];
}

RowReference Matrix4x4::getRow(int index) {
	generateFloatData();
	return { m_floatData[0][index], m_floatData[1][index], m_floatData[2][index], m_floatData[3][index] };
}

Vec4 Matrix4x4::getRowVector(int index) const{
	return { m_data[0][index], m_data[1][index], m_data[2][index], m_data[3][index] };
}

void Matrix4x4::generateFloatData()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_floatData[i][j] = m_data[i][j];
		}
	}
}

float const& Matrix4x4::getRawData() const
{
	return m_floatData[0][0];
}

Matrix4x4 Matrix4x4::identity()
{
	return Matrix4x4(Vec4(1.0f, 0.0f, 0.0f, 0.0f),
		Vec4(0.0f, 1.0f, 0.0f, 0.0f),
		Vec4(0.0f, 0.0f, 1.0f, 0.0f),
		Vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

Matrix4x4 Matrix4x4::translate(float x, float y, float z)
{
	return Matrix4x4(Vec4(1.0f, 0.0f, 0.0f, 0.0f),
		Vec4(0.0f, 1.0f, 0.0f, 0.0f),
		Vec4(0.0f, 0.0f, 1.0f, 0.0f),
		Vec4(x, y, z, 1.0f));
}

Matrix4x4 Matrix4x4::orthographicProject(float left, float right, float top, float bottom, float near, float far)
{
	return Matrix4x4(Vec4(2.0f / (right - left), 0.0f, 0.0f, 0.0f),
		Vec4(0.0f, 2.0f / (top - bottom), 0.0f, 0.0f),
		Vec4(0.0f, 0.0f, -2.0f / (far - near), 0.0f),
		Vec4(-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1.0f)
	);
}

Matrix4x4 Matrix4x4::perspectiveProject(float aspectRatio, float fov, float near, float far)
{
	float tan = std::tan(fov / 2.0f);
	return Matrix4x4(Vec4(1.0f / (aspectRatio * tan), 0.0f, 0.0f, 0.0f),
		Vec4(0.0f, 1.0f / tan, 0.0f, 0.0f), 
		Vec4(0.0f, 0.0f, -(far + near) / (far - near), -1.0f),
		Vec4(0.0f, 0.0f, -2.0f * far * near / (far - near), 0.0f)
	);
}

Matrix4x4 Matrix4x4::lookAt(const FloatVec3& origin, const FloatVec3& target, const FloatVec3& up)
{
	FloatVec3 localZ = normalise(target - origin);
	FloatVec3 localX = normalise(cross(localZ, up));
	FloatVec3 localY = cross(localX, localZ);

	Vec4 x(localX.x(), localY.x(), -localZ.x(), 0.0f);
	Vec4 y(localX.y(), localY.y(), -localZ.y(), 0.0f);
	Vec4 z(localX.z(), localY.z(), -localZ.z(), 0.0f);
	Vec4 w(-dot(origin, localX), -dot(origin, localY), dot(origin, localZ), 1.0f);

	return Matrix4x4(x, y, z, w);
}


Matrix4x4 Matrix4x4::rotateX(float angle)
{
	return Matrix4x4(Vec4(1.0f, 0.0f, 0.0f, 0.0f),
		Vec4(0.0f, std::cos(angle), std::sin(angle), 0.0f),
		Vec4(0.0f, -std::sin(angle), std::cos(angle), 0.0f),
		Vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

Matrix4x4 Matrix4x4::rotateY(float angle)
{
	return Matrix4x4(Vec4(std::cos(angle), 0.0f, -std::sin(angle), 0.0f),
		Vec4(0.0f, 1.0f, 0.0f, 0.0f),
		Vec4(std::sin(angle), 0.0f, std::cos(angle), 0.0f),
		Vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& rhs) const
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result[i][j] = (*this)[i][j] - rhs[i][j];
		}
	}
	return result;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& rhs) const
{
	return Matrix4x4(Vec4(m_data[0][0] + rhs[0][0], m_data[0][1] + rhs[0][1], m_data[0][2] + rhs[0][2], m_data[0][3] + rhs[0][3]),
		Vec4(m_data[1][0] + rhs[1][0], m_data[1][1] + rhs[1][1], m_data[1][2] + rhs[1][2], m_data[1][3] + rhs[1][3]),
		Vec4(m_data[2][0] + rhs[2][0], m_data[2][1] + rhs[2][1], m_data[2][2] + rhs[2][2], m_data[2][3] + rhs[2][3]),
		Vec4(m_data[3][0] + rhs[3][0], m_data[3][1] + rhs[3][1], m_data[3][2] + rhs[3][2], m_data[3][3] + rhs[3][3]));
}

Matrix4x4 operator*(const Matrix4x4& lhs, const Expression& rhs)
{
	return Matrix4x4(Vec4(lhs[0][0] * rhs, lhs[0][1] * rhs, lhs[0][2] * rhs, lhs[0][3] * rhs),
		Vec4(lhs[1][0] * rhs, lhs[1][1] * rhs, lhs[1][2] * rhs, lhs[1][3] * rhs),
		Vec4(lhs[2][0] * rhs, lhs[2][1] * rhs, lhs[2][2] * rhs, lhs[2][3] * rhs),
		Vec4(lhs[3][0] * rhs, lhs[3][1] * rhs, lhs[3][2] * rhs, lhs[3][3] * rhs));
}

Matrix4x4 operator*(const Expression& lhs, const Matrix4x4& rhs)
{
	return rhs * lhs;
}

Vec4 operator*(const Matrix4x4& lhs, const Vec4& rhs) {
	Vec4 result;
	for (int i = 0; i < 4; i++) {
		result[i] = dot(lhs.getRowVector(i), rhs);
	}
	return result;
}

Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs) {
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result[i][j] = dot(lhs.getRowVector(j), rhs[i]);
		}
	}
	return result;
}