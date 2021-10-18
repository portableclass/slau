// Practical_work_5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Decomposition.h"
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

    Matrix a;
    Matrix b;
    //Matrix result = a * b;

    //std::cout << "Matrix mul:" << std::endl;
    //for (int i = 0; i < result.get_rSize(); i++)
    //{
    //    for (int j = 0; j < result.get_cSize(); j++)
    //        std::cout << result.get_elem(i, j) << " ";
    //    std::cout << std::endl;
    //}

    Decomposition c = a;

    return 0;
}