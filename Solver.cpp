#include "Solver.h"

// 1) Constructors:
Solver::Solver(const Matrix& any, const Matrix& vectorB)
{
    this->A = any;
    this->b = vectorB;
}
Solver::Solver(const Decomposition& any, const Matrix& vectorB)
{
    this->A = any.get_compactLU();
    this->b = vectorB;
}

void Solver::outputMatrix()
{
    unsigned int row = this->A.get_rSize();
    unsigned int col = this->A.get_cSize();

    std::cout << std::endl;
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            std::cout.width(6);
            std::cout << this->A.get_elem(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Solver::solveCramer() {

    unsigned int size = this->A.get_rSize();
    Matrix* a = new Matrix[size];
    const double bigDet = this->A.det();
    double* detI = new double[size];

    std::vector <double> x;
    x.resize(size);

    for (size_t i = 0; i < size; i++)
    {
        a[i] = this->A;
        a[i].set_column(i, this->b);
        detI[i] = a[i].det();
        x.at(i) = detI[i] / bigDet;
        std::cout << x.at(i) << std::endl;
    }
}

void Solver::solveLU()
{
    unsigned int size = this->A.get_rSize();
    Matrix L(size, size);
    Matrix U(size, size);
    Matrix y(size, this->b.get_cSize());
    Matrix x(size, this->b.get_cSize());

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (i < j)
                L.set_elem(i, j, 0);
            else if (i > j)
                L.set_elem(i, j, this->A.get_elem(i, j));
        }
        L.set_elem(i, i, 1);
    }

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (i <= j)
                U.set_elem(i, j, this->A.get_elem(i, j));
            else if (i > j)
                U.set_elem(i, j, 0);
        }
    }

    y = reverseMoveL(L);
    x = reverseMoveU(U, y);

    Solver p(x, L);
    p.outputMatrix();
}

Matrix Solver::reverseMoveL(const Matrix& any)
{
    Matrix input = any;
    unsigned int size = input.get_rSize();
    Matrix y(this->b.get_rSize(), this->b.get_cSize());

    y.set_elem(0, 0, this->b.get_elem(0, 0));

    for (size_t k = 1; k < size; k++)
    {
        y.set_elem(k, 0, this->b.get_elem(k, 0));
        for (size_t p = 0; p < k; p++)
            y.set_elem(k, 0, y.get_elem(k, 0) - input.get_elem(k, p) * y.get_elem(p, 0));
    }

    /*std::cout << "y "<< "\n";
    Solver e(y, input);
    e.outputMatrix();
    std::cout << "L " << "\n";
    Solver i(input, input);
    i.outputMatrix();*/

    return y;
}

Matrix Solver::reverseMoveU(const Matrix& any, const Matrix& vectorY)
{
    Matrix input = any;
    Matrix y = vectorY;
    int size = input.get_rSize() - 1;
    Matrix x(this->b.get_rSize(), this->b.get_cSize());

    x.set_elem(size, 0, y.get_elem(size, 0) / input.get_elem(size, size));

    for (int k = size - 1; k >= 0; k--)
    {
        x.set_elem(k, 0, y.get_elem(k, 0));
        for (int p = k + 1; p < size + 1; p++)
            x.set_elem(k, 0, x.get_elem(k, 0) - input.get_elem(k, p) * x.get_elem(p, 0));
        x.set_elem(k, 0, x.get_elem(k, 0) / input.get_elem(k, k));
    }

    /*std::cout << "x " << "\n";
    Solver e(x, input);
    e.outputMatrix();
    std::cout << "U " << "\n";
    Solver i(input, input);
    i.outputMatrix();*/

    return x;
}