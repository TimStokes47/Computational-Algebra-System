#ifndef AUGMENTED_MATRIX_H
#define AUGMENTED_mATRIX_H

#include "Matrix4x4.h"
#include <iostream>

class AugmentedMatrix4x4 {
public:
	AugmentedMatrix4x4(Matrix4x4 left, Matrix4x4 right);
	void reduceLeft();
	inline Matrix4x4& getLeft() { return m_left; }
	inline Matrix4x4& getRight() { return m_right; }

	friend std::ostream& operator<<(std::ostream& output, const AugmentedMatrix4x4& matrix);

	void multiplyRow(int row, float factor);
	void subtractRow(int modifiedRow, int rowToSubtract, float factor);
	void swapRows(int row1, int row2);
private:

	Matrix4x4 m_left;
	Matrix4x4 m_right;
};

#endif