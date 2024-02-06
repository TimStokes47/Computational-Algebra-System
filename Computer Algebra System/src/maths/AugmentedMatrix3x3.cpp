#include "AugmentedMatrix3x3.h"
#include <iomanip>

AugmentedMatrix3x3::AugmentedMatrix3x3(Matrix3x3 left, Vec3 right)
	: m_left(left), m_right(right)
{}

void AugmentedMatrix3x3::reduceLeft() {
	int column = 0;
	while (column != 3) {
		if (m_left[column][column] > -0.0001f || m_left[column][column] < 0.0001f) {
			bool swapped = false;
			for (int j = column; j < 3; j++) {
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
		for (int j = column + 1; j < 3; j++) {
			subtractRow(j, column, m_left[column][j]);
		}
		column++;
	}
}

std::ostream& operator<<(std::ostream& output, const AugmentedMatrix3x3& matrix) {
	output << std::fixed << std::setprecision(3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			output << matrix.m_left[j][i] << " ";
		}
		output << "| ";
		output << matrix.m_right[i] << "\n";
	}

	return output;
}

void AugmentedMatrix3x3::multiplyRow(int row, float factor) {
	m_left.getRow(row).x = m_left.getRow(row).x * factor;
	m_left.getRow(row).y = m_left.getRow(row).y * factor;

	m_right[row] = m_right[row] * factor;
}

void AugmentedMatrix3x3::subtractRow(int modifiedRow, int rowToSubtract, float factor) {
	m_left.getRow(modifiedRow).x = m_left.getRow(modifiedRow).x - m_left.getRow(rowToSubtract).x * factor;
	m_left.getRow(modifiedRow).y = m_left.getRow(modifiedRow).y - m_left.getRow(rowToSubtract).y * factor;

	m_right[modifiedRow] = m_right[modifiedRow] - m_right[rowToSubtract] * factor;
}

void AugmentedMatrix3x3::swapRows(int row1, int row3) {
	Expression temp;
	temp = m_left.getRow(row1).x;
	m_left.getRow(row1).x = m_left.getRow(row3).x;
	m_left.getRow(row3).x = temp;

	temp = m_left.getRow(row1).y;
	m_left.getRow(row1).y = m_left.getRow(row3).y;
	m_left.getRow(row3).y = temp;

	temp = m_right[row1];
	m_right[row1] = m_right[row3];
	m_right[row3] = temp;
}