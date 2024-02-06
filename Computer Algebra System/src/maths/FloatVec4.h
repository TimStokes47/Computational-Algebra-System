#ifndef FLOAT_VEC_H
#define FLOAT_VEC_H

#include <iostream>
#include <intrin.h>


class FloatVec4 {
public:
	FloatVec4();
	FloatVec4(float x, float y, float z, float w);

	float x() const;
	float y() const;
	float z() const;
	float w() const;

	friend float dot(const FloatVec4& lhs, const FloatVec4& rhs);
	float const& operator[](int index) const;
	float& operator[](int index);

private:
	float m_data[4];
};

std::ostream& operator<<(std::ostream& output, const FloatVec4& vector);
//float slowDot(const FloatVec4& lhs, const FloatVec4& rhs);

#endif