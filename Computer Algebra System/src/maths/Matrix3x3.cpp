#include "Matrix3x3.h"
#include <array>
#include "AugmentedMatrix3x3.h"
#include "Matrix2x2.h"

Matrix3x3::Matrix3x3() 
	: m_data{ {}, {}, {} }, m_floatData{ {}, {}, {} }
{
}

Matrix3x3::Matrix3x3(const Vec3& x, const Vec3& y, const Vec3& z)
	: m_data{ x, y, z}, m_floatData{ x[0], x[1], x[2],  y[0], y[1], y[2], z[0], z[1], z[2]}
{
}

Vec3 const& Matrix3x3::operator[](int index) const
{
	return m_data[index];
}

Vec3& Matrix3x3::operator[](int index) {
	return m_data[index];
}

Matrix3x3RowReference Matrix3x3::getRow(int index) {
	generateFloatData();
	return { m_floatData[0][index], m_floatData[1][index], m_floatData[2][index] };
}

Vec3 Matrix3x3::getRowVector(int index) const{
	return { m_data[0][index], m_data[1][index], m_data[2][index] };
}

void Matrix3x3::generateFloatData()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			m_floatData[i][j] = m_data[i][j];
		}
	}
}

float const& Matrix3x3::getRawData() const
{
	return m_floatData[0][0];
}

Expression Matrix3x3::trace()
{
	return m_data[0][0] + m_data[1][1] + m_data[2][2];
}

Matrix3x3 Matrix3x3::identity()
{
	return Matrix3x3(Vec3(1.0f, 0.0f, 0.0f),
		Vec3(0.0f, 1.0f, 0.0f),
		Vec3(0.0f, 0.0f, 1.0f));
}

Matrix3x3 Matrix3x3::translate(float x, float y)
{
	return Matrix3x3(Vec3(1.0f, 0.0f, 0.0f),
		Vec3(0.0f, 1.0f, 0.0f),
		Vec3(x, y, 1.0f));
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& rhs) const
{
	Matrix3x3 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result[i][j] = (*this)[i][j] - rhs[i][j];
		}
	}
	return result;
}

Expression Matrix3x3::calculateDeterminant()
{
	return m_data[0][0] * Matrix2x2(Vec2(m_data[1][1], m_data[1][2]), Vec2(m_data[2][1], m_data[2][2])).calculateDeterminant()
		- m_data[1][0] * Matrix2x2(Vec2(m_data[0][1], m_data[0][2]), Vec2(m_data[2][1], m_data[2][2])).calculateDeterminant()
		+ m_data[2][0] * Matrix2x2(Vec2(m_data[0][1], m_data[0][2]), Vec2(m_data[1][1], m_data[1][2])).calculateDeterminant();
}

std::vector<Vec3> Matrix3x3::calculateEigenvectors()
{
	std::vector<Expression> eigenvalues;
	std::vector<Vec3> eigenvectors;

	Expression a = -1.0f;
	Expression b = trace();
	Expression c = - 0.5f * (trace() * trace() - ((*this) * (*this)).trace());
	Expression d = calculateDeterminant();

	Expression determinant = 18.0f * a * b * c * d - 4.0f * b * b * b * d + b * b * c * c - 4.0f * a * c * c * c - 27.0f * a * a * d * d;

	if ((float)determinant >= 0.0f) {
		eigenvalues.push_back((m_data[0][0] + m_data[1][1] + std::sqrt((float)determinant)) / 3.0f);
		eigenvalues.push_back((m_data[0][0] + m_data[1][1] - std::sqrt((float)determinant)) / 3.0f);
	}

	for (auto eigenvalue : eigenvalues) {
		std::cout << eigenvalue << "\n";
		Matrix3x3 matrix = eigenvalue * Matrix3x3::identity() - *this;
		Vec3 vector;
		AugmentedMatrix3x3 augmented(matrix, vector);
		augmented.reduceLeft();
		std::cout << augmented << "\n";
		Expression y = 1.0f;
		Expression x;
		Expression z;
		if (augmented.getLeft()[1][1] > 0.0001f || augmented.getLeft()[1][1] < -0.0001) {
			y = 0.0f;
		}
		if (augmented.getLeft()[0][0] > 0.0001f || augmented.getLeft()[0][0] < -0.0001) {
			x = -augmented.getLeft()[1][0] * y / augmented.getLeft()[0][0];
		}
		else { x = 1.0f; y = 0.0f; }
		eigenvectors.push_back(Vec3(x, y, z));
	}
	return eigenvectors;
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& rhs) const
{
	return Matrix3x3(Vec3(m_data[0][0] + rhs[0][0], m_data[0][1] + rhs[0][1], m_data[0][2] + rhs[0][2]),
		Vec3(m_data[1][0] + rhs[1][0], m_data[1][1] + rhs[1][1], m_data[1][2] + rhs[1][2]),
		Vec3(m_data[2][0] + rhs[2][0], m_data[2][1] + rhs[2][1], m_data[2][2] + rhs[2][2]));
}

Matrix3x3 operator*(const Matrix3x3& lhs, const Expression& rhs)
{
	return Matrix3x3(Vec3(lhs[0][0] * rhs, lhs[0][1] * rhs, lhs[0][2] * rhs),
		Vec3(lhs[1][0] * rhs, lhs[1][1] * rhs, lhs[1][2] * rhs),
		Vec3(lhs[2][0] * rhs, lhs[2][1] * rhs, lhs[2][2] * rhs));
}

Matrix3x3 operator*(const Expression& lhs, const Matrix3x3& rhs)
{
	return rhs * lhs;
}

Vec3 operator*(const Matrix3x3& lhs, const Vec3& rhs) {
	Vec3 result;
	for (int i = 0; i < 3; i++) {
		result[i] = dot(lhs.getRowVector(i), rhs);
	}
	return result;
}

Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs) {
	Matrix3x3 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result[i][j] = dot(lhs.getRowVector(j), rhs[i]);
		}
	}
	return result;
}