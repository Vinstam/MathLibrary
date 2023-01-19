#ifndef MATRIX
#define MATRIX
#include <stdexcept>

namespace LinearAlgebra
{
	
	class Matrix
	{
	private:
		int rows,columns;
		double* matrix;
	public:
		Matrix();
		Matrix(int rows, int columns);
		Matrix(const Matrix& other);
		~Matrix();

		constexpr int getColumns() const noexcept;
		constexpr int getRows() const noexcept;

		double& operator()(const int& row, const int& col);
		const double& operator()(const int& row, const int& col) const;

		Matrix& operator=(const Matrix& other) noexcept;

		void setColumns(const int& col);
		void setRows(const int& row);

		bool isEqual(const Matrix& other) noexcept;
		void sumMatrix(const Matrix& other);
		void subMatrix(const Matrix& other);
		void mulMatrix(const Matrix& other);
		void mulNumber(const double& value) noexcept;


		bool operator==(const Matrix& other) noexcept;
		bool operator!=(const Matrix& other) noexcept;
		Matrix& operator+=(const Matrix& other);	
		Matrix& operator-=(const Matrix& other);
		Matrix& operator*=(const double& value) noexcept;
		Matrix& operator*=(const Matrix& other);

		Matrix operator+(const Matrix& other) const;
		Matrix operator-(const Matrix& other) const;
		Matrix operator*(const Matrix& other) const;
		Matrix operator*(const double& value) const noexcept;

	}; // LinearAlgebra

}

#endif // MATRIX