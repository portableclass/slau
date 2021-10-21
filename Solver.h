#pragma once

#include "Matrix.h"
#include "Decomposition.h"
#include <vector>

class Solver
{
private:
	// 0) Values:
	// ������� ������� (������� � [��. ��������])   || ��� ��� ��������� ����� ���������� � ������ Task 
	// ������ ����� (������ b [��. ��������])		|| � ������������ ����� Task c ������� Solver.
	//
	// ����� ������ �������� �������� ��� �� ������������� ������� ������������ ��� ������� � �������.
	// ����� ����� �������� ����, �������� ������ ������� ������� ������� ��� ����������� ������������� �������� ����������.
	// � ����� ������ ������������ ������ ���������� ������ � ������ ������ ������� LU �����������.

	Matrix A, b;
	/*std::vector <double> solveK;*/

public:
	// 1) �onstructors:
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

