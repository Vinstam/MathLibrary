#include "matrix.h"

LinearAlgebra::Matrix::Matrix() : rows(0), columns(0), matrix(nullptr){}

LinearAlgebra::Matrix::Matrix(int rows, int columns) : rows(rows), columns(columns)
{
	if (rows < 1 || columns < 1)
	{
		throw std::invalid_argument("Wrong value of rows/columns");
	}
	else
	{
		matrix = new double[rows * columns]();
	}
}

LinearAlgebra::Matrix::Matrix(const Matrix& other)
{
	rows = other.rows;
	columns = other.columns;
	memcpy(matrix, other.matrix, rows * columns * sizeof(double));
}

LinearAlgebra::Matrix::~Matrix()
{
	rows = columns = 0;
	delete[] matrix;
}

constexpr int LinearAlgebra::Matrix::getColumns() const noexcept
{
	return columns;
}
constexpr int LinearAlgebra::Matrix::getRows() const noexcept

{
	return rows;
}

double& LinearAlgebra::Matrix::operator()(const int& row, const int& col)
{
	if (row <= 0 || col <= 0 || row >= rows || col >= columns)
	{
		throw std::invalid_argument("Wrong value of rows/columns");
	}
	else
	{
		return matrix[row * columns + col];
	}
}

const double& LinearAlgebra::Matrix::operator()(const int& row, const int& col) const
{
	if (row <= 0 || col <= 0 || row >= rows || col >= columns)
	{
		throw std::invalid_argument("Wrong value of rows/columns");
	}
	else
	{
		return matrix[row * columns + col];
	}
	
}

LinearAlgebra::Matrix& LinearAlgebra::Matrix::operator=(const Matrix& other) noexcept
{
	if (this != &other) {
		rows = other.rows;
		columns = other.columns;

		delete[] matrix;
		matrix = new double[other.rows * other.columns];
		memcpy(matrix, other.matrix, rows * columns * sizeof(double));
	}

	return *this;
}

void LinearAlgebra::Matrix::setColumns(const int& col)
{
	if (col <= 0)
	{
		throw std::invalid_argument("Wrong value of col");
	}
	else
	{
		Matrix tmp(rows, col);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < std::min(col, columns); ++j)
			{
				tmp(i,j) = (*this)(i,j);
			}
		}
		columns = col;
		*this = tmp;
	}
}

void LinearAlgebra::Matrix::setRows(const int& row)
{
	if (row <= 0)
	{
		throw std::invalid_argument("Wrong value of row");
	}
	else
	{
		Matrix tmp(row, columns);
		for (int i = 0; i < std::min(row, rows); ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				tmp(i, j) = (*this)(i, j);
			}
		}
		rows = row;
		*this = tmp;
	}
}

bool LinearAlgebra::Matrix::isEqual(const Matrix& other) noexcept
{
	if (rows != other.rows || columns != other.columns)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				if ((*this)(i, j) != other(i, j))
				{
					return false;
				}
			}
		}
		return true;
	}
}

void LinearAlgebra::Matrix::sumMatrix(const Matrix& other)
{
	if (rows != other.rows || columns != other.columns)
	{
		throw std::invalid_argument("The wrong value of rows/cols");
	}
	else
	{
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				(*this)(i, j) += other(i, j);
			}
		}
	}
}

void LinearAlgebra::Matrix::subMatrix(const Matrix& other)
{
	if (rows != other.rows || columns != other.columns)
	{
		throw std::invalid_argument("The wrong value of rows/cols");
	}
	else
	{
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				(*this)(i, j) -= other(i, j);
			}
		}
	}
}

void LinearAlgebra::Matrix::mulNumber(const double& value) noexcept
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			(*this)(i, j) *= value;
		}
	}
}

void LinearAlgebra::Matrix::mulMatrix(const Matrix& other)
{
	if (columns != other.rows)
	{
		throw std::invalid_argument("The number of columns of first matrix is not equal to number of rows of second matrix");
	}
	else
	{
		Matrix tmp(rows, other.columns);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < other.columns; ++j)
			{
				for (int k = 0; k < columns; ++k)
				{
					tmp(i, j) += ((*this)(i,k) * (other(k,j)));
				}
			}
		}
		*this = tmp;

	}
}

bool LinearAlgebra::Matrix::operator==(const Matrix& other) noexcept
{
	return isEqual(other);
}

bool LinearAlgebra::Matrix::operator!=(const Matrix& other) noexcept
{
	return !isEqual(other);
}

LinearAlgebra::Matrix& LinearAlgebra::Matrix::operator+=(const Matrix& other)
{
	sumMatrix(other);
	return *this;
}

LinearAlgebra::Matrix& LinearAlgebra::Matrix::operator-=(const Matrix& other)
{
	subMatrix(other);
	return *this;
}

LinearAlgebra::Matrix& LinearAlgebra::Matrix::operator*=(const double& value) noexcept
{
	mulNumber(value);
	return *this;
}

LinearAlgebra::Matrix& LinearAlgebra::Matrix:: operator *=(const Matrix& other)
{
	mulMatrix(other);
	return *this;
}


LinearAlgebra::Matrix LinearAlgebra::Matrix::operator+(const Matrix& other) const
{
	Matrix result(*this);
	result.sumMatrix(other);
	return result;
}

LinearAlgebra::Matrix LinearAlgebra::Matrix::operator-(const Matrix& other) const
{
	Matrix result(*this);
	result.subMatrix(*this);
	return result;
}

LinearAlgebra::Matrix LinearAlgebra::Matrix::operator*(const Matrix& other) const
{
	Matrix result(*this);
	result.mulMatrix(other);
	return result;
}

LinearAlgebra::Matrix LinearAlgebra::Matrix::operator*(const double& value) const noexcept
{
	Matrix result(*this);
	result.mulNumber(value);
	return result;
}
