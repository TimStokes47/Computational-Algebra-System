#ifndef FLOAT_MATRIX_4X4_H
#define FLOAT_MATRIX_4X4_H

#include "FloatVec4.h"
#include "FloatVec3.h"
#include <array>

struct FloatRowReference {
	FloatRowReference(float& _x, float& _y, float& _z, float& _w)
		: x(_x), y(_y), z(_z), w(_w)
	{
	}

	float& x;
	float& y;
	float& z;
	float& w;
};

class FloatMatrix4x4 {
public:
	FloatMatrix4x4();
	FloatMatrix4x4(const FloatVec4& x, const FloatVec4& y, const FloatVec4& z, const FloatVec4& w);
	FloatVec4 const& operator[](int index) const;
	FloatVec4& operator[](int index);
	//RowReference getRow(int index);
	FloatVec4 getRowVector(int index) const;
	//void generateFloatData();
	//float const& getRawData() const;

	static FloatMatrix4x4 identity();
	static FloatMatrix4x4 translate(float x, float y, float z);
	static FloatMatrix4x4 rotateX(float angle);
	static FloatMatrix4x4 rotateY(float angle);
	static FloatMatrix4x4 orthographicProject(float left, float right, float top, float bottom, float near, float far);
	static FloatMatrix4x4 perspectiveProject(float aspectRatio, float fov, float near, float far);
	static FloatMatrix4x4 lookAt(const FloatVec3& origin, const FloatVec3& target, const FloatVec3& up);
	//friend FloatMatrix4x4 inverse(const FloatMatrix4x4& matrix);

	friend FloatVec4 operator*(const FloatMatrix4x4& lhs, const FloatVec4& rhs);
	friend FloatMatrix4x4 operator*(const FloatMatrix4x4& lhs, const FloatMatrix4x4& rhs);

private:
	FloatVec4 m_data[4];
};

#endif