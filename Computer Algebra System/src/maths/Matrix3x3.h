#ifndef MATRIX_3X3_H
#define MATRIX_3X3_H

#include "Vec3.h"
#include "Vec3.h"
#include <array>

struct Matrix3x3RowReference {
	Matrix3x3RowReference(float& _x, float& _y, float& _z) 
		: x(_x), y(_y), z(_z)
	{
	}

	float& x;
	float& y;
	float& z;
};

class Matrix3x3 {
public:
	Matrix3x3();
	Matrix3x3(const Vec3& x, const Vec3& y, const Vec3& z);
	Vec3 const& operator[](int index) const;
	Vec3& operator[](int index);
	Matrix3x3RowReference getRow(int index);
	Vec3 getRowVector(int index) const;
	void generateFloatData();
	float const& getRawData() const;
	Expression trace();
	
	Matrix3x3 operator-(const Matrix3x3& rhs) const;
	Matrix3x3 operator+(const Matrix3x3& rhs) const;

	friend Matrix3x3 operator*(const Matrix3x3& lhs, const Expression& rhs);
	friend Matrix3x3 operator*(const Expression& lhs, const Matrix3x3& rhs);

	Expression calculateDeterminant();

	static Matrix3x3 identity();
	static Matrix3x3 translate(float x, float y);
	std::vector<Vec3> calculateEigenvectors();

	
	friend Vec3 operator*(const Matrix3x3& lhs, const Vec3& rhs);
	friend Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs);

private:
	Vec3 m_data[3];
	float m_floatData[3][3];
};

#endif