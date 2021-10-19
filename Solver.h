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

	Matrix A;
	std::vector <double> b;

public:
	// 1) �onstructors:
	Solver(const Matrix& any);

	// 2) Destructior:

	// 3) Geters and seters:

	// 4) Other methods:
	void outputMatrix();
	void outputDecomposition(const Decomposition& any);
	
};

