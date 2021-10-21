// Practical_work_5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Solver.h"

//#define NDEBUG 

int main()
{
    // В релизной версии программы необходимо отключить все макросы проверки (assert).
    // Все провеки, связанные с загрузкой матрицы из файла и корректности размеров,
    // должны быть явно реализованы в main. Релизная версия программы всегда должна завершаться
    // с кодом 0. Другой код, свидетельствующий об ошибке,в отлаженной программе возникать не должен.
    // 
    // Отключить все макросы необходимо добавив дерективу дял препроцессора в этом файле.
    // Добавление директивы пропусти добавление всех строк содержащих assert.

    /*Matrix o;
    Matrix i;
    Matrix result = o * i;

    std::cout << "Matrix mul:" << std::endl;
    for (int i = 0; i < result.get_rSize(); i++)
    {
        for (int j = 0; j < result.get_cSize(); j++)
            std::cout << result.get_elem(i, j) << " ";
        std::cout << std::endl;
    }*/

    Matrix a(3, 3);

    a.set_elem(0, 0, 2);
    a.set_elem(0, 1, 1);
    a.set_elem(0, 2, 1);
    a.set_elem(1, 0, 1);
    a.set_elem(1, 1, -1);
    a.set_elem(1, 2, 0);
    a.set_elem(2, 0, 3);
    a.set_elem(2, 1, -1);
    a.set_elem(2, 2, 2);

    Matrix b(3, 1);

    b.set_elem(0, 0, 2);
    b.set_elem(1, 0, -2);
    b.set_elem(2, 0, 2);

    Solver x(a, b);
    Decomposition LU(a);
    Solver y(LU, b);

    std::cout << "Default Matrix: " << std::endl;
    x.outputMatrix();
    std::cout << "LU decomposition written in compact form: " << std::endl;
    y.outputMatrix();

    Solver g(LU, b);

    std::cout << "cramer by daun seraphim: " << std::endl;
    x.solveCramer();

    std::cout << "LU by daun Lexa: " << std::endl;
    g.solveLU();

    return 0;
}