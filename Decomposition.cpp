#include "Decomposition.h"
#include <cassert>


// 1) Constructors:
Decomposition::Decomposition(const Matrix& any)
{
    // 0. Checking of sizes. If matrix isn't square then error out!
    assert((any.get_cSize() == any.get_rSize()) && "ERROR_MATRIX_IS_NOT_SQUARE");
    // assert((any.get_cSize() == 0) && "ERROR_MATRIX_IS_EMPTY");

    // 1. The data is set there:
    this->size = any.get_cSize();
    this->values = { 10.0, -0.1, 1.0, 10.1 };   //  <- Заменить на LU разложение
    // По умолчанию: (L\U) = { 10.0, -0.1, 1.0, 10.1 } - LU разложение для матрицы А = {10.0, -1.0, 1.0, 10.0}

    Matrix result, U, L;
    double temp;
    double temp1;
    double temp2;

    for (int i = 0; i < this->size; i++)
    {
        for (int j = 0; j < this->size; j++)
        {
            U.set_elem(i, j, 0);
            L.set_elem(i, j, 0);
        }
        L.set_elem(i, i, 1);
    }

    for (int i = 0; i < this->size; i++)
    {
        for (int j = 0; j < this->size; j++)
        {
            temp = 0;

            if ( i <= j )
            {
                for (size_t k = 0; k < (i - 1); k++)
                {
                    temp += L.get_elem(i, j) * U.get_elem(k, j);
                }
                U.set_elem(i, j, any.get_elem(i, j) - temp);
            } 
            else if ( i > j )
            {
                for (size_t k = 0; k < (j - 1); k++)
                {
                    temp += L.get_elem(i, j) * U.get_elem(k, j);
                }
                L.set_elem(i, j, (any.get_elem(i, j) - temp) / U.get_elem(j, j));
            }

        }
    }

    

    /*result.set_elem(0, 0, U.get_elem(0, 0));
    result.set_elem(0, 1, L.get_elem(0, 1));
    result.set_elem(1, 0, U.get_elem(1, 0));
    result.set_elem(1, 1, U.get_elem(1, 1));*/

    std::cout << std::endl;
    std::cout << "sorce" << std::endl;
    for (int i = 0; i < any.get_rSize(); i++)
    {
        for (int j = 0; j < any.get_cSize(); j++)
            std::cout << any.get_elem(i, j) << " ";
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "LU" <<std::endl;
    for (int i = 0; i < result.get_rSize(); i++)
    {
        for (int j = 0; j < result.get_cSize(); j++)
            std::cout << result.get_elem(i, j) << " ";
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "L" << std::endl;
    for (int i = 0; i < L.get_rSize(); i++)
    {
        for (int j = 0; j < L.get_cSize(); j++)
            std::cout << L.get_elem(i, j) << " ";
        std::cout << std::endl;
    }
    

    std::cout << std::endl;
    std::cout << "U" << std::endl;
    for (int i = 0; i < U.get_rSize(); i++)
    {
        for (int j = 0; j < U.get_cSize(); j++)
            std::cout << U.get_elem(i, j) << " ";
        std::cout << std::endl;
    }

}


// 2) Destructor:
Decomposition::~Decomposition()
{
    this->values.clear();
    this->values.shrink_to_fit();
}


// 3) Geters and seters:
const double Decomposition::get_elemL(unsigned int row, unsigned int col) const
{
    // 0. Checking of the indexes!
    assert(((row < this->size) && (col < this->size)) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");

    return 0.0;
}

const double Decomposition::get_elemU(unsigned int row, unsigned int col) const
{
    // 0. Checking of the indexes!
    assert(((row < this->size) && (col < this->size)) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");

    return 0.0;
}

const double Decomposition::get_size() const
{
    return this->size;
}

const Matrix Decomposition::get_L() const
{
    return Matrix();
}

const Matrix Decomposition::get_U(const Matrix& any) const
{
    return Matrix();
}
