#pragma once

#include "Matrix.h"
#include "Decomposition.h"

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

	Matrix A, b, L, U;
	/*std::vector <double> solveK;*/

public:
	// 1) �onstructors:
	Solver(const Matrix& any, const Matrix& vectorB);
	Solver(const Decomposition& any, const Matrix& vectorB);

	// 2) Destructior:
	~Solver();

	// 3) Geters and seters:

	// 4) Other methods:
	Matrix solveCramer();
	Matrix solveLU();
};

