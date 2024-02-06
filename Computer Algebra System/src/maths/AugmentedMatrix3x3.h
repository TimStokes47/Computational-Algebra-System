#ifndef AUGMENTED_MATRIX_3X3_H
#define AUGMENTED_mATRIX_3X3_H

#include "Matrix3x3.h"
#include <iostream>

class AugmentedMatrix3x3 {
public:
	AugmentedMatrix3x3(Matrix3x3 left, Vec3 right);
	void reduceLeft();
	inline Matrix3x3& getLeft() { return m_left; }
	inline Vec3& getRight() { return m_right; }

	friend std::ostream& operator<<(std::ostream& output, const AugmentedMatrix3x3& matrix);

	void multiplyRow(int row, float factor);
	void subtractRow(int modifiedRow, int rowToSubtract, float factor);
	void swapRows(int row1, int row3);
private:

	Matrix3x3 m_left;
	Vec3 m_right;
};

#endif