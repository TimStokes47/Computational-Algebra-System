#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <intrin.h>

#include "../expressionParsing/expression.h"

class Vec4 {
public:
	Vec4();
	Vec4(Expression x, Expression y, Expression z, Expression w);

	Expression x() const;
	Expression y() const;
	Expression z() const;
	Expression w() const;

	friend Expression dot(const Vec4& lhs, const Vec4& rhs);
	Expression const& operator[](int index) const;
	Expression& operator[](int index);

private:
	Expression m_data[4];
};

std::ostream& operator<<(std::ostream& output, const Vec4& vector);
//float slowDot(const Vec4& lhs, const Vec4& rhs);

#endif