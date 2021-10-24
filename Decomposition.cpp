#include "Decomposition.h"
#include <cassert>


// 1) Constructors:
Decomposition::Decomposition(const Matrix& any)
{
    // 0. Checking of sizes. If matrix isn't square then error out!
    assert((any.get_cSize() == any.get_rSize()) && "ERROR_MATRIX_IS_NOT_SQUARE");
    assert((any.get_cSize() != 0) && "ERROR_MATRIX_IS_EMPTY");

    // По умолчанию: (L\U) = { 10.0, -0.1, 1.0, 10.1 } - LU разложение для матрицы А = {10.0, -1.0, 1.0, 10.0}

    const unsigned int size = any.get_cSize();
    this->LU = Matrix(size, size);

    Matrix L(size, size);
    Matrix U(size, size);
    double temp;

    // Zeroing of Matrix elements U and L. Setting the value 1 to the main diagonal of the Matrix L
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            U.set_elem(i, j, 0);
            L.set_elem(i, j, 0);
        }
        L.set_elem(i, i, 1);
    }

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            temp = 0;

            if (i <= j)
            {
                // Determination of the elements of the Matrix U
                for (size_t k = 0; k < i; k++)
                    temp += L.get_elem(i, k) * U.get_elem(k, j);
                U.set_elem(i, j, any.get_elem(i, j) - temp);
            }
            else
            {
                // Determination of the elements of the Matrix L
                for (size_t k = 0; k < i; k++)
                    temp += L.get_elem(i, k) * U.get_elem(k, j);
                L.set_elem(i, j, (any.get_elem(i, j) - temp) / U.get_elem(j, j));
            }

        }
    }

    // Writing the LU Matrix in compact form
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (i < j)
                this->LU.set_elem(i, j, U.get_elem(i, j));
            else if (i > j)
                this->LU.set_elem(i, j, L.get_elem(i, j));
        }
        this->LU.set_elem(i, i, U.get_elem(i, i));
    }

    /*std::cout << std::endl;
    std::cout << "source" << std::endl;
    for (int i = 0; i < any.get_rSize(); i++)
    {
        for (int j = 0; j < any.get_cSize(); j++)
            std::cout << any.get_elem(i, j) << " ";
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "comp" << std::endl;
    for (int i = 0; i < this->LU.get_rSize(); i++)
    {
        for (int j = 0; j < this->LU.get_cSize(); j++)
            std::cout << this->LU.get_elem(i, j) << " ";
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
    }*/

}


// 2) Destructor:
Decomposition::~Decomposition() {}


// 3) Geters and seters:
const double Decomposition::get_elemL(unsigned int row, unsigned int col) const
{
    // 0. Checking of the indexes!
    assert(((row < get_size()) && (col < get_size())) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");

    return get_L().get_elem(row, col);
}

const double Decomposition::get_elemU(unsigned int row, unsigned int col) const
{
    // 0. Checking of the indexes!
    assert(((row < get_size()) && (col < get_size())) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");

    return get_U().get_elem(row, col);
}

const double Decomposition::get_size() const
{
    return this->LU.get_cSize();
}

const Matrix Decomposition::get_L() const
{
    Matrix L(get_size(), get_size());

    for (size_t i = 0; i < get_size(); i++)
    {
        for (size_t j = 0; j < get_size(); j++)
        {
            if (i < j)
                L.set_elem(i, j, 0);
            else if (i > j)
                L.set_elem(i, j, this->LU.get_elem(i, j));
        }
        L.set_elem(i, i, 1);
    }

    /*unsigned int size = L.get_cSize();

    std::cout << std::endl;
    std::cout << "L" << std::endl;
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            std::cout.width(6);
            std::cout << L.get_elem(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;*/

    return L;
}

const Matrix Decomposition::get_U() const
{
    Matrix U(get_size(), get_size());

    for (size_t i = 0; i < get_size(); i++)
    {
        for (size_t j = 0; j < get_size(); j++)
        {
            if (i <= j)
                U.set_elem(i, j, this->LU.get_elem(i, j));
            else if (i > j)
                U.set_elem(i, j, 0);
        }
    }

    unsigned int size = U.get_cSize();

    /*std::cout << std::endl;
    std::cout << "U" << std::endl;
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            std::cout.width(6);
            std::cout << U.get_elem(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;*/

    return U;
}

const Matrix Decomposition::get_compactLU() const
{
    return this->LU;
}