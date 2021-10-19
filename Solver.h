#pragma once

#include "Matrix.h"
#include "Decomposition.h"
#include <vector>

class Solver
{
private:
	// 0) Values:
	// Матрица системы (матрица А [см. конспект])   || Эти два параметра можно определить в классе Task 
	// Правая часть (вектор b [см. конспект])		|| И Асоциировать класс Task c классом Solver.
	//
	// Такой подход позволит избавить нас от необходимости хранить декомпозицию или систему в солвере.
	// Можно также добавить флаг, хранящий способ задания матрицы системы или возможность инициализации объектом разложения.
	// А можно просто использовать объект разложения только в случае вызова солвера LU разложением.

	Matrix A;
	std::vector <double> b;

public:
	// 1) Сonstructors:
	Solver(const Matrix& any);

	// 2) Destructior:

	// 3) Geters and seters:

	// 4) Other methods:
	void outputMatrix();
	void outputDecomposition(const Decomposition& any);
	
};

