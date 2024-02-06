#include "FloatVec4.h"
#include <intrin.h>

FloatVec4::FloatVec4()
	: m_data{ float(0), float(0), float(0), float(0) }
{
}

FloatVec4::FloatVec4(float x, float y, float z, float w)
	: m_data{ x, y, z, w }
{
}

float FloatVec4::x() const
{
	return m_data[0];
}

float FloatVec4::y() const
{
	return m_data[1];
}

float FloatVec4::z() const
{
	return m_data[2];
}

float FloatVec4::w() const
{
	return m_data[3];
}

float const& FloatVec4::operator[](int index) const
{
	return m_data[index];
}

float& FloatVec4::operator[](int index)
{
	return m_data[index];
}

std::ostream& operator<<(std::ostream& output, const FloatVec4& vector)
{
	output << "(" << vector.x() << ", " << vector.y() << ", " << vector.z() << ", " << vector.w() << ")";
	return output;
}

float dot(const FloatVec4& lhs, const FloatVec4& rhs)
{
	__m128 _lhs = _mm_load_ps(lhs.m_data);
	__m128 _rhs = _mm_load_ps(rhs.m_data);
	__m128 _product = _mm_mul_ps(_lhs, _rhs);
	return _product.m128_f32[0] + _product.m128_f32[1] + _product.m128_f32[2] + _product.m128_f32[3];
}