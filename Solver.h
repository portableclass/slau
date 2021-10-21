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

	Matrix A, b;
	/*std::vector <double> solveK;*/

public:
	// 1) Сonstructors:
	Solver(const Matrix& any, const Matrix& vectorB);
	Solver(const Decomposition& any, const Matrix& vectorB);

	// 2) Destructior:

	// 3) Geters and seters:
	//const std::vector <double> get_solveK() const;
	// 4) Other methods:
	void outputMatrix();
	void solveCramer();
	void solveLU();
	Matrix inverseMatrix(const Matrix& any);


};

