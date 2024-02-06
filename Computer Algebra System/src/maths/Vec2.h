#ifndef VEC2_H
#define VEC2_H

#include "../expressionParsing/expression.h"

class Vec2 {
public:
	Vec2();
	Vec2(Expression x, Expression y);

	Expression x() const;
	Expression y() const;
	Expression const& operator[](int index) const;
	Expression& operator[](int index);
	friend Vec2 operator-(const Vec2& lhs, const Vec2& rhs);
	friend Expression dot(const Vec2& lhs, const Vec2& rhs);


private:
	Expression m_data[2];
};

std::ostream& operator<<(std::ostream& output, const Vec2& vector);

#endif