#include "FloatVec3.h"
#include <intrin.h>

FloatVec3::FloatVec3()
	: m_data{ 0.0f, 0.0f, 0.0f }
{
}

FloatVec3::FloatVec3(float x, float y, float z)
	: m_data{ x, y , z }
{
}

float FloatVec3::x() const
{
	return m_data[0];
}

float FloatVec3::y() const
{
	return m_data[1];
}

float FloatVec3::z() const
{
	return m_data[2];
}

float const& FloatVec3::operator[](int index) const
{
	return m_data[index];
}

float& FloatVec3::operator[](int index) {
	return m_data[index];
}

FloatVec3 normalise(const FloatVec3& vector)
{
	float length = std::sqrt(dot(vector, vector));
	return vector / length;
}

float dot(const FloatVec3& lhs, const FloatVec3& rhs)
{
	__m128 _lhs = _mm_load_ps(lhs.m_data);
	__m128 _rhs = _mm_load_ps(rhs.m_data);
	__m128 _product = _mm_mul_ps(_lhs, _rhs);
	return _product.m128_f32[0] + _product.m128_f32[1] + _product.m128_f32[2];
}

FloatVec3 cross(const FloatVec3& lhs, const FloatVec3& rhs)
{
	return FloatVec3(lhs[1] * rhs[2] - lhs[2] * rhs[1],
		rhs[0] * lhs[2] - rhs[2] * lhs[0],
		lhs[0] * rhs[1] - lhs[1] * rhs[0]);
}

FloatVec3 operator-(const FloatVec3& lhs, const FloatVec3& rhs)
{
	__m128 _lhs = _mm_load_ps(lhs.m_data);
	__m128 _rhs = _mm_load_ps(rhs.m_data);
	__m128 _result = _mm_sub_ps(_lhs, _rhs);
	return FloatVec3(_result.m128_f32[0], _result.m128_f32[1], _result.m128_f32[2]);
}

FloatVec3 operator+(const FloatVec3& lhs, const FloatVec3& rhs)
{
	__m128 _lhs = _mm_load_ps(lhs.m_data);
	__m128 _rhs = _mm_load_ps(rhs.m_data);
	__m128 _result = _mm_add_ps(_lhs, _rhs);
	return FloatVec3(_result.m128_f32[0], _result.m128_f32[1], _result.m128_f32[2]);
}

FloatVec3 operator/(const FloatVec3& lhs, float rhs)
{
	return FloatVec3(lhs[0] / rhs, lhs[1] / rhs, lhs[2] / rhs);
}

std::ostream& operator<<(std::ostream& output, const FloatVec3& vector)
{
	output << "(" << vector.x() << ", " << vector.y() << ", " << vector.z() << ")";
	return output;
}