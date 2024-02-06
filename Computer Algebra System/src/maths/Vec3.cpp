#include "Vec3.h"
#include "Vec4.h"
#include <intrin.h>

Vec3::Vec3()
	: m_data{0.0f, 0.0f, 0.0f}
{
}

Vec3::Vec3(Expression x, Expression y, Expression z)
	: m_data{ x, y , z }
{
}

Vec3::Vec3(const Vec4& vec4)
	: m_data{ vec4.x() / vec4.w(), vec4. y() / vec4.w(), vec4.z() / vec4.w() }
{
}

Expression Vec3::x() const
{
	return m_data[0];
}

Expression Vec3::y() const
{
	return m_data[1];
}

Expression Vec3::z() const
{
	return m_data[2];
}

Expression const& Vec3::operator[](int index) const
{
	return m_data[index];
}

Expression& Vec3::operator[](int index) {
	return m_data[index];
}

Vec3 normalise(const Vec3& vector)
{
	float length = std::sqrt(dot(vector, vector));
	return vector / length;
}

Expression dot(const Vec3& lhs, const Vec3& rhs)
{
	/*__m128 _lhs = _mm_load_ps(lhs.m_data);
	__m128 _rhs = _mm_load_ps(rhs.m_data);
	__m128 _product = _mm_mul_ps(_lhs, _rhs);
	return _product.m128_f32[0] + _product.m128_f32[1] + _product.m128_f32[2];*/
	return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
}

Vec3 cross(const Vec3& lhs, const Vec3& rhs)
{
	return Vec3(lhs[1] * rhs[2] - lhs[2] * rhs[1],
		rhs[0] * lhs[2] - rhs[2] * lhs[0],
		lhs[0] * rhs[1] - lhs[1] * rhs[0]);
}

Vec3 operator-(const Vec3& lhs, const Vec3& rhs)
{
	/*__m128 _lhs = _mm_load_ps(lhs.m_data);
	__m128 _rhs = _mm_load_ps(rhs.m_data);
	__m128 _result = _mm_sub_ps(_lhs, _rhs);
	return Vec3(_result.m128_f32[0], _result.m128_f32[1], _result.m128_f32[2]);*/
	return Vec3(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]);
}

Vec3 operator+(const Vec3& lhs, const Vec3& rhs)
{
	/*__m128 _lhs = _mm_load_ps(lhs.m_data);
	__m128 _rhs = _mm_load_ps(rhs.m_data);
	__m128 _result = _mm_add_ps(_lhs, _rhs);
	return Vec3(_result.m128_f32[0], _result.m128_f32[1], _result.m128_f32[2]);*/

	return Vec3(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]);
}

Vec3 operator/(const Vec3& lhs, Expression rhs)
{
	return Vec3(lhs[0] / rhs, lhs[1] / rhs, lhs[2] / rhs);
}

std::ostream& operator<<(std::ostream& output, const Vec3& vector)
{
	output << "(" << vector.x() << ", " << vector.y() << ", " << vector.z() << ")";
	return output;
}
