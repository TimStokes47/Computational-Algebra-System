#ifndef FLOAT_VEC3_H
#define FLOAT_VEC3_H

#include <iostream>

class FloatVec3 {
public:
	FloatVec3();
	FloatVec3(float x, float y, float z);

	float x() const;
	float y() const;
	float z() const;

	friend FloatVec3 normalise(const FloatVec3& vector);
	friend float dot(const FloatVec3& lhs, const FloatVec3& rhs);
	friend FloatVec3 cross(const FloatVec3& lhs, const FloatVec3& rhs);
	friend FloatVec3 operator-(const FloatVec3& lhs, const FloatVec3& rhs);
	friend FloatVec3 operator+(const FloatVec3& lhs, const FloatVec3& rhs);
	friend FloatVec3 operator/(const FloatVec3& lhs, float rhs);
	float const& operator[](int index) const;
	float& operator[](int index);

private:
	float m_data[3];
};

std::ostream& operator<<(std::ostream& output, const FloatVec3& vector);

#endif