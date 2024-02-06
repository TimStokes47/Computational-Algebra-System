#ifndef MATRIX_4X4_H
#define MATRIX_4X4_H

#include "Vec4.h"
#include "FloatVec3.h"
#include <array>
#include <vector>

struct RowReference {
	RowReference(float& _x, float& _y, float& _z, float& _w) 
		: x(_x), y(_y), z(_z), w(_w)
	{
	}

	float& x;
	float& y;
	float& z;
	float& w;
};

class Matrix4x4 {
public:
	Matrix4x4();
	Matrix4x4(const Vec4& x, const Vec4& y, const Vec4& z, const Vec4& w);
	Vec4 const& operator[](int index) const;
	Vec4& operator[](int index);
	RowReference getRow(int index);
	Vec4 getRowVector(int index) const;
	void generateFloatData();
	float const& getRawData() const;
	
	static Matrix4x4 identity();
	static Matrix4x4 translate(float x, float y, float z);
	static Matrix4x4 orthographicProject(float left, float right, float top, float bottom, float near, float far);
	static Matrix4x4 perspectiveProject(float aspectRatio, float fov, float near, float far);
	static Matrix4x4 lookAt(const FloatVec3& origin, const FloatVec3& target, const FloatVec3& up);
	static Matrix4x4 rotateX(float angle);
	static Matrix4x4 rotateY(float angle);

	//friend Matrix4x4 inverse(const Matrix4x4& matrix);
	Matrix4x4 operator-(const Matrix4x4& rhs) const;
	Matrix4x4 operator+(const Matrix4x4& rhs) const;
	
	friend Matrix4x4 operator*(const Matrix4x4& lhs, const Expression& rhs);
	friend Matrix4x4 operator*(const Expression& lhs, const Matrix4x4& rhs);

	friend Vec4 operator*(const Matrix4x4& lhs, const Vec4& rhs);
	friend Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs);

private:
	Vec4 m_data[4];
	float m_floatData[4][4];
};

#endif