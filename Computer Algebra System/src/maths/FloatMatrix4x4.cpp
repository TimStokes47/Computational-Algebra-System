#include "FloatMatrix4x4.h"
#include <array>

FloatMatrix4x4::FloatMatrix4x4()
	: m_data{ {}, {}, {}, {} }
{
}

FloatMatrix4x4::FloatMatrix4x4(const FloatVec4& x, const FloatVec4& y, const FloatVec4& z, const FloatVec4& w)
	: m_data{ x, y, z, w }
{
}

FloatVec4 const& FloatMatrix4x4::operator[](int index) const
{
	return m_data[index];
}

FloatVec4& FloatMatrix4x4::operator[](int index) {
	return m_data[index];
}

//RowReference FloatMatrix4x4::getRow(int index) {
//	generateFloatData();
//	return { m_floatData[0][index], m_floatData[1][index], m_floatData[2][index], m_floatData[3][index] };
//}

FloatVec4 FloatMatrix4x4::getRowVector(int index) const {
	return { m_data[0][index], m_data[1][index], m_data[2][index], m_data[3][index] };
}

//void FloatMatrix4x4::generateFloatData()
//{
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++) {
//			m_floatData[i][j] = m_data[i][j];
//		}
//	}
//}

//float const& FloatMatrix4x4::getRawData() const
//{
//	return m_floatData[0][0];
//}

FloatMatrix4x4 FloatMatrix4x4::identity()
{
	return FloatMatrix4x4(FloatVec4(1.0f, 0.0f, 0.0f, 0.0f),
		FloatVec4(0.0f, 1.0f, 0.0f, 0.0f),
		FloatVec4(0.0f, 0.0f, 1.0f, 0.0f),
		FloatVec4(0.0f, 0.0f, 0.0f, 1.0f));
}

FloatMatrix4x4 FloatMatrix4x4::translate(float x, float y, float z)
{
	return FloatMatrix4x4(FloatVec4(1.0f, 0.0f, 0.0f, 0.0f),
		FloatVec4(0.0f, 1.0f, 0.0f, 0.0f),
		FloatVec4(0.0f, 0.0f, 1.0f, 0.0f),
		FloatVec4(x, y, z, 1.0f));
}

FloatMatrix4x4 FloatMatrix4x4::rotateX(float angle)
{
	return FloatMatrix4x4(FloatVec4(1.0f, 0.0f, 0.0f, 0.0f),
		FloatVec4(0.0f, std::cos(angle), std::sin(angle), 0.0f),
		FloatVec4(0.0f, -std::sin(angle), std::cos(angle), 0.0f),
		FloatVec4(0.0f, 0.0f, 0.0f, 1.0f));
}

FloatMatrix4x4 FloatMatrix4x4::rotateY(float angle)
{
	return FloatMatrix4x4(FloatVec4(std::cos(angle), 0.0f, -std::sin(angle), 0.0f),
		FloatVec4(0.0f, 1.0f, 0.0f, 0.0f),
		FloatVec4(std::sin(angle), 0.0f, std::cos(angle), 0.0f),
		FloatVec4(0.0f, 0.0f, 0.0f, 1.0f));
}

FloatMatrix4x4 FloatMatrix4x4::orthographicProject(float left, float right, float top, float bottom, float near, float far)
{
	return FloatMatrix4x4(FloatVec4(2.0f / (right - left), 0.0f, 0.0f, 0.0f),
		FloatVec4(0.0f, 2.0f / (top - bottom), 0.0f, 0.0f),
		FloatVec4(0.0f, 0.0f, -2.0f / (far - near), 0.0f),
		FloatVec4(-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1.0f)
	);
}

FloatMatrix4x4 FloatMatrix4x4::perspectiveProject(float aspectRatio, float fov, float near, float far)
{
	float tan = std::tan(fov / 2.0f);
	return FloatMatrix4x4(FloatVec4(1.0f / (aspectRatio * tan), 0.0f, 0.0f, 0.0f),
		FloatVec4(0.0f, 1.0f / tan, 0.0f, 0.0f),
		FloatVec4(0.0f, 0.0f, -(far + near) / (far - near), -1.0f),
		FloatVec4(0.0f, 0.0f, -2.0f * far * near / (far - near), 0.0f)
	);
}

FloatMatrix4x4 FloatMatrix4x4::lookAt(const FloatVec3& origin, const FloatVec3& target, const FloatVec3& up)
{
	FloatVec3 localZ = normalise(target - origin);
	FloatVec3 localX = normalise(cross(localZ, up));
	FloatVec3 localY = cross(localX, localZ);

	FloatVec4 x(localX.x(), localY.x(), localZ.x(), 0.0f);
	FloatVec4 y(localX.y(), localY.y(), -localZ.y(), 0.0f);
	FloatVec4 z(localX.z(), localY.z(), -localZ.z(), 0.0f);
	FloatVec4 w(-dot(origin, localX), -dot(origin, localY), dot(origin, localZ), 1.0f);

	return FloatMatrix4x4(x, y, z, w);
}

FloatVec4 operator*(const FloatMatrix4x4& lhs, const FloatVec4& rhs) {
	FloatVec4 result;
	for (int i = 0; i < 4; i++) {
		result[i] = dot(lhs.getRowVector(i), rhs);
	}
	return result;
}

FloatMatrix4x4 operator*(const FloatMatrix4x4& lhs, const FloatMatrix4x4& rhs) {
	FloatMatrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result[i][j] = dot(lhs.getRowVector(j), rhs[i]);
		}
	}
	return result;
}