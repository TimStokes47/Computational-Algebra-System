#include "AugmentedMatrix2x2.h"
#include <iomanip>

AugmentedMatrix2x2::AugmentedMatrix2x2(Matrix2x2 left, Vec2 right)
	: m_left(left), m_right(right)
{}

void AugmentedMatrix2x2::reduceLeft() {
	int column = 0;
	while (column != 2) {
		if (m_left[column][column] > -0.0001f || m_left[column][column] < 0.0001f) {
			bool swapped = false;
			for (int j = column; j < 2; j++) {
				if (m_left[column][j] < -0.0001f || m_left[column][j] > 0.0001f) {
					swapRows(column, j);
					swapped = true;
				}
			}
			if (!swapped) return;
		}
		multiplyRow(column, 1.0f / (float)m_left[column][column]);
		for (int j = 0; j < column; j++) {
			subtractRow(j, column, m_left[column][j]);
		}
		for (int j = column + 1; j < 2; j++) {
			subtractRow(j, column, m_left[column][j]);
		}
		column++;
	}
}

std::ostream& operator<<(std::ostream& output, const AugmentedMatrix2x2& matrix) {
	output << std::fixed << std::setprecision(2);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			output << matrix.m_left[j][i] << " ";
		}
		output << "| ";
		output << matrix.m_right[i] << "\n";
	}

	return output;
}

void AugmentedMatrix2x2::multiplyRow(int row, float factor) {
	m_left.getRow(row).x = m_left.getRow(row).x * factor;
	m_left.getRow(row).y = m_left.getRow(row).y * factor;

	m_right[row] = m_right[row] * factor;
}

void AugmentedMatrix2x2::subtractRow(int modifiedRow, int rowToSubtract, float factor) {
	m_left.getRow(modifiedRow).x = m_left.getRow(modifiedRow).x - m_left.getRow(rowToSubtract).x * factor;
	m_left.getRow(modifiedRow).y = m_left.getRow(modifiedRow).y - m_left.getRow(rowToSubtract).y * factor;

	m_right[modifiedRow] = m_right[modifiedRow] - m_right[rowToSubtract] * factor;
}

void AugmentedMatrix2x2::swapRows(int row1, int row2) {
	Expression temp;
	temp = m_left.getRow(row1).x;
	m_left.getRow(row1).x = m_left.getRow(row2).x;
	m_left.getRow(row2).x = temp;

	temp = m_left.getRow(row1).y;
	m_left.getRow(row1).y = m_left.getRow(row2).y;
	m_left.getRow(row2).y = temp;

	temp = m_right[row1];
	m_right[row1] = m_right[row2];
	m_right[row2] = temp;
}