#ifndef AUGMENTED_MATRIX_2X2_H
#define AUGMENTED_mATRIX_2X2_H

#include "Matrix2x2.h"
#include <iostream>

class AugmentedMatrix2x2 {
public:
	AugmentedMatrix2x2(Matrix2x2 left, Vec2 right);
	void reduceLeft();
	inline Matrix2x2& getLeft() { return m_left; }
	inline Vec2& getRight() { return m_right; }

	friend std::ostream& operator<<(std::ostream& output, const AugmentedMatrix2x2& matrix);

	void multiplyRow(int row, float factor);
	void subtractRow(int modifiedRow, int rowToSubtract, float factor);
	void swapRows(int row1, int row2);
private:

	Matrix2x2 m_left;
	Vec2 m_right;
};

#endif