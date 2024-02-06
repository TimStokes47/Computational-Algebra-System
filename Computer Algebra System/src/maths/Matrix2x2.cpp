#include "Matrix2x2.h"
#include <array>
#include "AugmentedMatrix2x2.h"

Matrix2x2::Matrix2x2() 
	: m_data{ {}, {} }, m_floatData{ {}, {}}
{
}

Matrix2x2::Matrix2x2(const Vec2& x, const Vec2& y)
	: m_data{ x, y}, m_floatData{ x.x(), x.y(), y.x(), y.y()}
{
}

Vec2 const& Matrix2x2::operator[](int index) const
{
	return m_data[index];
}

Vec2& Matrix2x2::operator[](int index) {
	return m_data[index];
}

Matrix2x2RowReference Matrix2x2::getRow(int index)
{
	return { m_data[0][index], m_data[1][index] };
}

Vec2 Matrix2x2::getRowVector(int index) const{
	return { m_data[0][index], m_data[1][index]};
}

void Matrix2x2::generateFloatData()
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			m_floatData[i][j] = m_data[i][j];
		}
	}
}

float const& Matrix2x2::getRawData() const
{
	return m_floatData[0][0];
}

Expression Matrix2x2::calculateDeterminant()
{
	return m_data[0][0] * m_data[1][1] - m_data[1][0] * m_data[0][1];
}

Matrix2x2 Matrix2x2::identity()
{
	return Matrix2x2(Vec2(1.0f, 0.0f),
		Vec2(0.0f, 1.0f));
}

std::vector<Vec2> Matrix2x2::calculateEigenvectors()
{
	std::vector<Expression> eigenvalues;
	std::vector<Vec2> eigenvectors;

	Expression determinant = (m_data[0][0] + m_data[1][1]) * (m_data[0][0] + m_data[1][1]) - 4 * calculateDeterminant();
	if ((float)determinant >= 0.0f) {
		eigenvalues.push_back((m_data[0][0] + m_data[1][1] + std::sqrt((float)determinant)) / 2.0f);
		eigenvalues.push_back((m_data[0][0] + m_data[1][1] - std::sqrt((float)determinant)) / 2.0f);
	}
	
	for (auto eigenvalue : eigenvalues) {
		Matrix2x2 matrix = eigenvalue * Matrix2x2::identity() - *this;
		Vec2 vector;
		AugmentedMatrix2x2 augmented(matrix, vector);
		augmented.reduceLeft();
		std::cout << augmented << "\n";
		Expression y = 1.0f;
		Expression x;
		if (augmented.getLeft()[1][1] > 0.0001f || augmented.getLeft()[1][1] < -0.0001) {
			y = 0.0f;
		}
		if (augmented.getLeft()[0][0] > 0.0001f || augmented.getLeft()[0][0] < -0.0001) {
			x = -augmented.getLeft()[1][0] * y / augmented.getLeft()[0][0];
		}
		else { x = 1.0f; y = 0.0f; }
		eigenvectors.push_back(Vec2(x, y));
	}
	return eigenvectors;
}


Matrix2x2 Matrix2x2::operator-(const Matrix2x2& rhs) const
{
	Matrix2x2 result;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			result[i][j] = (*this)[i][j] - rhs[i][j];
		}
	}
	return result;
}

Matrix2x2 Matrix2x2::operator+(const Matrix2x2& rhs) const
{
	return Matrix2x2(Vec2(m_data[0][0] + rhs[0][0], m_data[0][1] + rhs[0][1]),
		Vec2(m_data[1][0] + rhs[1][0], m_data[1][1] + rhs[1][1]));
}

Matrix2x2 operator*(const Matrix2x2& lhs, const Expression& rhs)
{
	return Matrix2x2(Vec2(lhs[0][0] * rhs, lhs[0][1] * rhs),
		Vec2(lhs[1][0] * rhs, lhs[1][1] * rhs));
}

Matrix2x2 operator*(const Expression& lhs, const Matrix2x2& rhs)
{
	return rhs * lhs;
}

Vec2 operator*(const Matrix2x2& lhs, const Vec2& rhs) {
	Vec2 result;
	for (int i = 0; i < 2; i++) {
		result[i] = dot(lhs.getRowVector(i), rhs);
	}
	return result;
}

Matrix2x2 operator*(const Matrix2x2& lhs, const Matrix2x2& rhs) {
	Matrix2x2 result;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			result[i][j] = dot(lhs.getRowVector(j), rhs[i]);
		}
	}
	return result;
}