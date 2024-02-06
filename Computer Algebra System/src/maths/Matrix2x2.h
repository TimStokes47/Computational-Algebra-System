#ifndef MATRIX_2X2_H
#define MATRIX_2X2_H

#include "Vec2.h"
#include <array>

struct Matrix2x2RowReference {
	Matrix2x2RowReference(Expression& _x, Expression& _y)
		: x(_x), y(_y)
	{
	}

	Expression& x;
	Expression& y;
};

class Matrix2x2 {
public:
	Matrix2x2();
	Matrix2x2(const Vec2& x, const Vec2& y);
	Vec2 const& operator[](int index) const;
	Vec2& operator[](int index);
	Matrix2x2RowReference getRow(int index);
	Vec2 getRowVector(int index) const;
	void generateFloatData();
	float const& getRawData() const;
	Expression calculateDeterminant();
	static Matrix2x2 identity();
	
	Matrix2x2 operator-(const Matrix2x2& rhs) const;
	Matrix2x2 operator+(const Matrix2x2& rhs) const;

	friend Matrix2x2 operator*(const Matrix2x2& lhs, const Expression& rhs);
	friend Matrix2x2 operator*(const Expression& lhs, const Matrix2x2& rhs);

	std::vector<Vec2> calculateEigenvectors();
	friend Vec2 operator*(const Matrix2x2& lhs, const Vec2& rhs);
	friend Matrix2x2 operator*(const Matrix2x2& lhs, const Matrix2x2& rhs);

private:
	Vec2 m_data[2];
	float m_floatData[2][2];
};

#endif