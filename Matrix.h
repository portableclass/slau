#pragma once
//���������������� ���(�����);
//���������� ������ :
//	����� ��������� �������� �������;
//	����� ���������� ������ ������
//	�������� ���������� ������������ det();
//	����� ������ �������;
//	��������� �����;
//	��������� ��������;
//	��������� ������������;
//	���������� �������.

#include <iostream>
#include <vector>

class Matrix
{
private:
	// -1) The private geter gets a linear index:
	unsigned int get_index(unsigned int row, unsigned int col) const;	// ������ ������� ������� ���� ����� ���������?
	// ����� ������ ��������� ������ ���������� �������� � ���� ��������� �������.
	// � ������, ���� ������ �������� �� ����� ���� �������� ��������, �� ���������� ������� � ��������� ������
	// �������� �� �����!

	// 0) Values:
	std::vector <double> values;	// ������ �������� (������� ����� �������� ��� ������������������ ��������)
	unsigned int rown;				// ���������� �����
	unsigned int coln;				// ���������� ��������
public:
	// 1) �onstructors:
	Matrix();
	Matrix(unsigned int rown, unsigned int coln); // �������������� ������� �� ��������� �������� �������� (����������� ������)

	// 2) Destructior:
	~Matrix();

	// 3) Geters and seters:
	const unsigned int get_rSize() const;
	const unsigned int get_cSize() const;
	const double get_elem(unsigned int row, unsigned int col) const;
	void set_elem(unsigned int row, unsigned int col, const double value);
	void set_column(unsigned int col, const Matrix& column); // ������ �������� ������� ������

	// 4) Other methods:
	const double det() const;
	const double norm() const;

	// 5) Operathors:
	// �������� ���������� ����������.
	// = ��������� (����� ����� ������)
	// + ��������� (���������� ����� �������)
	// -		   (���������� ����� �������)
	// *		   (���������� ����� �������)
	// ������������� ���������� ���������� ����� ������� ��������� �������� ������ �� ���������.
	// ��� ����������� ���� ��������� ������� ���������� ���������� �� ������� ���� ������.

	Matrix& operator=(const Matrix& Any); // ������� �� Matrix operator=(const Matrix& Any); ������ � ����
	// �������� = ����� ����������� ����� ����� ������. ��� ��������� ���, �������� ������������ ������� ��������� this
	// �� ������ ������� ����� �� ���������.
	// ��������� +=, -= � �.�. ���� ����� ����������� ����� ������ ������.
};

Matrix operator+(const Matrix& left, const Matrix& right);	// ���������� �� ���� ������, �������� ������ �� ���������.
Matrix operator-(const Matrix& left, const Matrix& right);	// ��� ���������� +,-,/, ���� ���� �����������, ����� ������������
Matrix operator*(const Matrix& left, const Matrix& right);	// ���������� ����� �������, ��� � ������ �������.