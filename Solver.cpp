#include "Solver.h"

// 1) Constructors:
Solver::Solver(const Matrix& any)
{
    unsigned int size = any.get_cSize();
    this->A = any;
}

void Solver::outputMatrix()
{
    unsigned int size = this->A.get_cSize();

    std::cout << std::endl;
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            std::cout.width(6);
            std::cout << this->A.get_elem(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Solver::outputDecomposition(const Decomposition& any)
{
    unsigned int size = any.get_size();
    Matrix result(size, size);

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (i < j)
                result.set_elem(i, j, any.get_U().get_elem(i, j));
            else if (i > j)
                result.set_elem(i, j, any.get_L().get_elem(i, j));
        }
        result.set_elem(i, i, any.get_U().get_elem(i, i));
    }

    std::cout << std::endl;
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            std::cout.width(6);
            std::cout << result.get_elem(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
