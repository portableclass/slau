#include "Solver.h"

// 1) Constructors:
Solver::Solver(const Matrix& any, const Matrix& vectorB) 
{
    this->A = any;
    this->b = vectorB;
}
Solver::Solver(const Decomposition& any, const Matrix& vectorB)
{
    this->L = any.get_L();
    this->U = any.get_U();
    this->A = any.get_compactLU();
    this->b = vectorB;
}

// 2) Destructior:
Solver::~Solver() {}

// 3) Geters and seters:

// 4) Other methods:
Matrix Solver::solveCramer() {
    if (this->A.det() != 0) {
        const double bigDet = this->A.det();
        const unsigned int size = this->A.get_rSize();
        double* detI = new double[size];
        Matrix* arrayA = new Matrix[size];
        Matrix x(this->b.get_rSize(), this->b.get_cSize());

        for (size_t i = 0; i < size; i++)
        {
            arrayA[i] = this->A;
            arrayA[i].set_column(i, this->b);
            detI[i] = arrayA[i].det();
            x.set_elem(i, 0, detI[i] / bigDet);
        }

        return x;
    }
    else {
        std::cout << "ERROR! The determinant of the matrix A must be non-zero.";
        return Matrix();
    }
}

Matrix Solver::solveLU()
{
    if (this->A.get_elem(0, 0) == 0) {
        // required = the number of the row in which A[required][0] != 0 
        unsigned int required;
        for (required = 1; required < this->A.get_rSize(); required++)
        {
            if (this->A.get_elem(required, 0) != 0) {
                double temp;
                for (size_t col = 0; col < this->A.get_cSize(); col++)
                {
                    temp = this->A.get_elem(required, col);
                    this->A.set_elem(required, col, this->A.get_elem(required + 1, col));
                    this->A.set_elem(required + 1, col, temp);
                }
                break;
            }
        }
    }

    const unsigned int size = this->A.get_rSize();
    Matrix y(this->b.get_rSize(), this->b.get_cSize());
    Matrix x(this->b.get_rSize(), this->b.get_cSize());

    // reverse move for matrix L
    y.set_elem(0, 0, this->b.get_elem(0, 0));
    for (size_t k = 1; k < this->L.get_rSize(); k++)
    {
        y.set_elem(k, 0, this->b.get_elem(k, 0));
        for (size_t p = 0; p < k; p++)
            y.set_elem(k, 0, y.get_elem(k, 0) - this->L.get_elem(k, p) * y.get_elem(p, 0));
    }

    // reverse move for matrix U
    const unsigned int sizeForX = this->U.get_rSize() - 1;
    x.set_elem(sizeForX, 0, y.get_elem(sizeForX, 0) / this->U.get_elem(sizeForX, sizeForX));
    for (int k = sizeForX - 1; k >= 0; k--)
    {
        x.set_elem(k, 0, y.get_elem(k, 0));
        for (size_t p = k + 1; p < sizeForX + 1; p++)
            x.set_elem(k, 0, x.get_elem(k, 0) - this->U.get_elem(k, p) * x.get_elem(p, 0));
        x.set_elem(k, 0, x.get_elem(k, 0) / this->U.get_elem(k, k));
    }

    return x;
}