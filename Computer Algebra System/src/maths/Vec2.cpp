#include "Vec2.h"

Vec2::Vec2()
	: m_data{ 0.0f, 0.0f }
{
}

Vec2::Vec2(Expression x, Expression y) 
	: m_data{ x, y }
{
}

Expression Vec2::x() const {
	return m_data[0];
}

Expression Vec2::y() const {
	return m_data[1];
}

Expression const& Vec2::operator[](int index) const
{
	return m_data[index];
}

Expression& Vec2::operator[](int index)
{
	return m_data[index];
}

Vec2 operator-(const Vec2& lhs, const Vec2& rhs) {
	return Vec2(lhs.x() - rhs.x(), lhs.y() - rhs.y());
}

Expression dot(const Vec2& lhs, const Vec2& rhs)
{
	return lhs[0] * rhs[0] + lhs[1] * rhs[1];
}

std::ostream& operator<<(std::ostream& output, const Vec2& vector)
{
	output << "(" << vector.x() << ", " << vector.y() << ")";
	return output;
}