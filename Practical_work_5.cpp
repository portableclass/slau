// Practical_work_5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Solver.h"
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cassert>

#define NDEBUG

const Matrix read(std::string fullway2data);
void print(const Matrix& Any, unsigned int precicion);

int main()
{
    // std::string fullway2data = "C:\\Users\\YASH\\Downloads\\Файлы программы\\input.txt";

    std::string fullway2data = /* enter the path to the file */;
    Matrix A = read(fullway2data);
    Matrix x_exist(A.get_cSize(), 1);

    // filling x_exist with values from 1 to the number of columns of matrix A
    unsigned int temp = 0;
    for (size_t i = 0; i < x_exist.get_rSize(); i++)
    {
        temp = i + 1;
        x_exist.set_elem(i, 0, temp);
    }

    // setting the values of the vector of the right part
    Matrix b = A * x_exist;

    Solver cramer_A(A, b);
    Decomposition decA(A);
    Solver LU_A(decA, b);

    std::cout << std::endl;
    std::cout << "Cramer: " << std::endl;
    Matrix x_Cramer = cramer_A.solveCramer();
    print(x_Cramer, 16);

    std::cout << std::endl;
    std::cout << "LU: " << std::endl;
    Matrix x_LU = LU_A.solveLU();
    print(x_LU, 16);

    const double normCramer = (x_exist - x_Cramer).norm();
    const double normLU = (x_exist - x_LU).norm();
    const double accuracy = (x_Cramer - x_LU).norm();

    std::cout << std::endl;
    std::cout << "1) ||x_exist - x_Cramer || = " << normCramer << std::endl;
    std::cout << "2) ||x_exist - x_LU || = " << normLU << std::endl;
    std::cout << "3) ||x_Cramer - x_LU || = " << accuracy << std::endl;

    return 0;
}

// LOCAL FUNS
const Matrix read(std::string fullway2data)
{
    std::ifstream inputfile;
    inputfile.open(fullway2data);

    Matrix Res;

    if (inputfile.is_open())
    {
        std::string buff_s;
        double buff_d;
        std::vector <std::vector<double>> buff_data;
        std::vector <double> buff_data_row;

        while (getline(inputfile, buff_s))
        {
            std::istringstream buff_ss(buff_s);

            while (buff_ss >> buff_d)
            {
                buff_data_row.push_back(buff_d);
            }

            buff_data.push_back(buff_data_row);
            buff_data_row.clear();
        }

        Res = Matrix(buff_data.size(), buff_data.at(0).size());

        for (size_t row = 0; row < Res.get_rSize(); row++)
        {
            assert((buff_data.at(row).size() == Res.get_cSize()) && "ERROR_COPIED_MATRIX_COLUMNS_SIZES_SHOULD_BE_EQUAL");

            if (buff_data.at(row).size() != Res.get_cSize())
            {
                std::cout << "ERROR: copying matrix is failed! Process was stopped!" << std::endl;

                return Res;
            }

            for (size_t col = 0; col < Res.get_cSize(); col++)
            {
                Res.set_elem(row, col, buff_data.at(row).at(col));
            }
        }
    }
    else
    {
        std::cout << "ERROR: copying matrix is failed! File isn't opened!" << std::endl;
    }

    return Res;
}

void print(const Matrix& Any, unsigned int precicion)
{
    if ((Any.get_rSize() == 0) || (Any.get_cSize() == 0))
    {
        std::cout << "WARNING: printed matrix is empty!" << std::endl;
    }

    for (size_t i = 0; i < Any.get_rSize(); i++)
    {
        for (size_t j = 0; j < Any.get_cSize(); j++)
        {
            std::cout << std::setprecision(precicion) << std::scientific << Any.get_elem(i, j) << "		";
        }
        std::cout << std::endl;
    }
}