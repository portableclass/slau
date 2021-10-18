#include "Matrix.h"
#include <cassert>

// -1) The private geter gets a linear index:
unsigned int Matrix::get_index(unsigned int row, unsigned int col) const
{
	// n = i - 1 + (j - 1) * rown    в случае, если i in [1, rown], а j in [1, coln]  =>
	// => return row - 1 + (col - 1) * this->rown;
	// n = i + j * rown		в случае, если i in [0, rown-1], а j in [0, coln-1] =>
	// => return row + col * this->rown;
	// Смотри подробное описание в exel файле задания.
	
	//assert((col < this->coln) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE"); // assert(bool = true)
	//assert((row < this->rown) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");

	return row + col * this->rown;
}

// 1) Сonstructors:
Matrix::Matrix() : values({ 10.0, -1.0, 1.0, 10.0 }), rown(2), coln(2) {}

Matrix::Matrix(unsigned int rown, unsigned int coln) : coln(coln), rown(rown), values(coln * rown) {}

// 2) Destructior:
Matrix::~Matrix()
{
	values.clear();
	values.shrink_to_fit();
}


// 3) Geters and seters:
const unsigned int Matrix::get_rSize() const
{
	return this->rown;
}

const unsigned int Matrix::get_cSize() const
{
	return this->coln;
}

const double Matrix::get_elem(unsigned int row, unsigned int col) const
{
	// 0. Checking of the indexes:
	assert(((row < this->rown) && (col < this->coln)) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");

	return this->values.at(get_index(row, col));
}

void Matrix::set_elem(unsigned int row, unsigned int col, const double value)
{
	// 0. Checking of the indexes:
	assert(((row < this->rown) && (col < this->coln)) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");

	this->values.insert(this->values.begin() + get_index(row, col), value);
}

void Matrix::set_column(unsigned int col, const Matrix& column)
{
	// 0. Checking of the indexes:
	assert((col < this->coln) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");
	assert((column.rown == this->rown) && "ERROR_MATRIXES_SIZES_SHOULD_BE_EQUAL");
	assert((column.coln == 1) && "ERROR_MATRIX_SHOULD_BE_A_COLUMN");

	// 1. The column is inserted there:
	this->values.insert(this->values.begin() + col * this->rown, column.values.begin(), column.values.end());
}

const double Matrix::det() const
{
	return 0.0;
}

const double Matrix::norm() const
{
	double value_max = std::abs(this->get_elem(0, 0));

	for (size_t col = 0; col < this->get_cSize(); col++) {
		for (size_t row = 0; row < this->get_rSize(); row++) {
			value_max = std::max(value_max, std::abs(this->get_elem(row, col)));
		}
	}

	return value_max;
}

Matrix& Matrix::operator=(const Matrix& Any)
{
	// Использование перегрузки опреатора Matrix& Matrix::operator=(const Matrix& Any),
	// возвращающего ссылку на объект, а не объект, позволяет выполнять цепочку присвоений!
	//
	// Для того, чтобы вернуть ссылку на объект, определяемый в теле используйте return *this;

	// 0. Проверка на самоприсвоение.
	// Чтобы не выполнять лишнее копирование.
	// Возвращает ссылку на текщий объект.
	if (this == &Any)
	{
		return *this;
	}

	// 1. The copying of the object values:
	this->coln = Any.coln;
	this->rown = Any.rown;
	this->values = Any.values;

	return *this;
}

Matrix operator+(const Matrix& left, const Matrix& right)
{
	// 0. Checking of the sizes:
	assert((left.get_cSize() == right.get_cSize()) && "ERROR_MATRIXES_SIZES_SHOULD_BE_EQUAL");
	assert((left.get_rSize() == right.get_rSize()) && "ERROR_MATRIXES_SIZES_SHOULD_BE_EQUAL");
	assert((left.get_cSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");
	assert((left.get_rSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");

	// 1. The matrix result is created there:
	Matrix result(left.get_rSize(), left.get_cSize());

	for (size_t j = 0; j < right.get_cSize(); j++)
	{
		for (size_t i = 0; i < right.get_rSize(); i++)
		{
			result.set_elem(i, j, left.get_elem(i, j) + right.get_elem(i, j));
		}
	}

	return result;
}

Matrix operator-(const Matrix& left, const Matrix& right)
{
	// 0. Checking of the sizes:
	assert((left.get_cSize() == right.get_cSize()) && "ERROR_MATRIXES_SIZES_SHOULD_BE_EQUAL");
	assert((left.get_rSize() == right.get_rSize()) && "ERROR_MATRIXES_SIZES_SHOULD_BE_EQUAL");
	assert((left.get_cSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");
	assert((left.get_rSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");

	return Matrix();
}

Matrix operator*(const Matrix& left, const Matrix& right)
{
	// 0. Checking of the sizes:
	assert((left.get_cSize() == right.get_cSize()) && "ERROR_MATRIXES_SIZES_SHOULD_BE_EQUAL");

	Matrix result;	

	for (size_t i = 0; i < left.get_rSize(); i++) {
		for (size_t j = 0; j < right.get_cSize(); j++) {
			result.set_elem(j, i, 0);
			for (size_t k = 0; k < left.get_cSize(); k++) {
				result.set_elem(j, i, (result.get_elem(j, i) + (left.get_elem(j, k) * right.get_elem(k, i))));
			}
		}
	}

	return result;
}



//Matrix operator*(const Matrix& left, const Matrix& right)
//{
//	// 0. Checking of the sizes:
//	assert((left.get_cSize() == right.get_cSize()) && "ERROR_MATRIXES_SIZES_SHOULD_BE_EQUAL");
//
//	Matrix result;
//
//	for (size_t i = 0; i < left.get_rSize(); i++) {
//		for (size_t j = 0; j < right.get_cSize(); j++) {
//			result.set_elem(i, j, 0);
//			for (size_t k = 0; k < left.get_cSize(); k++) {
//				std::cout << "iter num i:" << i << std::endl;
//				std::cout << "iter num j:" << j << std::endl;
//				std::cout << result.get_elem(i, j) << " += "; std::cout << left.get_elem(i, k) << " * "; std::cout << right.get_elem(k, j) << " = ";
//				result.set_elem(i, j, (result.get_elem(i, j) + (left.get_elem(i, k) * right.get_elem(k, j))));
//				std::cout << result.get_elem(i, j) << std::endl;
//			}
//		}
//	}
//
//
//
//	return result;
//}


//Matrix operator*(const Matrix& left, const Matrix& right) {// 0. Checking of the sizes:
//	assert((left.get_cSize() == right.get_rSize()) && "ERROR_NUMBERS_LEFT_MATRIX_COLUMNS_AND_RIGHT_MATRIX_ROWS_SHOULD_BE_EQUAL");
//	assert((left.get_cSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");
//	assert((left.get_rSize() != 0) && (right.get_cSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");
//
//	Matrix result(left.get_rSize(), right.get_cSize());
//
//	for (size_t col = 0; col < right.get_cSize(); col++)
//	{
//		for (size_t row = 0; row < left.get_rSize(); row++) {
//			result.set_elem(row, col, 0);
//			for (size_t i = 0; i < left.get_cSize(); i++)
//			{
//				result.set_elem(row, col, result.get_elem(row, col) + left.get_elem(row, i) * right.get_elem(i, col));
//				// add(result, row, col, left.get_elem(row, i) * right.get_elem(i, col));
//			}
//		}
//	}
//	return result;
//}