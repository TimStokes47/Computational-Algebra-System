#include "Augmented Matrix4x4.h"
#include <iomanip>

AugmentedMatrix4x4::AugmentedMatrix4x4(Matrix4x4 left, Matrix4x4 right)
	: m_left(left), m_right(right)
{}

void AugmentedMatrix4x4::reduceLeft() {
	int column = 0;
	while (column != 4) {
		if (m_left[column][column] > -0.0001f || m_left[column][column] < 0.0001f) {
			bool swapped = false;
			for (int j = column; j < 4; j++) {
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
		for (int j = column + 1; j < 4; j++) {
			subtractRow(j, column, m_left[column][j]);
		}
		column++;
	}
}

std::ostream& operator<<(std::ostream& output, const AugmentedMatrix4x4& matrix) {	
	output << std::fixed << std::setprecision(2);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			output << matrix.m_left[j][i] << " ";
		}
		output << "| ";
		for (int j = 0; j < 4; j++) {
			output << matrix.m_right[j][i] << " ";
		}
		if (i != 3) output << "\n";
	}

	return output;
}

void AugmentedMatrix4x4::multiplyRow(int row, float factor) {
	m_left.getRow(row).x *= factor;
	m_left.getRow(row).y *= factor;
	m_left.getRow(row).z *= factor;
	m_left.getRow(row).w *= factor;

	m_right.getRow(row).x *= factor;
	m_right.getRow(row).y *= factor;
	m_right.getRow(row).z *= factor;
	m_right.getRow(row).w *= factor;
}

void AugmentedMatrix4x4::subtractRow(int modifiedRow, int rowToSubtract, float factor) {
	m_left.getRow(modifiedRow).x -= m_left.getRow(rowToSubtract).x * factor;
	m_left.getRow(modifiedRow).y -= m_left.getRow(rowToSubtract).y * factor;
	m_left.getRow(modifiedRow).z -= m_left.getRow(rowToSubtract).z * factor;
	m_left.getRow(modifiedRow).w -= m_left.getRow(rowToSubtract).w * factor;

	m_right.getRow(modifiedRow).x -= m_right.getRow(rowToSubtract).x * factor;
	m_right.getRow(modifiedRow).y -= m_right.getRow(rowToSubtract).y * factor;
	m_right.getRow(modifiedRow).z -= m_right.getRow(rowToSubtract).z * factor;
	m_right.getRow(modifiedRow).w -= m_right.getRow(rowToSubtract).w * factor;
}

void AugmentedMatrix4x4::swapRows(int row1, int row2) {
	float temp;
	temp = m_left.getRow(row1).x;
	m_left.getRow(row1).x = m_left.getRow(row2).x;
	m_left.getRow(row2).x = temp;

	temp = m_left.getRow(row1).y;
	m_left.getRow(row1).y = m_left.getRow(row2).y;
	m_left.getRow(row2).y = temp;

	temp = m_left.getRow(row1).z;
	m_left.getRow(row1).z = m_left.getRow(row2).z;
	m_left.getRow(row2).z = temp;

	temp = m_left.getRow(row1).w;
	m_left.getRow(row1).w = m_left.getRow(row2).w;
	m_left.getRow(row2).w = temp;

	temp = m_right.getRow(row1).x;
	m_right.getRow(row1).x = m_right.getRow(row2).x;
	m_right.getRow(row2).x = temp;

	temp = m_right.getRow(row1).y;
	m_right.getRow(row1).y = m_right.getRow(row2).y;
	m_right.getRow(row2).y = temp;

	temp = m_right.getRow(row1).z;
	m_right.getRow(row1).z = m_right.getRow(row2).z;
	m_right.getRow(row2).z = temp;

	temp = m_right.getRow(row1).w;
	m_right.getRow(row1).w = m_right.getRow(row2).w;
	m_right.getRow(row2).w = temp;
}