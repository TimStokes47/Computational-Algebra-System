#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include "../expressionParsing/expression.h"

class Vec4;

class Vec3 {
public:
	Vec3();
	Vec3(Expression x, Expression y, Expression z);
	Vec3(const Vec4& vec4);

	Expression x() const;
	Expression y() const;
	Expression z() const;

	friend Vec3 normalise(const Vec3& vector);
	friend Expression dot(const Vec3& lhs, const Vec3& rhs);
	friend Vec3 cross(const Vec3& lhs, const Vec3& rhs);
	friend Vec3 operator-(const Vec3& lhs, const Vec3& rhs);
	friend Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
	friend Vec3 operator/(const Vec3& lhs, Expression rhs);
	Expression const& operator[](int index) const;
	Expression& operator[](int index);

private:
	Expression m_data[3];
};

std::ostream& operator<<(std::ostream& output, const Vec3& vector);

#endif