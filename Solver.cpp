#include "Solver.h"

// 1) Constructors:
Solver::Solver(const Matrix& any, const Matrix& vectorB)
{
    this->A = any;
    this->b = vectorB;
}
Solver::Solver(const Decomposition& any, const Matrix& vectorB)
{
    //this->A = Matrix(any.get_size(), any.get_size());
    //this->A.set_elem(0, 0, 2);
    //this->A.set_elem(0, 1, 1);
    //this->A.set_elem(0, 2, 1);
    //this->A.set_elem(1, 0, 1);
    //this->A.set_elem(1, 1, -1);
    //this->A.set_elem(1, 2, 0);
    //this->A.set_elem(2, 0, 3);
    //this->A.set_elem(2, 1, -1);
    //this->A.set_elem(2, 2, 2);
    this->A = any.get_LU();
    this->b = vectorB;
}

//const std::vector <double> Solver::get_solveK() const
//{
//    return this->solveK;
//}

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
    int n = this->A.get_rSize();
    Matrix* a = new Matrix[n];
    double* detI = new double[n];
    double* solveK = new double[n];
    double bigDet = this->A.det();

    for (int i = 0; i < n; i++)
    {
        a[i] = this->A;
        // error there
        a[i].set_column(i, this->b);
        detI[i] = a[i].det();
    }

    for (int i = 0; i < n; i++)
    {
        solveK[i] = detI[i] / bigDet;
        std::cout << solveK[i] << "\n";
    }

}

void Solver::solveLU()
{
    unsigned int size = this->A.get_rSize();
    Matrix L(size, size);
    Matrix U(size, size);
    Matrix invL(size, size);
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

    invL = inverseMatrix(L);
    y = invL * this->b;
    x = inverseMatrix(U) * y;

    Solver p(x, L);
    p.outputMatrix();
}

Matrix Solver::inverseMatrix(const Matrix& any)
{
    Matrix input = any;

    int size = input.get_rSize();
    // Единичная матрица (искомая обратная матрица)
    Matrix x(size, size);
    // Общая матрица, получаемая скреплением Начальной матрицы и единичной
    Matrix result(size, 2 * size);

    if (input.det() != 0)
    {
        for (int i = 0; i < size; i++)
            x.set_elem(i, i, 1);

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
            {
                result.set_elem(i, j, input.get_elem(i, j));
                result.set_elem(i, j + size, x.get_elem(i, j));
            }

        // Прямой ход (Зануление нижнего левого угла)
        for (int k = 0; k < size; k++)
        {
            for (int i = 0; i < 2 * size; i++)
                result.set_elem(k, i, result.get_elem(k, i) / input.get_elem(k, k));
            for (int i = k + 1; i < size; i++)
            {
                double K = result.get_elem(i, k) / result.get_elem(k, k); 
                for (int j = 0; j < 2 * size; j++)
                    result.set_elem(i, j, result.get_elem(i, j) - result.get_elem(k, j) * K);
            }
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    input.set_elem(i, j, result.get_elem(i, j));
        }

        // Обратный ход (Зануление верхнего правого угла)
        for (int k = size - 1; k > -1; k--)
        {
            for (int i = 2 * size - 1; i > -1; i--) 
                result.set_elem(k, i, result.get_elem(k, i) / input.get_elem(k, k));
            for (int i = k - 1; i > -1; i--)
            {
                double K = result.get_elem(i, k) / result.get_elem(k, k);
                for (int j = 2 * size - 1; j > -1; j--)
                    result.set_elem(i, j, result.get_elem(i, j) - result.get_elem(k, j) * K);
            }
        }

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                x.set_elem(i, j, result.get_elem(i, j + size));

        /*std::cout << "00000000000000000" << "\n";
        Solver y(result, input);
        y.outputMatrix();
        std::cout << "11111111111111111" << "\n";
        Solver e(x, input);
        e.outputMatrix();*/
    }

    return x;
}