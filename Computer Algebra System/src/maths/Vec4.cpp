#include "Vec4.h"
#include <intrin.h>

Vec4::Vec4()
	: m_data{Expression(0), Expression(0), Expression(0), Expression(0) }
{
}

Vec4::Vec4(Expression x, Expression y, Expression z, Expression w)
	: m_data{ x, y, z, w }
{
}

Expression Vec4::x() const
{
	return m_data[0];
}

Expression Vec4::y() const
{
	return m_data[1];
}

Expression Vec4::z() const
{
	return m_data[2];
}

Expression Vec4::w() const
{
	return m_data[3];
}

Expression const& Vec4::operator[](int index) const
{
	return m_data[index];
}

Expression& Vec4::operator[](int index)
{
	return m_data[index];
}

std::ostream& operator<<(std::ostream& output, const Vec4& vector)
{
	output << "(" << vector.x() << ", " << vector.y() << ", " << vector.z() << ", " << vector.w() << ")";
	return output;
}

Expression dot(const Vec4& lhs, const Vec4& rhs)
{
	/*__m128 _lhs = _mm_load_ps(lhs.m_data);
	__m128 _rhs = _mm_load_ps(rhs.m_data);
	__m128 _product = _mm_mul_ps(_lhs, _rhs);
	return _product.m128_f32[0] + _product.m128_f32[1] + _product.m128_f32[2] + _product.m128_f32[3];*/

	return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z() + lhs.w() * rhs.w();
}